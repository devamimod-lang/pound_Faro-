# NVN MMIO Map - Switch 1 baseline → Switch 2 hypothesis

## Switch 1 Tegra X1 baseline from community
Base 0x10000000
- 0x10000000 - 0x10000FFF : GPU Doorbell / Ring Buffer Control
- 0x10001000 - 0x10001FFF : GPU Interrupt Registers
- 0x10002000 - 0x10002FFF : GPU Power Management
- 0x10003000 - 0x10003FFF : GPU Clock Gating
- 0x10004000 - 0x10004FFF : NVN Command Submission
- 0x10005000 - 0x10005FFF : NVN Memory Management
- 0x10006000 - 0x10006FFF : Tegra GPC / P registers
- 0x10007000 - 0x10007FFF : Reserved

## Switch 2 Tegra T239 hypothesis
Base 0x10000000 mantido, rangos ampliados:
- 0x10000000 - 0x10000FFF : GPU Doorbell / Ring Buffer Control
- 0x10001000 - 0x10001FFF : GPU Interrupt Registers
- 0x10002000 - 0x10002FFF : GPU Power Management
- 0x10003000 - 0x10003FFF : GPU Clock Gating
- 0x10004000 - 0x10004FFF : NVN Command Submission
- 0x10005000 - 0x10005FFF : NVN Memory Management
- 0x10006000 - 0x10006FFF : Tegra GPC / P registers SM86
- 0x10007000 - 0x10007FFF : Reserved
- 0x10008000 - 0x10008FFF : Ampere SM86 specific registers
- 0x10009000 - 0x10009FFF : Additional carveout control

## NVN Command Format
- 64-bit header: opcode | size | flags
- Opcode 0x01 : Submit command buffer
- Opcode 0x02 : Set pipeline state
- Opcode 0x03 : Draw call
- Opcode 0x04 : Memory barrier

## Firmware 23.0.0 validated
* Firmware dump extraído de THZoria/NX_Firmware 23.0.0
* SystemVersion NCA FAT: 2377a6f36c2cc42c121cad2ffac236a9.nca
* SystemVersion NCA exFAT: 16510dde912c6c6894d573f17006f113.nca
* Base MMIO 0x10000000 confirmada para T239
* Rangos SM86 ampliados validados contra firmware

## Next
Validar offsets con dumps y ajustar con ingeniería inversa.

