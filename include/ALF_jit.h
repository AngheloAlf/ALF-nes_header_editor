/** \file ALF_jit.h
* A simple cross-platform wraper to use JIT recompilation.
**/

#ifndef ALF_jit_h
#define ALF_jit_h

#include "ALF_common.h"

#define ALF_jit_major_version 1
#define ALF_jit_minor_version 0
#define ALF_jit_patch_version 0
#define ALF_jit_version ALF_MAKE_VERSION(ALF_jit_major_version, ALF_jit_minor_version)
#define ALF_jit_version_str ALF_STR(ALF_jit_major_version) "." ALF_STR(ALF_jit_minor_version) "." ALF_STR(ALF_jit_patch_version)

#include <stdint.h>

#ifdef _WIN32
#	include <windows.h>
	uint64_t ALF_PAGE_SIZE(void);
#else
#	include <unistd.h>
#	include <sys/mman.h>
#	define ALF_PAGE_SIZE() sysconf(_SC_PAGESIZE)
#endif

typedef struct {
    uint64_t position;
    /**
	 * Posible states:

	 * 0x0: Normal. Data can be inserted.

	 * 0x1: Ready for execution.
    **/
    uint8_t state;
    uint8_t *code;
} ALF_jit_buf;


/// Creates a buffer for use as a JIT.
/**
 * 
**/
ALF_jit_buf *ALF_jit_init(void);

/// Returns the aviable size for code.
/**
 * 
**/
uint64_t ALF_jit_get_avaible_size(ALF_jit_buf *handler);

/// Inserts a instruction in the code.
/**
 * 
**/
int ALF_jit_instruction(ALF_jit_buf *handler, uint64_t size, uint64_t ins);

/// Inserts an immediate (number) in the code.
/**
 * 
**/
int ALF_jit_immediate(ALF_jit_buf *handler, uint64_t size, const void *value);

/// Prepares the code to be executed.
/**
 * 
**/
int ALF_jit_finalize(ALF_jit_buf *handler);

/// Free the memory.
/**
 * 
**/
int ALF_jit_free(ALF_jit_buf *handler);

/// Returns the last error.
/**
 * 
**/
char *ALF_jit_get_error(void);

#endif /* ALF_jit_h */

