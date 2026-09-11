# Nintendo Switch 2 - Research for Emulation

## Hardware
- SoC: Nvidia Tegra T239 codename Drake
- CPU: Octa-core ARM Cortex-A78C @ 998 MHz undocked / 1101 MHz docked
- GPU: 1536 CUDA cores Ampere SM86 @ 561 MHz undocked / 1007 MHz docked
- RAM: 12 GB LPDDR5X 128-bit
- Storage: 256 GB UFS 3.1
- Display: 7.9" LCD 1080p 120 Hz HDR10 VRR
- Dock: HDMI 2.1 4K 60 Hz

## Memory Map Initial
- 0x80000000 - 0x8BFFFFFF : Main RAM ~12 GB
- 0x40000000 - 0x4FFFFFFF : Kernel / System
- 0x10000000 - 0x1FFFFFFF : MMIO GPU / HW
- 0x30000000 - 0x3FFFFFFF : I/O

## NRO Format
- Nintendo Relay Object, based on ELF.
- Header at offset 0 with magic 'NRO0'
- Segments: .dyn.text, .dyn.rodata, .dyn.bss, .dyn.data
- Relocations and dynamic imports.

## Horizon OS Syscalls
- svcCreateThread, svcStartThread, svcExitThread
- svcMapMemory, svcUnmapMemory
- svcReadWriteRegister
- svcSleepThread, svcOutputDisplay

## GPU
- NVN API, SM86 shaders.
- Target SPIR-V via rules in SM86_TO_SPIRV_RULES.md

## References
- Wikipedia Nintendo Switch 2
- yuzu / Ryujinx memory maps
- libnx, switchbrew
