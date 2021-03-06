/** \file ALF_IO.h
* Macros and functions concerning I/O (input/output)
**/

#ifndef ALF_IO_h
#define ALF_IO_h

#include "ALF_common.h"

#define ALF_IO_major_version 1
#define ALF_IO_minor_version 0
#define ALF_IO_patch_version 0
#define ALF_IO_version ALF_MAKE_VERSION(ALF_IO_major_version, ALF_IO_minor_version)
#define ALF_IO_version_str ALF_STR(ALF_IO_major_version) "." ALF_STR(ALF_IO_minor_version) "." ALF_STR(ALF_IO_patch_version)

#define ALF_ANSI_COLOR_BLACK	"\x1b[30m"
#define ALF_ANSI_COLOR_RED		"\x1b[31m"
#define ALF_ANSI_COLOR_GREEN	"\x1b[32m"
#define ALF_ANSI_COLOR_YELLOW	"\x1b[33m"
#define ALF_ANSI_COLOR_BLUE		"\x1b[34m"
#define ALF_ANSI_COLOR_MAGENTA	"\x1b[35m"
#define ALF_ANSI_COLOR_CYAN		"\x1b[36m"
#define ALF_ANSI_COLOR_WHITE	"\x1b[37m"
#define ALF_ANSI_COLOR_RESET	"\x1b[0m"

/// Python-like input of data.
/** 
 * This function prints out a message to screen (stdout).

 * Then asks for input via stdin, until a \\n is meet.

 * The input string is propety of the caller, and he have to free it.

 * Params: 

 * -const char *outMessage: The string to be printed.

 * Return value:

 * ->char *: The user input.

**/
char *ALF_raw_input(const char *outMessage);

/// Printfs a char like an hex number
/** Printfs an unsigned char like an hex number.

 * If the number is minor than 16 (0x10), it adds a 0 (zero) at the beggining of the number.

 * Params: 

 * -unsigned char character: The char to be printed.

 * Return value:

 * ->void
**/
void ALF_puthex(unsigned char character);

/// Printfs a colored block. The color depends on the input.
/** !! Doesn't work on Windows !!

* The color of the block depends of the character param. It should be a number between 0 and 7.

* Params:

* -unsigned char character: The color to be printed. It should be a number between 0 and 7.

* -char withNumber: Non-zero specifies if the param character should be printed in the colored block.

* Return value:

* ->void

**/
void ALF_printfColoredBlock(unsigned char character, char withNumber);

#endif /* ALF_LIB_IO */
