/**
 * @file
 * This file is part of Grenache Command Line Interface.
 *
 * Copyright (C) 2017-2021 Davide Scola <davide@bitfinex.com>
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

#ifndef _ENCODE_H
#define _ENCODE_H


#undef ED25519_MAX_KEY_SIZE
#define ED25519_MAX_KEY_SIZE (MAX(ED25519_SECRET_KEY_SIZE,ED25519_PUBLIC_KEY_SIZE))

#undef ED25519_MAX_HEX_SIZE
#define ED25519_MAX_HEX_SIZE (MAX(ED25519_MAX_KEY_SIZE,ED25519_SIGNATURE_SIZE) << 1)


#ifdef __cplusplus
extern          "C" {
#endif                          /* __cplusplus */

    char *          encode(const unsigned char *, size_t, char *);
    unsigned char * decode(const char *, size_t, unsigned char *);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _ENCODE_H */
