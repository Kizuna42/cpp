#!/usr/bin/env bash
# CPP00〜04 の回帰チェック：ビルド・subject 例との出力比較・Valgrind によるリーク検出。
# 作業はソースのコピー上で行い、リポジトリには生成物を残さない。

set -uo pipefail

SOURCE_ROOT=$(CDPATH= cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
if ! RUN_DIR=$(mktemp -d "${TMPDIR:-/tmp}/cpp00-04-verify.XXXXXX"); then
	printf 'Error: could not create verification directory.\n' >&2
	exit 1
fi
trap 'rm -rf "$RUN_DIR"' EXIT
ROOT="$RUN_DIR/worktree"
mkdir "$ROOT" || exit 1
for source_dir in cpp00 cpp01 cpp02 cpp03 cpp04; do
	cp -R "$SOURCE_ROOT/$source_dir" "$ROOT/" || exit 1
done

CXX_BIN=${CXX:-c++}
PASS=0
FAIL=0

pass() { PASS=$((PASS + 1)); printf 'PASS %s\n' "$1"; }
fail() { FAIL=$((FAIL + 1)); printf 'FAIL %s\n' "$1"; }

# expect_output <name> <expected-file> <command...>
expect_output()
{
	local name=$1 expected=$2
	shift 2
	if "$@" >"$RUN_DIR/actual.txt" 2>&1 && diff -u "$expected" "$RUN_DIR/actual.txt"; then
		pass "$name"
	else
		fail "$name"
	fi
}

# expect_contains <name> <needle> <command...>
expect_contains()
{
	local name=$1 needle=$2 output
	shift 2
	output=$("$@" 2>&1)
	if grep -Fq -- "$needle" <<< "$output"; then
		pass "$name"
	else
		fail "$name"
		printf '%s\n' "$output" | sed -n '1,40p'
	fi
}

# 実行ファイル名は各 Makefile の NAME から取る
exe()
{
	local dir=$1
	printf '%s/%s/%s' "$ROOT" "$dir" "$(awk '/^NAME/ {print $NF; exit}' "$ROOT/$dir/Makefile")"
}

dirs=()
for d in "$ROOT"/cpp0[0-4]/ex*; do
	dirs+=("${d#"$ROOT"/}")
done

# 1. ビルド（-Wall -Wextra -Werror -std=c++98 は各 Makefile が指定）
for dir in "${dirs[@]}"; do
	if make -C "$ROOT/$dir" CXX="$CXX_BIN" >"$RUN_DIR/build.log" 2>&1 && [ -x "$(exe "$dir")" ]; then
		pass "build $dir"
	else
		fail "build $dir"
		sed -n '1,40p' "$RUN_DIR/build.log"
	fi
done

# 2. subject の例と出力を比較
cat >"$RUN_DIR/megaphone.txt" <<'EOF'
SHHHHH... I THINK THE STUDENTS ARE ON VACATION
EOF
expect_output 'cpp00/ex00 uppercase' "$RUN_DIR/megaphone.txt" \
	"$(exe cpp00/ex00)" "shhhhh... I think the students are on vacation"
cat >"$RUN_DIR/megaphone2.txt" <<'EOF'
DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF.
EOF
expect_output 'cpp00/ex00 multiple args' "$RUN_DIR/megaphone2.txt" \
	"$(exe cpp00/ex00)" Damnit " ! " "Sorry students, I thought this thing was off."
cat >"$RUN_DIR/megaphone3.txt" <<'EOF'
* LOUD AND UNBEARABLE FEEDBACK NOISE *
EOF
expect_output 'cpp00/ex00 no args' "$RUN_DIR/megaphone3.txt" "$(exe cpp00/ex00)"

phonebook_input()
{
	printf 'ADD\nJohn\nDoe\nJD\n0123456789\nsecret\nSEARCH\n0\n'
}
if phonebook_input | timeout 5 "$(exe cpp00/ex01)" >"$RUN_DIR/pb.txt" 2>&1; then
	if grep -Fq 'Darkest Secret: secret' "$RUN_DIR/pb.txt" \
		&& grep -Eq '^ +0\| +John\| +Doe\| +JD$' "$RUN_DIR/pb.txt"; then
		pass 'cpp00/ex01 ADD/SEARCH and exit on EOF'
	else
		fail 'cpp00/ex01 ADD/SEARCH and exit on EOF'
		sed -n '1,40p' "$RUN_DIR/pb.txt"
	fi
else
	fail 'cpp00/ex01 ADD/SEARCH and exit on EOF (timeout or error)'
fi
long_name=$(printf 'ADD\nAbcdefghijkl\nB\nC\n1\nS\nSEARCH\n0\nEXIT\n' \
	| timeout 5 "$(exe cpp00/ex01)" 2>&1)
if grep -Fq 'Abcdefghi.' <<< "$long_name"; then
	pass 'cpp00/ex01 truncates long fields with a dot'
else
	fail 'cpp00/ex01 truncates long fields with a dot'
fi

expect_contains 'cpp01/ex02 prints the same address' 'string' "$(exe cpp01/ex02)"

printf 'hello world\nhello again\nno match\n' >"$RUN_DIR/sed_in.txt"
printf 'bye world\nbye again\nno match\n' >"$RUN_DIR/sed_expected.txt"
if (cd "$RUN_DIR" && "$(exe cpp01/ex04)" sed_in.txt hello bye >/dev/null) \
	&& diff -u "$RUN_DIR/sed_expected.txt" "$RUN_DIR/sed_in.txt.replace"; then
	pass 'cpp01/ex04 replaces every occurrence'
else
	fail 'cpp01/ex04 replaces every occurrence'
fi
printf 'aaaa' >"$RUN_DIR/sed_overlap.txt"
if (cd "$RUN_DIR" && "$(exe cpp01/ex04)" sed_overlap.txt a aa >/dev/null) \
	&& [ "$(cat "$RUN_DIR/sed_overlap.txt.replace")" = 'aaaaaaaa' ]; then
	pass 'cpp01/ex04 does not rescan replaced text'
else
	fail 'cpp01/ex04 does not rescan replaced text'
fi
if (cd "$RUN_DIR" && ! "$(exe cpp01/ex04)" does_not_exist a b >/dev/null 2>&1); then
	pass 'cpp01/ex04 rejects a missing file'
else
	fail 'cpp01/ex04 rejects a missing file'
fi

harl_filter="$(exe cpp01/ex06)"
warning_out=$("$harl_filter" WARNING 2>&1)
if grep -Fq '[ WARNING ]' <<< "$warning_out" || grep -Fq '[WARNING]' <<< "$warning_out"; then
	if grep -Eq '\[ ?ERROR ?\]' <<< "$warning_out" && ! grep -Eq '\[ ?(DEBUG|INFO) ?\]' <<< "$warning_out"; then
		pass 'cpp01/ex06 WARNING prints WARNING and ERROR only'
	else
		fail 'cpp01/ex06 WARNING prints WARNING and ERROR only'
	fi
else
	fail 'cpp01/ex06 WARNING prints WARNING and ERROR only'
fi
expect_contains 'cpp01/ex06 unknown level' \
	'[ Probably complaining about insignificant problems ]' "$harl_filter" foo

cat >"$RUN_DIR/fixed00.txt" <<'EOF'
Default constructor called
Copy constructor called
Copy assignment operator called
getRawBits member function called
Default constructor called
Copy assignment operator called
getRawBits member function called
getRawBits member function called
0
getRawBits member function called
0
getRawBits member function called
0
Destructor called
Destructor called
Destructor called
EOF
expect_output 'cpp02/ex00 subject output' "$RUN_DIR/fixed00.txt" "$(exe cpp02/ex00)"

cat >"$RUN_DIR/fixed01.txt" <<'EOF'
Default constructor called
Int constructor called
Float constructor called
Copy constructor called
Copy assignment operator called
Float constructor called
Copy assignment operator called
Destructor called
a is 1234.43
b is 10
c is 42.4219
d is 10
a is 1234 as integer
b is 10 as integer
c is 42 as integer
d is 10 as integer
Destructor called
Destructor called
Destructor called
Destructor called
EOF
expect_output 'cpp02/ex01 subject output' "$RUN_DIR/fixed01.txt" "$(exe cpp02/ex01)"

cat >"$RUN_DIR/fixed02.txt" <<'EOF'
0
0.00390625
0.00390625
0.00390625
0.0078125
10.1016
10.1016
EOF
"$(exe cpp02/ex02)" >"$RUN_DIR/fixed02_full.txt" 2>&1
if head -n 7 "$RUN_DIR/fixed02_full.txt" | diff -u "$RUN_DIR/fixed02.txt" -; then
	pass 'cpp02/ex02 subject output'
else
	fail 'cpp02/ex02 subject output'
fi

bsp_out=$("$(exe cpp02/ex03)" 2>&1)
if grep -Fq 'Point (2, 1): INSIDE' <<< "$bsp_out" \
	&& grep -Fq 'Point (2, 0): OUTSIDE' <<< "$bsp_out" \
	&& grep -Fq 'Vertex A(0, 0): OUTSIDE' <<< "$bsp_out"; then
	pass 'cpp02/ex03 inside / edge / vertex'
else
	fail 'cpp02/ex03 inside / edge / vertex'
fi
if grep -A4 -E 'On Edges|Triangle Vertices' <<< "$bsp_out" | grep -q INSIDE; then
	fail 'cpp02/ex03 edges and vertices are OUTSIDE'
else
	pass 'cpp02/ex03 edges and vertices are OUTSIDE'
fi

expect_contains 'cpp03/ex03 whoAmI DiamondTrap name' 'DiamondTrap name: DiamondBot' "$(exe cpp03/ex03)"
expect_contains 'cpp03/ex03 whoAmI ClapTrap name' 'ClapTrap name: DiamondBot_clap_name' "$(exe cpp03/ex03)"
expect_contains 'cpp03/ex03 stats' 'EP: 50' "$(exe cpp03/ex03)"

expect_contains 'cpp04/ex00 virtual makeSound (Cat)' 'Meow' "$(exe cpp04/ex00)"
expect_contains 'cpp04/ex00 WrongCat uses WrongAnimal sound' 'WrongAnimal makes a wrong animal sound' "$(exe cpp04/ex00)"
expect_contains 'cpp04/ex03 subject ice' '* shoots an ice bolt at bob *' "$(exe cpp04/ex03)"
expect_contains 'cpp04/ex03 subject cure' "* heals bob's wounds *" "$(exe cpp04/ex03)"

# 3. Valgrind（リーク・不正アクセス）
run_valgrind()
{
	local name=$1
	shift
	if valgrind --quiet --error-exitcode=99 --leak-check=full \
		--errors-for-leak-kinds=definite,indirect,possible "$@" \
		</dev/null >/dev/null 2>"$RUN_DIR/valgrind.log"; then
		pass "valgrind $name"
	else
		fail "valgrind $name"
		sed -n '1,60p' "$RUN_DIR/valgrind.log"
	fi
}

if command -v valgrind >/dev/null 2>&1; then
	for dir in "${dirs[@]}"; do
		case $dir in
			cpp00/ex00) run_valgrind "$dir" "$(exe "$dir")" "hello" ;;
			cpp01/ex04) run_valgrind "$dir" "$(exe "$dir")" "$RUN_DIR/sed_in.txt" hello bye ;;
			cpp01/ex06) run_valgrind "$dir" "$(exe "$dir")" DEBUG ;;
			*) run_valgrind "$dir" "$(exe "$dir")" ;;
		esac
	done
	if phonebook_input | valgrind --quiet --error-exitcode=99 --leak-check=full \
		"$(exe cpp00/ex01)" >/dev/null 2>"$RUN_DIR/valgrind.log"; then
		pass 'valgrind cpp00/ex01 with input'
	else
		fail 'valgrind cpp00/ex01 with input'
		sed -n '1,60p' "$RUN_DIR/valgrind.log"
	fi
else
	printf 'SKIP valgrind (not installed)\n'
fi

printf 'SUMMARY pass=%d fail=%d\n' "$PASS" "$FAIL"
[ "$FAIL" -eq 0 ]
