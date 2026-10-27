#!/usr/bin/env python3
"""Regression checks comparing optimized and original IR execution."""
import subprocess
from pathlib import Path

root = Path(__file__).resolve().parent
exe = root / "mini_ir"
if not exe.exists():
    raise SystemExit("Build first: g++ -std=c++17 -O2 -Wall -Wextra -Wpedantic main.cpp -o mini_ir")

def run(program, *flags):
    return subprocess.run([str(exe), *flags], input=program, text=True, capture_output=True)

def check(program, expected):
    a = run(program)
    b = run(program, "--no-opt")
    assert a.returncode == b.returncode == 0, (program, a.stderr, b.stderr)
    assert a.stdout.split("=== Output ===\n")[1] == expected, a.stdout
    assert b.stdout.split("=== Output ===\n")[1] == expected, b.stdout

check("a = 2 + 3\nb = a * 4\nprint b\n", "20\n")
check("x = 1\nx = x + 3\nprint x\n", "4\n")
check("unused = 5\nx = 2 * 3\nprint x\n", "6\n")
check("x = -5\ny = x * -2\nprint y\n", "10\n")
check("x = 1\nprint x\nx = 5\nprint x\n", "1\n5\n")
check("print 11\n", "11\n")
for invalid in ["print z\n", "x = 9223372036854775808\n", "x = 1 / 2\n", "x = 1 +\n"]:
    assert run(invalid).returncode != 0, invalid
for opts in [(), ("--no-opt",)]:
    assert run("x = 9223372036854775807\ny = x + 1\nprint y\n", *opts).returncode != 0
print("All checks passed.")
