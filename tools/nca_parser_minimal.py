#!/usr/bin/env python3
import struct
from pathlib import Path

NCA_FILES = [
    "/tmp/firmware/2377a6f36c2cc42c121cad2ffac236a9.nca",
    "/tmp/firmware/16510dde912c6c6894d573f17006f113.nca",
]

def parse_nca_header(path):
    data = open(path, 'rb').read(0x200)
    if len(data) < 0x200:
        print(f"File too small: {path}")
        return
    magic = data[0:4]
    if magic != b'NCA3':
        print(f"Not NCA3: {magic}")
        return
    print(f"\n=== {Path(path).name} ===")
    print(f"Magic: {magic}")
    version = struct.unpack_from('<I', data, 0x4)[0]
    print(f"Version: {version}")
    # NCA header fields
    # Section info at offset 0x18...
    print("Header size: 0x200")
    # Print first 64 bytes hex
    hex_dump = ' '.join(f'{b:02X}' for b in data[:64])
    print(f"Hex dump start: {hex_dump}")

if __name__ == "__main__":
    for f in NCA_FILES:
        parse_nca_header(f)
