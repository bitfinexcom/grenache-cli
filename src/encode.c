/**
 * @file
 * This file is part of Grenache Command Line Interface.
 *
 * Copyright (C) 2017 Davide Scola <davide@bitfinex.com>
 *
 * Licensed under the Apache License,  Version 2.0 (the "License"); you may
 * not use this file except in  compliance with the License. You may obtain
 * a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless  required by  applicable law  or agreed  to in  writing, software
 * distributed  under the  License  is  distributed on  an  "AS IS"  BASIS,
 * WITHOUT  WARRANTIES  OR  CONDITIONS  OF  ANY  KIND,  either  express  or
 * implied. See the License for the specific language governing permissions
 * and limitations under the License.
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "encode.h"


/**
 * Return decimal value from hexadecimal character.
 *
 * @param char ch
 *   The hexadecimal character (lowercase).
 *
 * @return unsigned char
 *   The decimal value or 0 in case of error.
 */
INLINE ALWAYS_INLINE unsigned char ord(char ch) {
  return (ch >= L'0' && ch <= L'9') ? (ch - L'0') : (
    (ch >= L'a' && ch <= L'f') ? (ch - L'a' + 10) : 0
  );
}

/**
 * Return hexadecimal character from decimal value.
 *
 * @param unsigned char ord
 *   The decimal value.
 *
 * @return char
 *   The hexadecimal character (lowercase).
 */
INLINE ALWAYS_INLINE char ch(unsigned char ord) {
  return ((ord & 0x0F) >= 0 && (ord & 0x0F) <= 9) ? ((ord & 0x0F) + L'0') : (
    (ord & 0x0F) + L'a' - 10
  );
}

/**
 * Encode byte string to hexadecimal sequence.
 *
 * @param const unsigned char *binary
 *   The input buffer of the binary string.
 * @param size_t length
 *   The size of the input buffer.
 * @param char *buffer
 *   The output buffer of the hexadecimal string.
 *
 * @return unsigned char *
 *   A pointer to the output buffer.
 */
char *encode(const unsigned char *binary, size_t length, char *buffer) {
  char *ptr_out = buffer;
  unsigned char *ptr_in = (unsigned char *)binary;

  while (ptr_in < binary + length) {
    *ptr_out++ = ch(*ptr_in >> 4);
    *ptr_out++ = ch(*ptr_in++);
  }

  *ptr_out = '\0';
  return buffer;
}

/**
 * Decode hexadecimal sequence to byte string.
 *
 * @param const char *buffer
 *   The input buffer of the hexadecimal string.
 * @param size_t length
 *   The size of the input buffer.
 * @param unsigned char *binary
 *   The output buffer of the binary string.
 *
 * @return unsigned char *
 *   A pointer to the output buffer.
 */
unsigned char *decode(const char *buffer, size_t length, unsigned char *binary) {
  char *ptr_in = (char *)buffer;
  unsigned char *ptr_out = binary;

  while (ptr_out < binary + (length >> 1)) {
    *ptr_out = (ord(*ptr_in++) << 4);
    *ptr_out++ |= ord(*ptr_in++);
  }

  return binary;
}
