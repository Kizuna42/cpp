#!/usr/bin/env python3
"""CPP09 regression tests; builds temporary copies, leaving submissions intact."""

import argparse
import bisect
import datetime
import decimal
import fractions
import itertools
import math
import os
from pathlib import Path
import random
import re
import shutil
import subprocess
import sys
import tempfile


ROOT = Path(__file__).resolve().parents[1]
FLAGS = ["-Wall", "-Wextra", "-Werror", "-std=c++98", "-pedantic-errors"]
COUNT = 0


def require(condition, message):
    global COUNT
    if not condition:
        raise RuntimeError(message)
    COUNT += 1


def run(args, cwd=None, stdin=None, timeout=120):
    result = subprocess.run([str(arg) for arg in args], cwd=cwd, input=stdin,
                            text=True, capture_output=True, timeout=timeout)
    if "AddressSanitizer" in result.stderr or "runtime error:" in result.stderr:
        raise RuntimeError(f"Sanitizer failure: {args}\n{result.stderr}")
    return result


def success(args, **kwargs):
    result = run(args, **kwargs)
    require(result.returncode == 0, f"Failed: {args}\n{result.stdout}{result.stderr}")
    return result


def close(actual, expected):
    return math.isclose(float(actual), float(expected), rel_tol=2e-13, abs_tol=1e-320)


def build(work, sanitize):
    flags = FLAGS + (["-fsanitize=address,undefined", "-fno-omit-frame-pointer", "-g"]
                     if sanitize else [])
    names = ["btc", "RPN", "PmergeMe"]
    for exercise, name in enumerate(names):
        source = ROOT / "cpp09" / f"ex{exercise:02}"
        target = work / source.name
        target.mkdir()
        for file in source.iterdir():
            if file.suffix in (".cpp", ".hpp", ".csv", ".txt") or file.name == "Makefile":
                shutil.copy2(file, target / file.name)
        success(["make", "re", "CXXFLAGS=" + " ".join(flags)], cwd=target)
        timestamp = (target / name).stat().st_mtime_ns
        success(["make"], cwd=target)
        require((target / name).stat().st_mtime_ns == timestamp, f"Unexpected relink: {name}")
        success(["make", "clean"], cwd=target)
        require((target / name).exists() and not (target / "obj").exists(), "clean failed")
        success(["make", "fclean"], cwd=target)
        require(not (target / name).exists(), "fclean failed")
        success(["make", "CXXFLAGS=" + " ".join(flags)], cwd=target)
        header = next(target.glob("*.hpp"))
        success(["c++", *flags, "-I", target, "-x", "c++", "-fsyntax-only", "-"],
                stdin=f'#include "{header.name}"\n#include "{header.name}"\nint main() {{}}\n')
    for exercise, harness, implementation in [("ex00", "bitcoin_api", "BitcoinExchange"),
                                                ("ex01", "rpn_batch", "RPN")]:
        success(["c++", *flags, "-I", work / exercise,
                 ROOT / "tests/cpp09" / (harness + ".cpp"),
                 work / exercise / (implementation + ".cpp"), "-o", work / harness])
    return flags


