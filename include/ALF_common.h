/** \file ALF_common.h
* The common interface. 
* Has any definition that will be used in more than one lib file.
**/

#ifndef ALF_common_h
#define ALF_common_h

#define _ALF_STR(x) #x

/// Converts things to string at compile-time.
#define ALF_STR(x) _ALF_STR(x)

#define _ALF_NUMBER_LENGTH(x) (sizeof(ALF_STR(x)) - 1)

/// Returns the amount of digits in a number.
#define ALF_NUMBER_LENGTH(x) _ALF_NUMBER_LENGTH(x)


#define ALF_CONC_(A, B) A##B
#define ALF_CONC(A, B) ALF_CONC_(A, B)

#define ALF_MAKE_VERSION(x, y) ALF_CONC(x, ALF_CONC(.,y))

#define ALF_common_major_version 1
#define ALF_common_minor_version 0
#define ALF_common_patch_version 0
#define ALF_common_version ALF_MAKE_VERSION(ALF_common_major_version, ALF_common_minor_version)
#define ALF_common_version_str ALF_STR(ALF_common_major_version) "." ALF_STR(ALF_common_minor_version) "." ALF_STR(ALF_common_patch_version)


#endif /* ALF_common_h */
