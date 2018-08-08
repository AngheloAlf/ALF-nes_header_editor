/** \file ALF_bit.h
* Some bitwise operations via macros.
**/

#ifndef ALF_bit_h
#define ALF_bit_h

#include "ALF_common.h"

#define ALF_bit_major_version 1
#define ALF_bit_minor_version 0
#define ALF_bit_patch_version 0
#define ALF_bit_version ALF_MAKE_VERSION(ALF_bit_major_version, ALF_bit_minor_version)
#define ALF_bit_version_str ALF_STR(ALF_bit_major_version) "." ALF_STR(ALF_bit_minor_version) "." ALF_STR(ALF_bit_patch_version)

/// Bit 0
#define ALF_BIT_0   0x1  // 0b00000001
/// Bit 1
#define ALF_BIT_1   0x2  // 0b00000010
/// Bit 2
#define ALF_BIT_2   0x4  // 0b00000100
/// Bit 3
#define ALF_BIT_3   0x8  // 0b00001000
/// Bit 4
#define ALF_BIT_4   0x10 // 0b00010000
/// Bit 5
#define ALF_BIT_5   0x20 // 0b00100000
/// Bit 6
#define ALF_BIT_6   0x40 // 0b01000000
/// Bit 7
#define ALF_BIT_7   0x80 // 0b10000000

/// Upper half of a byte
#define ALF_HIGH_NIBBLE 0xF0 // 0b11110000
/// Lower half of a byte
#define ALF_LOW_NIBBLE  0x0F // 0b00001111

/// Returns the value at that exact bit position
#define ALF_GET_BIT(value, bit) ((value & (0x1<<bit)) >> bit)
/// Returns the value at that exact byte position
#define ALF_GET_BYTE(value, byte) ((value & (0xFF<<(byte*0x8))) >> (byte*0x8))

#endif /* ALF_bit_h */