def bitcoin(work):
    executable = work / "ex00/btc"
    data = work / "ex00/data.csv"
    rates = {}
    for line in data.read_text().splitlines()[1:]:
        date, rate = line.split(",")
        rates[date] = decimal.Decimal(rate)
    dates = sorted(rates)
    rng = random.Random(420900)
    values = ["0", "-0", "+0", "1000", "1000.", "0001000.000", ".5", "+.5",
              "1000.0000000000000000000001", "999.999999999999999999999999",
              "-0.0000000000000000000001", "-1e-500", "1e-500", "0e99999999",
              "1e3", "1.0000000000000000000001e3", "1000000e-3", "1000001e-3",
              "1e99999999999999999999999999", "1e-99999999", "-1e99999999"]
    for _ in range(2000):
        values.append(rng.choice(["", "+", "-"]) + str(rng.randrange(0, 2001)) + "." +
                      "".join(str(rng.randrange(10)) for _ in range(rng.randrange(1, 100))))
    for _ in range(2000):
        values.append(str(rng.randrange(1, 10001)) + "." + str(rng.randrange(100000)) +
                      "e" + str(rng.randrange(-400, 401)))
    for n in [1, 16, 30, 100, 1000, 10000]:
        values.extend(["1000." + "0" * n + "1", "1000." + "0" * n,
                       "-0." + "0" * n + "1", "0" * n + "1000.0001"])
    # Short mantissas and exponents must not saturate to the 1000 boundary.
    for mantissa, exponent in itertools.product(
            ["0", "1", "2", "9", "10", "100", "1000", ".1", ".01", "0.001", "1.", "1.0", "00001"],
            range(-15, 16)):
        values.append(mantissa + "e" + str(exponent))
    invalid = ["", ".", "+", "-", "nan", "NaN", "inf", "+inf", "0x10", "1f",
               "1 2", "1..0", "--1", "1e", "1e+", "1e-", "1ee2", "1,5", "９", "1\x002"]
    cases = [("2011-01-03", value) for value in values + invalid]
    for year in range(1896, 2405):
        cases.append((f"{year}-02-29", "1"))
    for _ in range(1000):
        date = datetime.date(2009, 1, 1) + datetime.timedelta(days=rng.randrange(10000))
        cases.append((date.isoformat(), str(rng.randrange(1001))))
    cases += [(date, "1") for date in [dates[0], dates[-1], "0000-01-01", "2011-00-01",
                                      "2011-13-01", "2011-04-31", "2011-01-00",
                                      "2011-1-01", "2011-01-1", "9999-12-31"]]
    file = work / "bitcoin-input.txt"
    file.write_text("date | value\n" + "\n".join(f"{d} | {v}" for d, v in cases) + "\n")
    result = success([executable, file], cwd=work)
    require(not result.stderr, "btc wrote unexpected stderr")
    lines = result.stdout.splitlines()
    require(len(lines) == len(cases), "btc stopped early or omitted a row")
    for (date, value), line in zip(cases, lines):
        try:
            datetime.date.fromisoformat(date)
            valid_date = len(date) == 10
        except ValueError:
            valid_date = False
        if not valid_date or value in invalid:
            require(line.startswith("Error: bad input =>"), f"Accepted bad input: {date}|{value}")
            continue
        try:
            number = decimal.Decimal(value)
        except decimal.InvalidOperation:
            # The two explicit huge-exponent cases exceed Decimal's exponent
            # capacity too; their sign and magnitude determine the verdict.
            require(line == ("Error: not a positive number." if value.startswith("-") else
                             "Error: too large a number."), "Huge exponent misclassified")
            continue
        if number < 0:
            require(line == "Error: not a positive number.", f"Negative accepted: {value}")
        elif number > 1000:
            require(line == "Error: too large a number.", f"Upper bound failed: {value}")
        elif number != 0 and float(number) == 0:
            require(line == "Error: Number out of range", f"Unrepresentable positive silently lost: {value}")
        elif date < dates[0]:
            require(line.startswith("Error: No exchange rate available"), "Used a future rate")
        else:
            rate = rates[dates[bisect.bisect_right(dates, date) - 1]]
            product = float(number) * float(rate)
            if number != 0 and rate != 0 and product == 0:
                require(line == "Error: Exchange result out of range", "Product underflow silently lost")
                continue
            require(line.startswith(date + " => "), f"Valid row rejected: {value}: {line}")
            actual = line.split(" = ")[1]
            require(close(actual, product), f"Incorrect rate/result: {line}")
    # Check the literal subject output and a CRLF/no-final-newline input.
    file.write_bytes(b"date | value\r\n2011-01-03 | 3\r\n2011-01-09 | 1")
    result = success([executable, file], cwd=work)
    require(result.stdout == "2011-01-03 => 3 = 0.9\n2011-01-09 => 1 = 0.32\n", "Subject/CRLF failed")
    for content in ["date | value\n2011-01-03|1\n2011-01-03 | 2 | 3\n2011-01-03 | 1\n",
                    "bad header\n2011-01-03 | 1\n"]:
        file.write_text(content)
        result = success([executable, file], cwd=work)
        require(result.stdout.endswith("2011-01-03 => 1 = 0.3\n"), "Did not recover after bad row")
    file.write_text("")
    for args in [[], [file], [work / "missing"], [work], [file, file]]:
        result = run([executable, *args], cwd=work)
        require(result.returncode != 0 and result.stderr.startswith("Error:"), "File error missed")
    fixture = work / "db-fixture"
    fixture.mkdir()
    file.write_text("date | value\n2011-01-02 | 2\n")
    valid = "date,exchange_rate\n2011-01-01,2\n2011-01-03,3\n"
    (fixture / "data.csv").write_text(valid)
    result = success([executable, file], cwd=fixture)
    require(result.stdout == "2011-01-02 => 2 = 4\n", "Closest lower fixture failed")
    corrupt = ["", "date,exchange_rate\n", "date,exchange_rate\ninvalid\n",
               "2011-02-29,2\n", "2011-01-01,-1e-500\n", "2011-01-01,nan\n",
               "2011-01-01,inf\n", "2011-01-01,1e309\n", "2011-01-01,1,2\n",
               "2011-01-01,2\n2011-01-01,3\n"]
    for content in corrupt:
        (fixture / "data.csv").write_text(content)
        result = run([executable, file], cwd=fixture)
        require(result.returncode != 0 and result.stderr.startswith("Error:"), "Corrupt DB accepted")
    (fixture / "data.csv").write_text("2011-01-01,1e308\n")
    file.write_text("date | value\n2011-01-02 | 1000\n")
    result = success([executable, file], cwd=fixture)
    require(result.stdout.startswith("Error: Exchange result out of range"), "Printed infinite result")
    (fixture / "data.csv").write_text("2011-01-01,0.5\n")
    file.write_text("date | value\n2011-01-02 | 5e-324\n2011-01-02 | 0\n")
    result = success([executable, file], cwd=fixture)
    require(result.stdout == "Error: Exchange result out of range\n2011-01-02 => 0 = 0\n",
            "Product underflow silently lost or did not recover")
    (fixture / "data.csv").write_text("2011-01-01,-0\n")
    file.write_text("date | value\n2011-01-02 | 1\n")
    result = success([executable, file], cwd=fixture)
    require(result.stdout == "2011-01-02 => 1 = 0\n", "Negative zero leaked into display")
    db1, db2, db3 = [work / name for name in ["valid.csv", "corrupt.csv", "replacement.csv"]]
    db1.write_text(valid)
    db2.write_text("2011-01-01,999\ninvalid\n")
    db3.write_text("2011-01-01,7\n")
    success([work / "bitcoin_api", db1, db2, db3])
    print(f"PASS BitcoinExchange: {len(cases)} oracle rows, files, database reload")


