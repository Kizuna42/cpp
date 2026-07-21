#!/usr/bin/env bash

set -uo pipefail

ROOT=$(CDPATH= cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
TESTS="$ROOT/tests/cpp05_09"
if ! RUN_DIR=$(mktemp -d "${TMPDIR:-/tmp}/cpp05-09-verify.XXXXXX"); then
	printf 'Error: could not create verification directory.\n' >&2
	exit 1
fi
PASS=0
FAIL=0
SKIP=0

dirs=(
	cpp05/ex00 cpp05/ex01 cpp05/ex02 cpp05/ex03
	cpp06/ex00 cpp06/ex01 cpp06/ex02
	cpp07/ex00 cpp07/ex01 cpp07/ex02
	cpp08/ex00 cpp08/ex01 cpp08/ex02
	cpp09/ex00 cpp09/ex01 cpp09/ex02
)

cleanup()
{
	local command_status=$?
	trap - EXIT
	for dir in "${dirs[@]}"; do
		(cd "$ROOT/$dir" && make fclean >/dev/null 2>&1) || true
	done
	rm -rf "$RUN_DIR"
	exit "$command_status"
}

trap cleanup EXIT

pass()
{
	PASS=$((PASS + 1))
	printf 'PASS %s\n' "$1"
}

fail()
{
	FAIL=$((FAIL + 1))
	printf 'FAIL %s\n' "$1"
}

skip()
{
	SKIP=$((SKIP + 1))
	printf 'SKIP %s\n' "$1"
}

expect_contains()
{
	local name=$1
	local needle=$2
	shift 2
	local output
	if output=$("$@" 2>&1) && grep -Fq -- "$needle" <<< "$output"; then
		pass "$name"
	else
		fail "$name"
		printf '%s\n' "$output"
	fi
}

expect_exact()
{
	local name=$1
	local expected=$2
	shift 2
	local output
	if output=$("$@" 2>&1) && [[ "$output" == "$expected" ]]; then
		pass "$name"
	else
		fail "$name"
		printf 'expected=[%s] actual=[%s]\n' "$expected" "$output"
	fi
}

expect_block()
{
	local name=$1
	local expected=$2
	shift 2
	local output
	if output=$("$@" 2>&1) && [[ "$output" == *"$expected"* ]]; then
		pass "$name"
	else
		fail "$name"
		printf 'expected block=[%s] actual=[%s]\n' "$expected" "$output"
	fi
}

expect_error()
{
	local name=$1
	local needle=$2
	shift 2
	local output
	local command_status
	output=$("$@" 2>&1)
	command_status=$?
	if [[ $command_status -ne 0 ]] && grep -Fq -- "$needle" <<< "$output"; then
		pass "$name"
	else
		fail "$name"
		printf 'status=%s output=[%s]\n' "$command_status" "$output"
	fi
}

expect_compile_failure()
{
	local name=$1
	shift
	if "$@" >"$RUN_DIR/compile-failure.log" 2>&1; then
		fail "$name"
	else
		pass "$name"
	fi
}

expect_absent()
{
	local name=$1
	local pattern=$2
	local file=$3
	if grep -Eq -- "$pattern" "$file"; then
		fail "$name"
	else
		pass "$name"
	fi
}

run_btc()
{
	(cd "$ROOT/cpp09/ex00" && ./btc "$1")
}

run_valgrind_case()
{
	local name=$1
	shift
	if valgrind --quiet --error-exitcode=99 --leak-check=full \
		--show-leak-kinds=all --errors-for-leak-kinds=all "$@" \
		>"$RUN_DIR/valgrind.log" 2>&1; then
		pass "valgrind $name"
	else
		fail "valgrind $name"
		sed -n '1,80p' "$RUN_DIR/valgrind.log"
	fi
}

run_valgrind_btc_case()
{
	if (cd "$ROOT/cpp09/ex00" && \
		valgrind --quiet --error-exitcode=99 --leak-check=full \
		--show-leak-kinds=all --errors-for-leak-kinds=all \
		./btc input.txt) >"$RUN_DIR/valgrind.log" 2>&1; then
		pass 'valgrind case 14'
	else
		fail 'valgrind case 14'
		sed -n '1,80p' "$RUN_DIR/valgrind.log"
	fi
}

for dir in "${dirs[@]}"; do
	if (cd "$ROOT/$dir" && make re >"$RUN_DIR/build.log" 2>&1); then
		pass "build $dir"
	else
		fail "build $dir"
		sed -n '1,80p' "$RUN_DIR/build.log"
	fi
	if (cd "$ROOT/$dir" && make -q); then
		pass "no relink $dir"
	else
		fail "no relink $dir"
	fi
done

header_count=0
while IFS= read -r header; do
	header_count=$((header_count + 1))
	if c++ -std=c++98 -Wall -Wextra -Werror -x c++ \
		-include "$header" -c /dev/null -o "$RUN_DIR/header.o"; then
		pass "standalone header ${header#$ROOT/}"
	else
		fail "standalone header ${header#$ROOT/}"
	fi
done < <(find "$ROOT/cpp05" "$ROOT/cpp06" "$ROOT/cpp07" \
	"$ROOT/cpp08" "$ROOT/cpp09" -type f -name '*.hpp' | sort)

if [[ $header_count -eq 26 ]]; then
	pass 'header inventory 26'
else
	fail "header inventory expected 26 got $header_count"
fi

cd "$RUN_DIR" || exit 1

expect_contains 'cpp05 ex00 smoke' 'FormatCheck, bureaucrat grade 42.' "$ROOT/cpp05/ex00/bureaucrat"
expect_contains 'cpp05 ex01 smoke' 'Director signed Secret Form' "$ROOT/cpp05/ex01/form"
expect_contains 'cpp05 ex02 smoke' 'Admin couldn' "$ROOT/cpp05/ex02/aform"
expect_contains 'cpp05 ex03 smoke' 'Unknown form type' "$ROOT/cpp05/ex03/intern"
expect_contains 'cpp06 ex00 int' 'int: 42' "$ROOT/cpp06/ex00/convert" 42
expect_contains 'cpp06 ex01 pointer roundtrip' 'Pointers equal: PASS' "$ROOT/cpp06/ex01/serializer"
expect_contains 'cpp06 ex02 identify' $'Testing A instance:\nA\nA' "$ROOT/cpp06/ex02/identify"
expect_contains 'cpp07 ex00 subject' 'min(a, b) = 2' "$ROOT/cpp07/ex00/whatever"
expect_contains 'cpp07 ex01 subject' $'0\n1\n2\n3\n4\n42\n42\n42\n42\n42' "$ROOT/cpp07/ex01/iter"
expect_contains 'cpp07 ex02 deep copy' 'Copy: Array[4]: {1, 2, 3, 4}' "$ROOT/cpp07/ex02/array_test"
expect_contains 'cpp08 ex00 easyfind' 'Found first occurrence of 5 at position: 0' "$ROOT/cpp08/ex00/easyfind"
expect_contains 'cpp08 ex01 subject' $'2\n14' "$ROOT/cpp08/ex01/span"
expect_contains 'cpp08 ex02 subject' $'17\n1\n5\n3\n5\n737\n0' "$ROOT/cpp08/ex02/mutantstack"
expect_contains 'cpp09 ex00 subject' '2011-01-03 => 3 = 0.9' run_btc "$ROOT/cpp09/ex00/input.txt"
expect_exact 'cpp09 ex01 subject' '42' "$ROOT/cpp09/ex01/RPN" '8 9 * 9 - 9 - 9 - 4 - 1 +'
expect_contains 'cpp09 ex02 subject' 'After:  1 3 4 5 7 9' "$ROOT/cpp09/ex02/PmergeMe" 3 5 9 7 4 1

expect_contains 'scalar nan' 'float: nanf' "$ROOT/cpp06/ex00/convert" nan
expect_contains 'scalar int max' 'int: 2147483647' "$ROOT/cpp06/ex00/convert" 2147483647
expect_contains 'scalar int overflow keeps double' $'int: impossible\nfloat: 2.14748e+09f\ndouble: 2.14748e+09' "$ROOT/cpp06/ex00/convert" 2147483648
expect_contains 'scalar float overflow' $'float: impossible\ndouble: 1e+39' "$ROOT/cpp06/ex00/convert" 999999999999999999999999999999999999999.0f
expect_contains 'scalar truncates before int range check' 'int: -2147483648' "$ROOT/cpp06/ex00/convert" -2147483648.9
expect_contains 'scalar truncates before char range check' 'char: Non displayable' "$ROOT/cpp06/ex00/convert" -0.9
scalar_subnormal=$(printf '0.%0307d1' 0)
expect_contains 'scalar accepts double subnormal' 'double: 1e-308' "$ROOT/cpp06/ex00/convert" "$scalar_subnormal"

if c++ -std=c++98 -Wall -Wextra -Werror -I"$ROOT/cpp05/ex01" \
	"$TESTS/form_repeat.cpp" "$ROOT/cpp05/ex01/Bureaucrat.cpp" \
	"$ROOT/cpp05/ex01/Form.cpp" -o "$RUN_DIR/form_repeat"; then
	expect_contains 'cpp05 repeated signing is idempotent' 'repeat=ok' "$RUN_DIR/form_repeat"
else
	fail 'cpp05 repeated-sign harness compile'
fi

if c++ -std=c++98 -Wall -Wextra -Werror -I"$ROOT/cpp05/ex02" \
	"$TESTS/aform_failure.cpp" "$ROOT/cpp05/ex02/Bureaucrat.cpp" \
	"$ROOT/cpp05/ex02/AForm.cpp" "$ROOT/cpp05/ex02/ShrubberyCreationForm.cpp" \
	-o "$RUN_DIR/aform_failure"; then
	if aform_output=$("$RUN_DIR/aform_failure") && \
		grep -Fq "couldn't execute" <<< "$aform_output" && \
		! grep -Fq 'Executor executes' <<< "$aform_output"; then
		pass 'cpp05 failed action has no success message'
	else
		fail 'cpp05 failed action has no success message'
	fi
else
	fail 'cpp05 failed-action harness compile'
fi

expect_compile_failure 'cpp05 executeAction is not public' \
	c++ -std=c++98 -Wall -Wextra -Werror -I"$ROOT/cpp05/ex02" \
	"$TESTS/aform_access.cpp" "$ROOT/cpp05/ex02/AForm.cpp" \
	"$ROOT/cpp05/ex02/Bureaucrat.cpp" \
	"$ROOT/cpp05/ex02/ShrubberyCreationForm.cpp" \
	-o "$RUN_DIR/aform_access"

if c++ -std=c++98 -Wall -Wextra -Werror -I"$ROOT/cpp07/ex01" \
	"$TESTS/iter_eval.cpp" -o "$RUN_DIR/iter_eval"; then
	expect_exact 'cpp07 ex01 evaluator main' $'0\n1\n2\n3\n4\n42\n42\n42\n42\n42' "$RUN_DIR/iter_eval"
else
	fail 'cpp07 ex01 evaluator main compile'
fi

if c++ -std=c++98 -Wall -Wextra -Werror -I"$ROOT/cpp07/ex02" \
	"$TESTS/array_eval.cpp" -o "$RUN_DIR/array_eval"; then
	if "$RUN_DIR/array_eval"; then
		pass 'cpp07 ex02 evaluator main with required includes'
	else
		fail 'cpp07 ex02 evaluator main with required includes'
	fi
else
	fail 'cpp07 ex02 evaluator main compile'
fi

if c++ -std=c++98 -Wall -Wextra -Werror -I"$ROOT/cpp07/ex02" \
	"$TESTS/array_throw.cpp" -o "$RUN_DIR/array_throw"; then
	if "$RUN_DIR/array_throw"; then
		pass 'cpp07 ex02 exception-path behavior'
	else
		fail 'cpp07 ex02 exception-path behavior'
	fi
else
	fail 'cpp07 ex02 exception-path harness compile'
fi

if c++ -std=c++98 -Wall -Wextra -Werror -I"$ROOT/cpp08/ex01" \
	"$TESTS/span_extreme.cpp" "$ROOT/cpp08/ex01/Span.cpp" -o "$RUN_DIR/span_extreme"; then
	expect_exact 'cpp08 ex01 full int-domain span' $'4294967295\n4294967295' "$RUN_DIR/span_extreme"
else
	fail 'cpp08 ex01 full int-domain harness compile'
fi

if c++ -std=c++98 -Wall -Wextra -Werror -I"$ROOT/cpp08/ex01" \
	"$TESTS/span_input.cpp" "$ROOT/cpp08/ex01/Span.cpp" -o "$RUN_DIR/span_input"; then
	expect_exact 'cpp08 ex01 single-pass input iterator' '10 20' "$RUN_DIR/span_input"
else
	fail 'cpp08 ex01 single-pass harness compile'
fi

expect_compile_failure 'cpp09 RPN reset is not public' \
	c++ -std=c++98 -Wall -Wextra -Werror -I"$ROOT/cpp09/ex01" \
	"$TESTS/rpn_access.cpp" "$ROOT/cpp09/ex01/RPN.cpp" \
	-o "$RUN_DIR/rpn_access"

scalar_static_count=$(grep -Ec '^[[:space:]]*static[[:space:]]' \
	"$ROOT/cpp06/ex00/ScalarConverter.hpp")
if [[ $scalar_static_count -eq 1 ]]; then
	pass 'ScalarConverter exposes only convert as a static method'
else
	fail "ScalarConverter expected 1 static method got $scalar_static_count"
fi
grep -Eq 'const[[:space:]]+size_t[[:space:]]+length' "$ROOT/cpp07/ex01/iter.hpp" \
	&& pass 'iter length is passed as a const value' \
	|| fail 'iter length is passed as a const value'
expect_absent 'Array has no test-only public helpers' \
	'^[[:space:]]*void[[:space:]]+(fill|display)[[:space:]]*\(' \
	"$ROOT/cpp07/ex02/Array.hpp"
expect_absent 'Span has no test-only public helpers' \
	'^[[:space:]]*(unsigned int|bool|void)[[:space:]]+(size|maxSize|empty|full|display)[[:space:]]*\(' \
	"$ROOT/cpp08/ex01/Span.hpp"
expect_absent 'MutantStack has no duplicate or display helpers' \
	'^[[:space:]]*(size_t|bool|void)[[:space:]]+(size|empty|display|displayReverse)[[:space:]]*\(' \
	"$ROOT/cpp08/ex02/MutantStack.hpp"

for dir in "${dirs[@]}"; do
	if (cd "$ROOT/$dir" && make fclean >/dev/null && \
		make CXXFLAGS='-Wall -Wextra -Werror -std=c++98 -pedantic-errors' \
		>"$RUN_DIR/pedantic.log" 2>&1); then
		pass "pedantic build $dir"
	else
		fail "pedantic build $dir"
		sed -n '1,80p' "$RUN_DIR/pedantic.log"
	fi
done

expect_exact 'RPN integer division at each step' '4' "$ROOT/cpp09/ex01/RPN" '5 2 / 2 *'
expect_error 'RPN rejects empty expression' 'Error' "$ROOT/cpp09/ex01/RPN" ''
expect_error 'RPN rejects decimal token' 'Error' "$ROOT/cpp09/ex01/RPN" '1.5 2 +'
expect_error 'RPN rejects malformed expression' 'Error' "$ROOT/cpp09/ex01/RPN" '1 2'
expect_error 'RPN rejects division by zero' 'Error' "$ROOT/cpp09/ex01/RPN" '1 0 /'
expect_error 'RPN rejects integer overflow' 'Error' "$ROOT/cpp09/ex01/RPN" \
	'9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *'

expect_error 'PmergeMe rejects zero' 'Error' "$ROOT/cpp09/ex02/PmergeMe" 0 1
expect_error 'PmergeMe rejects negative' 'Error' "$ROOT/cpp09/ex02/PmergeMe" 1 -2
expect_error 'PmergeMe rejects int overflow' 'Error' "$ROOT/cpp09/ex02/PmergeMe" 2147483648
expect_error 'PmergeMe rejects invalid token' 'Error' "$ROOT/cpp09/ex02/PmergeMe" 1 two 3
expect_contains 'PmergeMe single value' 'After:  42' "$ROOT/cpp09/ex02/PmergeMe" 42
expect_contains 'PmergeMe two values' 'After:  1 2' "$ROOT/cpp09/ex02/PmergeMe" 2 1
expect_contains 'PmergeMe accepts explicit plus' 'After:  1 2 3' "$ROOT/cpp09/ex02/PmergeMe" +3 1 2
expect_contains 'PmergeMe sorted input' 'After:  1 2 3 4 5' "$ROOT/cpp09/ex02/PmergeMe" 1 2 3 4 5
expect_contains 'PmergeMe duplicates' 'After:  1 3 5 5' "$ROOT/cpp09/ex02/PmergeMe" 5 3 5 1

descending=()
expected_values=()
for ((i = 3000; i >= 1; i--)); do
	descending+=("$i")
done
for ((i = 1; i <= 3000; i++)); do
	expected_values+=("$i")
done
if pmerge_output=$("$ROOT/cpp09/ex02/PmergeMe" "${descending[@]}"); then
	pmerge_after=$(grep '^After:' <<< "$pmerge_output" | sed 's/^After:[[:space:]]*//')
	pmerge_expected=$(printf '%s ' "${expected_values[@]}")
	pmerge_expected=${pmerge_expected% }
	if [[ "$pmerge_after" == "$pmerge_expected" ]]; then
		pass 'PmergeMe 3000 descending'
	else
		fail 'PmergeMe 3000 descending'
	fi
else
	fail 'PmergeMe 3000 descending'
fi

property_ok=1
for ((n = 1; n <= 100 && property_ok == 1; n++)); do
	for ((trial = 0; trial < 5 && property_ok == 1; trial++)); do
		values=()
		for ((i = 0; i < n; i++)); do
			values+=("$(( (i * 1103515245 + n * 12345 + trial * 97) % 997 + 1 ))")
		done
		if ! pmerge_output=$("$ROOT/cpp09/ex02/PmergeMe" "${values[@]}"); then
			property_ok=0
			break
		fi
		pmerge_after=$(grep '^After:' <<< "$pmerge_output" | sed 's/^After:[[:space:]]*//')
		pmerge_expected=$(printf '%s\n' "${values[@]}" | sort -n | paste -sd ' ' -)
		if [[ "$pmerge_after" != "$pmerge_expected" ]]; then
			property_ok=0
		fi
	done
done
if [[ $property_ok -eq 1 ]]; then
	pass 'PmergeMe property 500 deterministic cases'
else
	fail 'PmergeMe property 500 deterministic cases'
fi

if btc_output=$(run_btc "$TESTS/btc_edge.txt" 2>&1); then
	grep -Fq '2012-02-29 => 1' <<< "$btc_output" && pass 'btc leap day' || fail 'btc leap day'
	grep -Fq '2011-01-03 => 1e-11 = 3e-12' <<< "$btc_output" && pass 'btc preserves tiny positive result' || fail 'btc preserves tiny positive result'
	grep -Fq 'Error: bad input => 2011-02-29' <<< "$btc_output" && pass 'btc rejects invalid leap day' || fail 'btc rejects invalid leap day'
	grep -Fq '2101-01-01 => 1' <<< "$btc_output" && pass 'btc future date uses lower DB date' || fail 'btc future date uses lower DB date'
	grep -Fq 'Error: too large a number.' <<< "$btc_output" && pass 'btc upper bound' || fail 'btc upper bound'
	grep -Fq 'Error: not a positive number.' <<< "$btc_output" && pass 'btc negative value' || fail 'btc negative value'
	grep -Fq 'Error: bad input => nan' <<< "$btc_output" && pass 'btc rejects nan' || fail 'btc rejects nan'
	grep -Fq 'Error: bad input => +inf' <<< "$btc_output" && pass 'btc rejects infinity' || fail 'btc rejects infinity'
	grep -Fq 'No exchange rate available for date: 2009-01-01' <<< "$btc_output" && pass 'btc before first DB date' || fail 'btc before first DB date'
else
	for btc_case in \
		'btc leap day' \
		'btc preserves tiny positive result' \
		'btc rejects invalid leap day' \
		'btc future date uses lower DB date' \
		'btc upper bound' \
		'btc negative value' \
		'btc rejects nan' \
		'btc rejects infinity' \
		'btc before first DB date'; do
		fail "$btc_case"
	done
	printf '%s\n' "$btc_output"
fi

# Subject-example conformance and static policy checks (frozen against
# official subject PDFs; do not edit expected strings without re-reading
# the PDF).
expect_exact 'scalar subject example 0' $'char: Non displayable\nint: 0\nfloat: 0.0f\ndouble: 0.0' "$ROOT/cpp06/ex00/convert" 0
expect_exact 'scalar subject example nan' $'char: impossible\nint: impossible\nfloat: nanf\ndouble: nan' "$ROOT/cpp06/ex00/convert" nan
expect_exact 'scalar subject example 42.0f' $'char: \'*\'\nint: 42\nfloat: 42.0f\ndouble: 42.0' "$ROOT/cpp06/ex00/convert" 42.0f
expect_exact 'scalar char literal' $'char: \'a\'\nint: 97\nfloat: 97.0f\ndouble: 97.0' "$ROOT/cpp06/ex00/convert" a
expect_exact 'scalar pseudo literal +inf' $'char: impossible\nint: impossible\nfloat: +inff\ndouble: +inf' "$ROOT/cpp06/ex00/convert" +inf
expect_exact 'scalar pseudo literal -inff' $'char: impossible\nint: impossible\nfloat: -inff\ndouble: -inf' "$ROOT/cpp06/ex00/convert" -inff
expect_exact 'scalar garbage is impossible' $'char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible' "$ROOT/cpp06/ex00/convert" abc
expect_block 'cpp07 ex00 subject output block' $'a = 3, b = 2\nmin(a, b) = 2\nmax(a, b) = 3\nc = chaine2, d = chaine1\nmin(c, d) = chaine1\nmax(c, d) = chaine2' "$ROOT/cpp07/ex00/whatever"
expect_exact 'RPN subject example 2' '42' "$ROOT/cpp09/ex01/RPN" '7 7 * 7 -'
expect_exact 'RPN subject example 3' '0' "$ROOT/cpp09/ex01/RPN" '1 2 * 2 / 2 * 2 4 - +'
expect_error 'RPN rejects parenthesized infix' 'Error' "$ROOT/cpp09/ex01/RPN" '(1 + 1)'
expect_error 'btc requires input file argument' 'Error: could not open file.' "$ROOT/cpp09/ex00/btc"
expect_error 'btc missing input file' 'Error: could not open file.' run_btc missing-input.txt
if "$ROOT/cpp09/ex02/PmergeMe" 3 5 9 7 4 >"$RUN_DIR/pmerge_subject.out" 2>&1 && \
	[[ "$(wc -l < "$RUN_DIR/pmerge_subject.out" | tr -d '[:space:]')" == 4 ]] && \
	sed -n '1p' "$RUN_DIR/pmerge_subject.out" | grep -qx 'Before: 3 5 9 7 4' && \
	sed -n '2p' "$RUN_DIR/pmerge_subject.out" | grep -qx 'After:  3 4 5 7 9' && \
	sed -n '3p' "$RUN_DIR/pmerge_subject.out" | \
		grep -Eqx 'Time to process a range of 5 elements with std::vector : [0-9]+\.[0-9]+ us' && \
	sed -n '4p' "$RUN_DIR/pmerge_subject.out" | \
		grep -Eqx 'Time to process a range of 5 elements with std::deque  : [0-9]+\.[0-9]+ us'; then
	pass 'PmergeMe subject example full structure'
else
	fail 'PmergeMe subject example full structure'
	cat "$RUN_DIR/pmerge_subject.out"
fi
expect_contains 'cpp05 ex00 grade too high boundary' 'Caught GradeTooHighException' "$ROOT/cpp05/ex00/bureaucrat"
expect_contains 'cpp05 ex00 grade too low boundary' 'Caught GradeTooLowException' "$ROOT/cpp05/ex00/bureaucrat"
expect_contains 'cpp08 ex00 not-found path' 'easyfind: value not found' "$ROOT/cpp08/ex00/easyfind"

forbidden_hits=$(grep -RnE 'using[[:space:]]+namespace|(^|[^_[:alnum:]])friend([^_[:alnum:]]|$)|printf|malloc|calloc|realloc|(^|[^_[:alnum:]])free[[:space:]]*\(' \
	--include='*.cpp' --include='*.hpp' \
	"$ROOT/cpp05" "$ROOT/cpp06" "$ROOT/cpp07" "$ROOT/cpp08" "$ROOT/cpp09" 2>&1)
forbidden_status=$?
if [[ $forbidden_status -eq 1 ]]; then
	pass 'sources free of forbidden constructs'
else
	fail 'sources free of forbidden constructs'
	printf '%s\n' "$forbidden_hits"
fi

typeinfo_hits=$(grep -RnE '#[[:space:]]*include[[:space:]]*[<"]typeinfo[>"]' \
	--include='*.cpp' --include='*.hpp' \
	"$ROOT/cpp05" "$ROOT/cpp06" "$ROOT/cpp07" "$ROOT/cpp08" "$ROOT/cpp09" 2>&1)
typeinfo_status=$?
if [[ $typeinfo_status -eq 1 ]]; then
	pass 'no typeinfo include anywhere'
else
	fail 'no typeinfo include anywhere'
	printf '%s\n' "$typeinfo_hits"
fi

makefile_flags_ok=1
for dir in "${dirs[@]}"; do
	for flag in -Wall -Wextra -Werror -std=c++98; do
		if ! grep -q -- "$flag" "$ROOT/$dir/Makefile"; then
			makefile_flags_ok=0
			printf 'missing %s in %s/Makefile\n' "$flag" "$dir"
		fi
	done
done
if [[ $makefile_flags_ok -eq 1 ]]; then
	pass 'makefiles carry mandated flags'
else
	fail 'makefiles carry mandated flags'
fi

build_flags_ok=1
for dir in "${dirs[@]}"; do
	if ! dry_run_output=$( (cd "$ROOT/$dir" && make -nB re) 2>/dev/null ); then
		build_flags_ok=0
		printf 'make -nB re failed in %s\n' "$dir"
		continue
	fi
	compile_lines=$(printf '%s\n' "$dry_run_output" | grep -E '(^|[[:space:]])-c([[:space:]]|$)')
	if [[ -z "$compile_lines" ]]; then
		build_flags_ok=0
		printf 'no compile command found in %s\n' "$dir"
		continue
	fi
	if [[ -n "$(printf '%s\n' "$compile_lines" | \
		grep -Ev 'c\+\+ .*-Wall .*-Wextra .*-Werror .*-std=c\+\+98')" ]]; then
		build_flags_ok=0
		printf 'compile command missing mandated flags in %s\n' "$dir"
	fi
done
if [[ $build_flags_ok -eq 1 ]]; then
	pass 'compile commands carry mandated flags'
else
	fail 'compile commands carry mandated flags'
fi

if command -v valgrind >/dev/null 2>&1; then
	run_valgrind_case 'Array exception paths' "$RUN_DIR/array_throw"
	run_valgrind_case 'case 1' "$ROOT/cpp05/ex00/bureaucrat"
	run_valgrind_case 'case 2' "$ROOT/cpp05/ex01/form"
	run_valgrind_case 'case 3' "$ROOT/cpp05/ex02/aform"
	run_valgrind_case 'case 4' "$ROOT/cpp05/ex03/intern"
	run_valgrind_case 'case 5' "$ROOT/cpp06/ex00/convert" 42
	run_valgrind_case 'case 6' "$ROOT/cpp06/ex01/serializer"
	run_valgrind_case 'case 7' "$ROOT/cpp06/ex02/identify"
	run_valgrind_case 'case 8' "$ROOT/cpp07/ex00/whatever"
	run_valgrind_case 'case 9' "$ROOT/cpp07/ex01/iter"
	run_valgrind_case 'case 10' "$ROOT/cpp07/ex02/array_test"
	run_valgrind_case 'case 11' "$ROOT/cpp08/ex00/easyfind"
	run_valgrind_case 'case 12' "$ROOT/cpp08/ex01/span"
	run_valgrind_case 'case 13' "$ROOT/cpp08/ex02/mutantstack"
	run_valgrind_btc_case
	run_valgrind_case 'case 15' "$ROOT/cpp09/ex01/RPN" \
		'8 9 * 9 - 9 - 9 - 4 - 1 +'
	run_valgrind_case 'case 16' "$ROOT/cpp09/ex02/PmergeMe" 3 5 9 7 4 1
else
	skip 'valgrind unavailable (run the documented Ubuntu container command)'
fi

printf 'SUMMARY pass=%d fail=%d skip=%d\n' "$PASS" "$FAIL" "$SKIP"
exit "$FAIL"
