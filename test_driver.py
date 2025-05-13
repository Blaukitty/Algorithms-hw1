import base64
import os
import subprocess
import sys
from pathlib import Path

def run_cli(bin_path: Path, data: bytes) -> int:
    """Запускает бинарь, передаёт data в stdin, возвращает код выхода."""
    res = subprocess.run([bin_path],
                         input=data,
                         stdout=subprocess.PIPE,
                         stderr=subprocess.PIPE)
    return res.returncode

def main() -> None:
    if len(sys.argv) < 2:
        print("Usage: tests_ascii85_cli.py <path-to-cli>", file=sys.stderr)
        sys.exit(1)

    cli = Path(sys.argv[1]).resolve()
    if not cli.is_file():
        print(f"CLI not found: {cli}", file=sys.stderr)
        sys.exit(1)

    # корректные данные
    raw = os.urandom(64)
    # ascii85 = base64.a85encode(raw)
    code_ok = run_cli(BIN, raw)
    print("correct data: exit code =", code_ok.returncode)
    assert code_ok.returncode ==0, code_ok.returncode()
    
    # некорректные данные 
    bad = b"!!!***invalid***data***!!!~>"  # запрещённые символы, но с "~>"
    code_bad = run_cli(BIN, bad)
    print("invalid data: exit code =", code_bad)
    assert code_bad.returncode !=0, "CLi должен был упасть"

    print("python tests passed")

if __name__ == "__main__":
    main()