def rpn(work):
    rng = random.Random(420901)
    cases = []
    for left, right, operator in itertools.product(range(10), range(10), "+-*/"):
        expected = None if operator == "/" and right == 0 else {
            "+": lambda: fractions.Fraction(left + right),
            "-": lambda: fractions.Fraction(left - right),
            "*": lambda: fractions.Fraction(left * right),
            "/": lambda: fractions.Fraction(left, right)}[operator]()
        cases.append((f"{left} {right} {operator}", expected))

    def expression(depth):
        if depth == 0 or rng.random() < 0.2:
            number = rng.randrange(10)
            return str(number), fractions.Fraction(number)
        a, left = expression(depth - 1)
        b, right = expression(depth - 1)
        operator = rng.choice("+-*/")
        if operator == "/" and right == 0:
            operator = "+"
        value = {"+": lambda: left + right, "-": lambda: left - right,
                 "*": lambda: left * right, "/": lambda: left / right}[operator]()
        return f"{a} {b} {operator}", value

    cases.extend(expression(rng.randrange(1, 7)) for _ in range(3000))
    cases.extend([("8 3 / 2 * 6 * 6 * 6 * 6 *", fractions.Fraction(6912)),
                  ("8 9 * 9 - 9 - 9 - 4 - 1 +", fractions.Fraction(42)),
                  ("7 7 * 7 -", fractions.Fraction(42)),
                  ("1 2 * 2 / 2 * 2 4 - +", fractions.Fraction(0)),
                  ("9 8 * 4 * 4 / 2 + 9 - 8 - 8 - 1 - 6 -", fractions.Fraction(42)),
                  ("1 2 * 2 / 2 + 5 * 6 - 1 3 * - 4 5 * * 8 /", fractions.Fraction(15)),
                  ("5 2 / 2 *", fractions.Fraction(5)), ("0 3 - 2 /", fractions.Fraction(-3, 2)),
                  ("9 " + "9 * " * 9, fractions.Fraction(9 ** 10)),
                  ("1 " + "9 / " * 100, fractions.Fraction(1, 9 ** 100)),
                  ("9 " + "9 * " * 400, None),
                  ("1 " + "9 / " * 400 + "9 * " * 400, None),
                  ("0 1 - 0 *", fractions.Fraction(0))])
    malformed = ["", " ", "+", "1 +", "1 2", "1 2 + +", "1 2 3 +", "12", "-1",
                 "+1", "1.5", "1e0", "(1 + 1)", "1 2 %", "1 2+", "12+", "９", "1,2+",
                 "1 1 1 - /", "1 0 /", "1 2 + garbage"]
    cases.extend((expr, None) for expr in malformed)
    result = success([work / "rpn_batch"], stdin="\n".join(expr for expr, _ in cases) + "\n")
    require(not result.stderr, "RPN batch stderr")
    output = result.stdout.splitlines()
    require(len(output) == len(cases), "RPN batch lost expressions")
    for (expr, expected), actual in zip(cases, output):
        require(actual == "Error" if expected is None else actual != "Error" and close(actual, expected),
                f"RPN mismatch: {expr!r}: expected {expected}, got {actual}")
    executable = work / "ex01/RPN"
    for expr, expected in cases[:40] + cases[-34:]:
        result = run([executable, expr])
        if expected is None:
            require(result.returncode != 0 and not result.stdout and result.stderr == "Error\n", "RPN CLI error")
        else:
            require(result.returncode == 0 and not result.stderr and close(result.stdout, expected), "RPN CLI result")
    for args in [[], ["1", "2"], ["\t 5\t2 / \r\n2 * "]]:
        result = run([executable, *args])
        require((result.returncode == 0 and result.stdout == "5\n") if len(args) == 1 else
                (result.returncode != 0 and result.stderr == "Error\n"), "RPN CLI arguments/whitespace")
    print(f"PASS RPN: {len(cases)} Fraction oracle expressions, copies/reuse, CLI")


