#!/usr/bin/env python3
"""
Мини-CLI для ASCII-85:

$  cat raw.bin | python cli.py
Encode: -e <ASCII85>~>
Decoded: -d <RAW-байты>

Возврат: 0 — успех, 1 — decode() выкинул исключение.
"""

import sys

# ----------------------------------------------------------------------
# 1. импортируем обёртку, собранную CMake-ом (pybind11 или ctypes .so)
# ----------------------------------------------------------------------
try:
    import ascii85            # <build>/ascii85.{so,pyd,dll}
except ModuleNotFoundError as exc:
    print("ascii85 module not found:", exc, file=sys.stderr)
    sys.exit(2)

def main() -> None:
    # ------------------------------------------------------------------
    # 2. читаем «сырые» данные из stdin   (binary-режим!)
    # ------------------------------------------------------------------
    raw: bytes = sys.stdin.buffer.read()

    # ------------------------------------------------------------------
    # 3. encode → печать
    # ------------------------------------------------------------------
    encoded: str = ascii85.encode(raw)
    print(f"Encode: -e {encoded}")

    # ------------------------------------------------------------------
    # 4. decode → печать   |  ловим RuntimeError как признак «плохих данных»
    # ------------------------------------------------------------------
    try:
        decoded: bytes = ascii85.decode(encoded)
    except RuntimeError as e:
        print(f"Decoding error: {e}", file=sys.stderr)
        sys.exit(1)

    sys.stdout.buffer.write(b"Decoded: -d ")
    sys.stdout.buffer.write(decoded)
    sys.exit(0)

# ----------------------------------------------------------------------
if __name__ == "__main__":
    main()
