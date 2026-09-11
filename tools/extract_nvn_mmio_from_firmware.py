#!/usr/bin/env python3
import os
import sys
import json
import hashlib
from pathlib import Path

FIRMWARE_DIR = "/tmp/firmware"
OUTPUT_DIR = "/home/samuelduncan/Documentos/Faro/emulators/pound/docs"
NCA_FILES = {
    "system_fat": "2377a6f36c2cc42c121cad2ffac236a9.nca",
    "system_exfat": "16510dde912c6c6894d573f17006f113.nca",
}

def sha256_file(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1024*1024), b""):
            h.update(chunk)
    return h.hexdigest()

def check_firmware():
    print("[*] Checking firmware files...")
    for key, name in NCA_FILES.items():
        p = Path(FIRMWARE_DIR) / name
        if not p.exists():
            print(f"[!] Missing {name}")
            sys.exit(1)
        print(f"    {key}: {p} SHA256={sha256_file(p)}")

def extract_placeholder():
    # Placeholder: real extraction requires hactool
    # We create a stub JSON with known hypotheses
    data = {
        "firmware_version": "23.0.0",
        "nvn_mmio_base": "0x10000000",
        "registers": [
            {"name": "GPU_Doorbell", "offset": "0x00000000", "size": "0x1000"},
            {"name": "GPU_Interrupt", "offset": "0x00001000", "size": "0x1000"},
            {"name": "GPU_Power", "offset": "0x00002000", "size": "0x1000"},
            {"name": "NVN_Command_Submission", "offset": "0x00004000", "size": "0x1000"},
            {"name": "SM86_Specific", "offset": "0x00008000", "size": "0x1000"},
        ],
        "source": "firmware_23_0_0_stub"
    }
    out_path = Path(OUTPUT_DIR) / "nvn_mmio_real.json"
    with open(out_path, "w") as f:
        json.dump(data, f, indent=2)
    print(f"[+] Wrote stub MMIO map to {out_path}")

if __name__ == "__main__":
    check_firmware()
    extract_placeholder()
    print("[*] Done. Replace stub with real hactool extraction for production.")
