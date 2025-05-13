#!/usr/bin/env python3
import os
import subprocess
import sys
from pathlib import Path     

def run_cli(bin_path: Path, data: bytes) -> subprocess.CompletedProcess:
    """Запускает CLI, отдаёт data в stdin, возвращает CompletedProcess."""
    return subprocess.run(
        [bin_path],
        input=data,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )

def main() -> None:
    if len(sys.argv) != 2:
        print("Usage: tests_ascii85_cli.py <path-to-cli>", file=sys.stderr)
        sys.exit(1)

    cli = Path(sys.argv[1]).resolve()
    if not cli.is_file():
        print(f"CLI not found: {cli}", file=sys.stderr)
        sys.exit(1)

    #  корректные данные 
    raw = os.urandom(64)                      # сырые байты
    ok = run_cli(cli, raw)
    print("correct data: exit code =", ok.returncode)
    assert ok.returncode == 0, ok.stderr.decode()

    # некорректные данные 
    bad = b"abc{def~>"   
    err = run_cli(cli, bad)
    print("invalid data: exit code =", err.returncode)
    assert err.returncode != 0, "CLI must fail on bad input"

    print("python tests passed ✔︎")

if __name__ == "__main__":
    main()
