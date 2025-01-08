/**
 * @file
 * This file is part of Grenache Command Line Interface.
 *
 * Copyright (C) 2017-2025 Davide Scola <davide@bitfinex.com>
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

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif

#include "common.h"
#include "io.h"


/**
 * Perform an I/O operation.
 *
 * @param ioop_t op
 *   The I/O operation.
 * @param int fd
 *   The file descriptor.
 * @param char *buffer
 *   The buffer to operate on.
 * @param size_t length
 *   On how many bytes to operate.
 *
 * @return int
 *   The number of bytes it was operated on, -1 otherwise.
 */
static INLINE ALWAYS_INLINE ssize_t ioop(ioop_t op, int fd, char *buffer, size_t length) {
  ssize_t size;
  size_t nbytes = 0;

  while (nbytes < length) {
    if ((size = op(fd, buffer + nbytes, length - nbytes)) < 1) {
      /* Return error even when EINTR. */
      return -1;
    }

    nbytes += size;
  }

  return nbytes;
}


/**
 * Read from a file descriptor.
 *
 * @param int fd
 *   The file descriptor.
 * @param char *buffer
 *   The buffer to fill.
 * @param size_t length
 *   How many bytes to read.
 *
 * @return int
 *   0 if all the bytes have been read, -1 otherwise.
 */
int ioread(int fd, char *buffer, size_t length) {
  ssize_t nread;

  if ((nread = ioop(read, fd, buffer, length)) == -1) {
    return -1;
  }

  *(buffer + nread) = '\0';
  return 0;
}

/**
 * Write to a file descriptor.
 *
 * @param int fd
 *   The file descriptor.
 * @param char *buffer
 *   The buffer to write.
 * @param size_t length
 *   How many bytes to write.
 *
 * @return int
 *   0 if all bytes have been written, -1 otherwise.
 */
int iowrite(int fd, char *buffer, size_t length) {
  if (ioop((ioop_t) write, fd, buffer, length) == -1) {
    return -1;
  }

  (void) fsync(fd);
  return 0;
}
