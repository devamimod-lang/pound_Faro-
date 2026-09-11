# Switch 2 Engineering Plan - Full Reverse Engineering

## Current State
- Memory model + Ballistic JIT integration
- NRO loader with decoder validation
- HLE syscalls stubs
- SM86 translator stub
- decoder_cli operational

## Next Steps - MMIO NVN GPU

### 1. MMIO Map
- 0x10000000 - 0x1000FFFF : GPU doorbell / command ring
- 0x10010000 - 0x1001FFFF : GPU registers NVN
- Implement switch2_memory_translate with region checks
- Trap write to MMIO -> dispatch to gpu_handle_mmio

### 2. GPU Handler
- File: src/core/gpu/nvn_mmio.h/.c
- Functions:
  - nvn_init
  - nvn_handle_write(addr, value, size)
  - nvn_handle_read(addr)
  - nvn_submit_command_buffer
- Map NVN commands to Vulkan

### 3. SM86 to SPIR-V Pipeline
- Pass1: predicados, UGPR
- Pass2: SPIR-V emission
- Vulkan backend with descriptor sets

### 4. HLE Services Expansion
- fs, ncm, sm, nvn
- Implement svcOpenFile, svcReadFile, svcWriteFile

### 5. Input / Audio / Storage
- Joy-Con 2 mouse mode
- Audio PCM via SDL
- SD card emulation

### 6. Profiling & Debugging
- Instruction counter
- Block cache stats
- Logs per syscall

## Milestones
M1: Boot menu Horizon
M2: Render tri-color
M3: Home menu navigable
M4: First game boot

## Risks
- MMIO reverse engineering
- Shader translation complexity
- Signature verification