def pmerge(work, flags, quick):
    executable = work / "ex02/PmergeMe"
    invalid = [[], ["0"], ["-1"], ["2147483648"], ["9" * 1000], [""], [" "], ["+"],
               ["1.0"], ["1e1"], ["0x10"], ["９"], ["1", "2 3"], [" 1"], ["1 "], ["++1"]]
    for args in invalid:
        result = run([executable, *args])
        require(result.returncode != 0 and not result.stdout and result.stderr == "Error\n", "Pmerge invalid input")
    rng = random.Random(420902)
    cases = [["42"], ["+3", "001", "2"], ["0" * 10000 + "1"], ["2147483647"] * 3000,
             list(range(3000, 0, -1)), [rng.randrange(1, 100000) for _ in range(3001)]]
    cases.extend([rng.randrange(1, 20) for _ in range(n)] for n in range(1, 50))
    for values in cases:
        result = success([executable, *values])
        output = result.stdout.splitlines()
        require(len(output) == 4 and not result.stderr, "Pmerge output must have four lines")
        require(output[0].startswith("Before: ") and
                [int(x.lstrip("+0") or "0") for x in output[0].split()[1:]] ==
                [int(str(x).lstrip("+0") or "0") for x in values], "Before input changed")
        require(output[1].startswith("After: ") and [int(x) for x in output[1].split()[1:]] ==
                sorted(int(str(x).lstrip("+0") or "0") for x in values), "CLI sort differs from Python sorted")
        for line, container in zip(output[2:], ["vector", "deque"]):
            pattern = rf"Time to process a range of {len(values)} elements with std::{container}\s+: (\d+\.\d+) us"
            require(re.fullmatch(pattern, line) is not None, f"Timing malformed: {line}")
    instrumented = work / "instrumented"
    instrumented.mkdir()
    header = (work / "ex02/PmergeMe.hpp").read_text()
    (instrumented / "PmergeMe.hpp").write_text(header.replace("private:", "public:", 1))
    source = (work / "ex02/PmergeMe.cpp").read_text()
    for original, replacement in [
        ("if (values[a] < values[b])", "if ((++auditComparisons, values[a] < values[b]))"),
        ("if (values[chain[mid]] <= value)", "if ((++auditComparisons, values[chain[mid]] <= value))")]:
        require(source.count(original) == 2, "Comparison instrumentation needs updating")
        source = source.replace(original, replacement)
    (instrumented / "PmergeMe.cpp").write_text("unsigned long auditComparisons = 0;\n" + source)
    success(["c++", *flags, "-O2", "-I", instrumented, ROOT / "tests/cpp09/pmerge_properties.cpp",
             instrumented / "PmergeMe.cpp", "-o", work / "pmerge_properties"])
    result = success([work / "pmerge_properties", "7" if quick else "9", "100" if quick else "1000"],
                     timeout=180)
    print(result.stdout.strip())


