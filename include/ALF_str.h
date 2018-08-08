/** \file ALF_str.h
* Macros and functions concerning strings operations
**/

#ifndef ALF_str_h
#define ALF_str_h

#include "ALF_common.h"

#define ALF_str_major_version 1
#define ALF_str_minor_version 0
#define ALF_str_patch_version 0
#define ALF_str_version ALF_MAKE_VERSION(ALF_str_major_version, ALF_str_minor_version)
#define ALF_str_version_str ALF_STR(ALF_str_major_version) "." ALF_STR(ALF_str_minor_version) "." ALF_STR(ALF_str_patch_version)

#include <stdlib.h>

/// Python-like string.split()
/**
 * Params:

 * -char *string: The string to be splited.

 * -char *delimiters: The delimiter that is going to split the string.

 * Return value:

 * ->char **: An 'array' of strings. Each string is a part of the original string param.

**/
char **ALF_split(char *string, const char *delimiters);

///
void ALF_charCopy(unsigned char* dst, const unsigned char* src, size_t size);

///
unsigned char *ALF_newCharFromIndex(const unsigned char* src, size_t size, size_t start);

/// 
char* ALF_changeExtension(const char* word, const char* newExt, int lenExt);

#endif /* ALF_str_h */
