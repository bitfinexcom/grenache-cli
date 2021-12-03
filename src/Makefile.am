############################################################################
# This file is part of Grenache Command Line Interface.                    #
#                                                                          #
# Copyright (C) 2017-2021 Davide Scola <davide@bitfinex.com>               #
#                                                                          #
# Licensed under the Apache License,  Version 2.0 (the "License"); you may #
# not use this file except in  compliance with the License. You may obtain #
# a copy of the License at                                                 #
#                                                                          #
#       http://www.apache.org/licenses/LICENSE-2.0                         #
#                                                                          #
# Unless  required by  applicable law  or agreed  to in  writing, software #
# distributed  under the  License  is  distributed on  an  "AS IS"  BASIS, #
# WITHOUT  WARRANTIES  OR  CONDITIONS  OF  ANY  KIND,  either  express  or #
# implied. See the License for the specific language governing permissions #
# and limitations under the License.                                       #
############################################################################

CFLAGS += $(WARN_CFLAGS)
LDFLAGS += $(WARN_LDFLAGS)
CPPFLAGS += -I$(top_srcdir)/include


bin_PROGRAMS = \
grc-keygen \
grc-sign \
grc-verify

bin_SCRIPTS = \
grenache-put \
grenache-get \
grenache-keygen \
grenache-lookup \
grenache-announce

noinst_LTLIBRARIES = \
libed25519.la \
libcommon.la


libed25519_la_SOURCES = \
../ed25519/src/add_scalar.c \
../ed25519/src/ed25519.h \
../ed25519/src/fe.h \
../ed25519/src/fe.c \
../ed25519/src/fixedint.h \
../ed25519/src/ge.h \
../ed25519/src/ge.c \
../ed25519/src/key_exchange.c \
../ed25519/src/keypair.c \
../ed25519/src/precomp_data.h \
../ed25519/src/sc.h \
../ed25519/src/sc.c \
../ed25519/src/seed.c \
../ed25519/src/sha512.h \
../ed25519/src/sha512.c \
../ed25519/src/sign.c \
../ed25519/src/verify.c


libcommon_la_SOURCES = \
io.c \
encode.c


grc_keygen_SOURCES = \
grc-keygen.c

grc_keygen_CPPFLAGS = \
-I$(top_srcdir)/ed25519/src

grc_keygen_LDADD = \
libcommon.la \
libed25519.la


grc_sign_SOURCES = \
grc-sign.c

grc_sign_CPPFLAGS = \
-I$(top_srcdir)/ed25519/src

grc_sign_LDADD = \
libcommon.la \
libed25519.la


grc_verify_SOURCES = \
grc-verify.c

grc_verify_CPPFLAGS = \
-I$(top_srcdir)/ed25519/src

grc_verify_LDADD = \
libcommon.la \
libed25519.la