def valgrind(work):
    if shutil.which("valgrind") is None:
        raise RuntimeError("--valgrind requires Valgrind installed")
    cases = [(work / "ex00/btc", [work / "ex00/input.txt"], 0, None),
             (work / "ex00/btc", [work / "missing"], 1, None),
             (work / "bitcoin_api", [work / "valid.csv", work / "corrupt.csv",
                                    work / "replacement.csv"], 0, None),
             (work / "ex01/RPN", ["8 3 / 2 * 6 * 6 * 6 * 6 *"], 0, None),
             (work / "ex01/RPN", ["1 0 /"], 1, None),
             (work / "ex01/RPN", ["9 " + "9 * " * 400], 1, None),
             (work / "ex01/RPN", ["1 " + "9 / " * 400 + "9 * " * 400], 1, None),
             (work / "rpn_batch", [], 0, "1 0 /\n5 2 / 2 *\n1 2\n8 3 /\n"),
             (work / "ex02/PmergeMe", [3, 1, 2, 1, 2147483647], 0, None),
             (work / "ex02/PmergeMe", [7] * 3000, 0, None),
             (work / "ex02/PmergeMe", [1, -2], 1, None)]
    for index, (binary, args, expected_status, stdin) in enumerate(cases):
        log = work / f"valgrind-{index}.txt"
        result = run(["valgrind", "--leak-check=full", "--show-leak-kinds=all",
                      "--errors-for-leak-kinds=definite,indirect,possible", "--error-exitcode=99",
                      "--log-file=" + str(log), binary, *args], cwd=work, stdin=stdin)
        require(result.returncode == expected_status, f"Valgrind case {index} failed: {result.stderr}")
        evidence = log.read_text()
        require("ERROR SUMMARY: 0 errors" in evidence and
                "in use at exit: 0 bytes in 0 blocks" in evidence, f"Valgrind case {index}: {evidence}")
    print(f"PASS Valgrind: {len(cases)} cases, zero errors, zero bytes at exit")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--sanitize", action="store_true", help="Build/run with ASan and UBSan")
    parser.add_argument("--quick", action="store_true", help="Exhaust through n=7; 100 instead of 1000 random sorts")
    parser.add_argument("--valgrind", action="store_true", help="Also check Linux leaks and error paths")
    args = parser.parse_args()
    if args.sanitize and args.valgrind:
        parser.error("Run --sanitize and --valgrind separately")
    os.environ.setdefault("ASAN_OPTIONS", "detect_leaks=0" if sys.platform == "darwin" else "detect_leaks=1")
    with tempfile.TemporaryDirectory(prefix="cpp09-verify-") as directory:
        work = Path(directory)
        flags = build(work, args.sanitize)
        bitcoin(work)
        rpn(work)
        pmerge(work, flags, args.quick)
        if args.valgrind:
            valgrind(work)
    print(f"PASS CPP09: {COUNT} assertions; C++98; sanitize={args.sanitize}")


if __name__ == "__main__":
    main()
