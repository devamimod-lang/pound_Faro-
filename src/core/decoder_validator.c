#include "decoder_validator.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool run_decoder_cli(uint32_t instr) {
    char cmd[256];
    char out[1024];
    snprintf(cmd, sizeof(cmd), "/tmp/ballistic_release/bin/decoder_cli %08X", instr);
    FILE *pipe = popen(cmd, "r");
    if (!pipe) return false;
    if (!fgets(out, sizeof(out), pipe)) {
        pclose(pipe);
        return false;
    }
    pclose(pipe);
    return strstr(out, "Mnemonic:") != NULL;
}

bool decoder_validate_arm64_block(const uint8_t *code, size_t size) {
    if (!code || size % 4 != 0) return false;
    for (size_t i = 0; i < size; i += 4) {
        uint32_t instr = (uint32_t)code[i] | ((uint32_t)code[i+1] << 8) | ((uint32_t)code[i+2] << 16) | ((uint32_t)code[i+3] << 24);
        // Little endian to host big endian representation for decoder?
        // decoder expects big endian hex value
        uint32_t be = __builtin_bswap32(instr);
        if (!run_decoder_cli(be)) {
            POUND_LOG_WARN(&thread_logger, "Decoder validation failed at offset %zu", i);
            return false;
        }
    }
    return true;
}
