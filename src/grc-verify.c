/**
 * @file
 * This file is part of Grenache Command Line Interface.
 *
 * Copyright (C) 2017, 2018, 2019, 2020 Davide Scola <davide@bitfinex.com>
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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAVE_FCNTL_H
# include <fcntl.h>
#endif

#include <ed25519.h>
#include "common.h"
#include "io.h"
#include "encode.h"


static char buffer[
  ED25519_MAX_HEX_SIZE +
  ED25519_SIGNATURE_SIZE +
  ED25519_PUBLIC_KEY_SIZE +
  1
];


int main(int argc, char *argv[]) {
  unsigned char *signature = (unsigned char *) (buffer + ED25519_MAX_HEX_SIZE + 1),
                *public_key = (unsigned char *) (signature + ED25519_SIGNATURE_SIZE);

  if (fcntl(SIGN_FILENO, F_GETFD) < 0 && errno == EBADF) {
#if !defined(NDEBUG)
    (void) fprintf(stderr, "error: cannot access file descriptor %d\n", SIGN_FILENO);
#endif

    exit(EXIT_FAILURE);
  }

  if (fcntl(PKEY_FILENO, F_GETFD) < 0 && errno == EBADF) {
#if !defined(NDEBUG)
    (void) fprintf(stderr, "error: cannot access file descriptor %d\n", PKEY_FILENO);
#endif

    exit(EXIT_FAILURE);
  }

  if (ioread(SIGN_FILENO, buffer, ED25519_SIGNATURE_SIZE << 1) < 0) {
#if !defined(NDEBUG)
    (void) fprintf(stderr, "error: cannot read signature from descriptor %d\n", SIGN_FILENO);
#endif

    exit(EXIT_FAILURE);
  }

  (void) decode(buffer, ED25519_SIGNATURE_SIZE << 1, signature);

  if (ioread(PKEY_FILENO, buffer, ED25519_PUBLIC_KEY_SIZE << 1) < 0) {
#if !defined(NDEBUG)
    (void) fprintf(stderr, "error: cannot read public key from descriptor %d\n", PKEY_FILENO);
#endif

    exit(EXIT_FAILURE);
  }

  (void) decode(buffer, ED25519_PUBLIC_KEY_SIZE << 1, public_key);

  while (*++argv != NULL) {
    if (**argv != '\0') {
      if (!ed25519_verify(signature, (unsigned char *)*argv, strlen(*argv), public_key)) {
#if !defined(NDEBUG)
        (void) fprintf(stderr, "NOT OK\n");
#endif

        exit(EXIT_FAILURE);
      }
    }
  }

#if !defined(NDEBUG)
  (void) fprintf(stdout, "OK\n");
#endif

  exit(EXIT_SUCCESS);
}
