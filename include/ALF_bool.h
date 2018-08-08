/** \file ALF_bool.h
* A simple boolean type implementation.

* Remark: This implementation is defined only if compiling C code, not C++.
**/

#ifndef ALF_bool_h
#define ALF_bool_h

#include "ALF_common.h"

#define ALF_bool_major_version 1
#define ALF_bool_minor_version 0
#define ALF_bool_patch_version 0
#define ALF_bool_version (ALF_bool_major_version, ALF_bool_minor_version)
#define ALF_bool_version_str ALF_STR(ALF_bool_major_version) "." ALF_STR(ALF_bool_minor_version) "." ALF_STR(ALF_bool_patch_version)


#ifndef __cplusplus
	/// The bool type. Has 2 posible values: true and false;
	typedef enum{
		false,
		true,
	} bool;
#endif /* __cplusplus */

#endif /* ALF_bool_h */
