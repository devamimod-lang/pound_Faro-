#pragma once
#include <stdio.h>
typedef struct {} logger_t;
#define POUND_LOG_INFO(l,fmt,...) printf(fmt"\n", ##__VA_ARGS__)
#define POUND_LOG_WARN(l,fmt,...) printf("WARN: " fmt"\n", ##__VA_ARGS__)
#define POUND_LOG_ERROR(l,fmt,...) printf("ERROR: " fmt"\n", ##__VA_ARGS__)
#define POUND_LOG_DEBUG(l,fmt,...)
extern logger_t mem_logger, gpu_logger, hle_logger, loader_logger, io_logger, audio_logger, prof_logger, thread_logger;
