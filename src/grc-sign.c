/**
 * @file
 * This file is part of Grenache Command Line Interface.
 *
 * Copyright (C) 2017, 2018 Davide Scola <davide@bitfinex.com>
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

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif

#ifdef HAVE_FCNTL_H
# include <fcntl.h>
#endif

#ifdef HAVE_BSD_STRING_H
# include <bsd/string.h>
#endif

#include <ed25519.h>
#include "common.h"
#include "io.h"
#include "encode.h"


static char buffer[
  ED25519_MAX_HEX_SIZE +
  ED25519_SIGNATURE_SIZE +
  ED25519_PUBLIC_KEY_SIZE +
  ED25519_SECRET_KEY_SIZE +
  1
];


int main(int argc, char *argv[]) {
  unsigned char *signature = (unsigned char *) (buffer + ED25519_MAX_HEX_SIZE + 1),
                *public_key = (unsigned char *) (signature + ED25519_SIGNATURE_SIZE),
                *private_key = (unsigned char *) (public_key + ED25519_PUBLIC_KEY_SIZE);

  if (argc < 2) {
#if !defined(NDEBUG)
    (void) fprintf(stderr, "usage: grc-sign <message> [, message[, message[, ...]]]\n");
#endif

    exit(EXIT_FAILURE);
  }

  if (fcntl(SKEY_FILENO, F_GETFD) < 0 && errno == EBADF) {
#if !defined(NDEBUG)
    (void) fprintf(stderr, "error: cannot access file descriptor %d\n", SKEY_FILENO);
#endif

    exit(EXIT_FAILURE);
  }

  if (fcntl(PKEY_FILENO, F_GETFD) < 0 && errno == EBADF) {
#if !defined(NDEBUG)
    (void) fprintf(stderr, "error: cannot access file descriptor %d\n", PKEY_FILENO);
#endif

    exit(EXIT_FAILURE);
  }

  if (ioread(SKEY_FILENO, buffer, ED25519_SECRET_KEY_SIZE << 1) < 0) {
#if !defined(NDEBUG)
    (void) fprintf(stderr, "error: cannot read secret key from descriptor %d\n", SKEY_FILENO);
#endif

    exit(EXIT_FAILURE);
  }

  (void) decode(buffer, ED25519_SECRET_KEY_SIZE << 1, private_key);
  explicit_bzero(buffer, ED25519_SECRET_KEY_SIZE << 1);

  if (ioread(PKEY_FILENO, buffer, ED25519_PUBLIC_KEY_SIZE << 1) < 0) {
#if !defined(NDEBUG)
    (void) fprintf(stderr, "error: cannot read public key from descriptor %d\n", PKEY_FILENO);
#endif

    exit(EXIT_FAILURE);
  }

  (void) decode(buffer, ED25519_PUBLIC_KEY_SIZE << 1, public_key);

  while (*++argv != NULL) {
    if (**argv != '\0') {
      ed25519_sign(signature, (unsigned char *)*argv, strlen(*argv), public_key, private_key);
      iowrite(STDOUT_FILENO, encode(signature, ED25519_SIGNATURE_SIZE, buffer), ED25519_SIGNATURE_SIZE << 1);
    }
  }

  explicit_bzero(private_key, ED25519_SECRET_KEY_SIZE);
  exit(EXIT_SUCCESS);
}
