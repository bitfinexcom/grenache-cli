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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef HAVE_FCNTL_H
# include <fcntl.h>
#endif

#ifdef HAVE_BSD_STRING_H
# include <bsd/string.h>
#else
# include <string.h>
#endif

#ifdef HAVE_SYS_RANDOM_H
# include <sys/random.h>
#endif

#include <ed25519.h>
#include "common.h"
#include "io.h"
#include "encode.h"


static char buffer[
  ED25519_MAX_HEX_SIZE +
  ED25519_SEED_SIZE +
  ED25519_PUBLIC_KEY_SIZE +
  ED25519_SECRET_KEY_SIZE +
  1
];

int main(void) {
  unsigned char *seed = (unsigned char *) (buffer + ED25519_MAX_HEX_SIZE + 1),
                *public_key = (unsigned char *) (seed + ED25519_SEED_SIZE),
                *private_key = (unsigned char *) (public_key + ED25519_PUBLIC_KEY_SIZE);

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

#ifdef HAVE_GETENTROPY
  if (getentropy(seed, ED25519_SEED_SIZE) != ED25519_SEED_SIZE) {
#else
  if (ed25519_create_seed(seed) != 0) {
#endif
#if !defined(NDEBUG)
    (void) fprintf(stderr, "error: cannot initialize ed25519 seeder.\n");
#endif

    exit(EXIT_FAILURE);
  }

  ed25519_create_keypair(public_key, private_key, seed);
  explicit_bzero(seed, ED25519_SEED_SIZE);

  (void) encode(private_key, ED25519_SECRET_KEY_SIZE, buffer);

  if (iowrite(SKEY_FILENO, buffer, ED25519_SECRET_KEY_SIZE << 1) < 0) {
#if !defined(NDEBUG)
    (void) fprintf(stderr, "error: cannot write secret key to descriptor %d\n", SKEY_FILENO);
#endif

    exit(EXIT_FAILURE);
  }

  explicit_bzero(private_key, ED25519_SECRET_KEY_SIZE);
  (void) encode(public_key, ED25519_PUBLIC_KEY_SIZE, buffer);

  if (iowrite(PKEY_FILENO, buffer, ED25519_PUBLIC_KEY_SIZE << 1) < 0) {
#if !defined(NDEBUG)
    (void) fprintf(stderr, "error: cannot write public key to descriptor %d\n", PKEY_FILENO);
#endif

    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
