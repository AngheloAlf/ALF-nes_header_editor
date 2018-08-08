/** \file ALF_OS.h
 * A Operative System detector using the defined macros.

 * This library tries to detect differents operative systems using the macros defined by the compiler.

 * Any  function return non-zero if at compile time detected it was compiled on the system it think it is.

 * 0 Otherwise.

 * Some alternative macros are implemented, their function is comodity for the dev.

**/

#ifndef ALF_OS_h
#define ALF_OS_h

#include "ALF_common.h"

#define ALF_OS_major_version 1
#define ALF_OS_minor_version 0
#define ALF_OS_patch_version 0
#define ALF_OS_version ALF_MAKE_VERSION(ALF_OS_major_version, ALF_OS_minor_version)
#define ALF_OS_version_str ALF_STR(ALF_OS_major_version) "." ALF_STR(ALF_OS_minor_version) "." ALF_STR(ALF_OS_patch_version)

/// Detects the macro _WIN32
char ALF_isWindows(void);

/// Detects the macro __APPLE__
char ALF_isOSX(void);
/// Just another name for ALF_isOSX()
#define ALF_isMac() ALF_isOSX()

/// Detects the macro __linux__
char ALF_isLinux(void);

/// Detects if is a WIN32 and not a WIN64
char ALF_isWindows32(void);
/// Detects _WIN64
char ALF_isWindows64(void);

/// Detects __unix__
char ALF_isUnix(void);
/// Detects if defined __unix__ but is not a linux, apple, or android machine.
char ALF_isUnixOther(void);

/// Detects _POSIX_VERSION
char ALF_isPosix(void);

/// Detects __ANDROID__
char ALF_isAndroid(void);

/// Detects iOS (iPhone)
char ALF_isIOS(void);
/// Other name for ALF_isIOS()
#define ALF_isIphone() ALF_isIOS()
/// Detects TARGET_IPHONE_SIMULATOR
char ALF_isIOSSimulator(void);
/// Other name for ALF_isIOSSimulator()
#define ALF_isIphoneSimulator() ALF_isIOSSimulator()
/// Detects TARGET_OS_MAC
char ALF_isOSXOther(void);
/// Other name for ALF_isOSXOther()
#define ALF_isMACOther() ALF_isOSXOther()
/// Detect is Apple product, but not detected by the others macros. 
char ALF_isAppleOther(void);

/// Detects FreeBSD
char ALF_isFreeBSD(void);

/// Detects the not detected by this library.
/**

 * Returns 1 only if none of the others are detected by this library.

 * 0 Otherwise.
**/
char ALF_isOther(void);

/* OS DETECTOR */
/*
#ifdef __WIN32__
    //define something for Windows (32-bit and 64-bit, this part is common)
    #include <windows.h>
    // #include <winbase.h>
    // #include <windef.h>

    #ifdef __WIN64__
        //define something for Windows (64-bit only)
    #else
        //define something for Windows (32-bit only)
    #endif

#elif __unix__ 
    // Unix

    #if __APPLE__
        #include "TargetConditionals.h"
        #if TARGET_IPHONE_SIMULATOR
            // iOS Simulator
        #elif TARGET_OS_IPHONE
            // iOS device
        #elif TARGET_OS_MAC
            // Other kinds of Mac OS
        #else
            #error "Unknown Apple platform"
        #endif
    #elif defined(__ANDROID__)
        // Android
    #elif __linux__
         // linux

    #include <unistd.h>
    #elif defined(_POSIX_VERSION)
        // POSIX
        #error "Supported?"

    #endif
#else
    #error "Unknown compiler"
#endif
*/

#endif /* ALF_OS_h */
