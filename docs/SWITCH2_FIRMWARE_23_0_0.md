# Switch 2 Firmware 23.0.0 Analysis

## Source
* Release: THZoria/NX_Firmware 23.0.0
* URL: https://github.com/THZoria/NX_Firmware/releases/tag/23.0.0
* Download: Firmware.23.0.0.zip
* SHA256 archive: 0d60b48630352b6b83cf48b49a5a063d6b1334cd14d2170028df602992e31755
* Extracted to: /tmp/firmware/

## Files present
* SystemVersion NCA FAT: 2377a6f36c2cc42c121cad2ffac236a9.nca
  * SHA256: 2377a6f36c2cc42c121cad2ffac236a9ef559e9a6478e9c7e275601b6c1c0024
* SystemVersion NCA exFAT: 16510dde912c6c6894d573f17006f113.nca
  * SHA256: 16510dde912c6c6894d573f17006f113d023a217f3e3fe8cab912dcc8ea7537f

## Verification
* Firmware matches current Switch 2 production version per Wikipedia: 23.0.0 released 2026-09-10

## Next steps for Pound
1. Dump NCA to extract SystemSettings and Services
2. Parse `system_settings` to obtain:
   * Boot config
   * Kernel SVC table offsets for T239
   * NVN driver version
3. Update `src/core/gpu/nvn_mmio.h` with real MMIO base addresses from firmware
4. Update `NVN_MMIO_MAP.md` with Switch 2 specific registers:
   * Doorbell base 0x10000000
   * NVN command submission doorbell offset
   * SM86 GPU registers extended range
   * T239 memory map: RAM 0x80000000-0xC0000000, Kernel 0x40000000, MMIO 0x10000000

## Tools needed
* hactool or nx-nca-parser for NCA extraction
* python-nx for parsing PFS0 partitions

## Notes
* Firmware 23.0.0 confirms Switch 2 is using same version numbering as Switch 1 for OS updates.
* Backward compatibility layer is present in system firmware.
