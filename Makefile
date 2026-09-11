CC=gcc
CFLAGS=-I src -O2 -Wall
STUBS=src/core/memory/switch2_memory.c src/core/nro_loader.c src/core/gpu/nvn_mmio.c src/core/gpu/vulkan_nvn_bridge.c src/core/gpu/nvn_command.c src/core/profiler/profiler.c
all: /tmp/pound_run
/tmp/pound_run: tests/run_nro_smoke.c $(STUBS)
	$(CC) $(CFLAGS) tests/run_nro_smoke.c $(STUBS) -o /tmp/pound_run
run:
	/tmp/pound_run
clean:
	rm -f /tmp/pound_run
