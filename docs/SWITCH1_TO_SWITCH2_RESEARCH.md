# Switch 1 → Switch 2 Reverse Engineering Baseline

## Switch 1 Hardware Baseline
- SoC: Nvidia Tegra X1 codename Erista / Mariko
- CPU: Quad-core ARM Cortex-A57 @1.02 GHz
- GPU: 256 CUDA Maxwell SM75? Actually Maxwell 256 cores
- RAM: 4 GB LPDDR4
- Storage: eMMC 32/64 GB
- OS: Horizon OS
- GPU API: NVN, Maxwell SM75

## Memory Map Switch 1 (from community research)
- 0x80000000 - 0x8FFFFFFF : Main RAM 4 GB
- 0x40000000 - 0x4FFFFFFF : Kernel
- 0x10000000 - 0x1FFFFFFF : MMIO GPU / HW
- 0x30000000 - 0x3FFFFFFF : I/O

## NRO / ELF
- Nintendo Relay Object based on ELF64
- Segments: .dyn.text, .dyn.rodata, .dyn.data, .dyn.bss
- Relocations for imports

## Horizon Services
- svcCreateThread, svcStartThread, svcExitThread
- svcMapMemory, svcUnmapMemory
- svcReadWriteRegister
- svcOutputDisplay
- svcSleepThread

## NVN GPU
- Maxwell SM75 shaders
- Commands via MMIO doorbell
- Memory management via carveout

## Switch 2 Hypotheses
- SoC: Nvidia Tegra T239 Drake
- CPU: Octa-core ARM Cortex-A78C
- GPU: Ampere SM86
- RAM: 12 GB LPDDR5X
- Memory map likely similar with larger RAM
- NVN API evolved, MMIO offsets similar but expanded
- Horizon OS evolved, same syscall numbers

## Sources
- yuzu / Ryujinx / libnx / switchbrew
- Tegra X1 docs
- Nvidia Maxwell / Ampere programming guides
