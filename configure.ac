dnl This file is part of Grenache Command Line Interface.
dnl
dnl Copyright (C) 2017, 2018, 2019, 2020 Davide Scola <davide@bitfinex.com>
dnl
dnl Licensed under the Apache License,  Version 2.0 (the "License"); you may
dnl not use this file except in  compliance with the License. You may obtain
dnl a copy of the License at
dnl
dnl       http://www.apache.org/licenses/LICENSE-2.0
dnl
dnl Unless  required by  applicable law  or agreed  to in  writing, software
dnl distributed  under the  License  is  distributed on  an  "AS IS"  BASIS,
dnl WITHOUT  WARRANTIES  OR  CONDITIONS  OF  ANY  KIND,  either  express  or
dnl implied. See the License for the specific language governing permissions
dnl and limitations under the License.

AC_PREREQ(2.69)
AC_INIT([grenache-cli], [0.7.1], [davide@bitfinex.com])

AC_SUBST([VERSION], [0.7.1])
AC_SUBST([SB], [`$srcdir/shtool echo -n -e %B`])
AC_SUBST([EB], [`$srcdir/shtool echo -n -e %b`])

AC_COPYRIGHT([Copyright (c) 2017, 2018, 2019, 2020 Davide Scola, <davide@bitfinex.com>
This configure script may be copied, distributed and modified under the
terms of the Apache License 2.0 license; see LICENSE for more details.])

dnl --------------------------------------------------------------------
dnl Basic configuration
dnl --------------------------------------------------------------------
AX_MSG_BOLD([Configuring grenache-cli $VERSION])

AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_AUX_DIR([build-aux])

AC_CONFIG_SRCDIR([include/io.h])
AC_CONFIG_HEADERS([config.h])

AC_CANONICAL_HOST
AM_INIT_AUTOMAKE([foreign no-dist-gzip dist-xz])
AM_EXTRA_RECURSIVE_TARGETS([install-man])

AX_IS_RELEASE([git-directory])
AX_CHECK_ENABLE_DEBUG
AM_MAINTAINER_MODE
AX_GENERATE_CHANGELOG

dnl --------------------------------------------------------------------
dnl Checks for programs.
dnl --------------------------------------------------------------------
AX_MSG_BOLD([Checking for required programs])

LT_INIT
AC_PROG_CC
AC_PROG_CPP
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
AC_PROG_AWK
AM_MISSING_PROG([HELP2MAN], [help2man])

AX_PROG_JQ
AX_PROG_CAT
AX_PROG_XXD
AX_PROG_DATE
AX_PROG_CURL
AX_PROG_MKDIR
AX_PROG_GETOPT
AX_PROG_UUIDGEN
AX_PROG_SHA1SUM
AX_PROG_READLINK

dnl --------------------------------------------------------------------
dnl Checks for libraries.
dnl --------------------------------------------------------------------
AX_MSG_BOLD([Checking for required libraries])

AC_CHECK_HEADERS([bsd/string.h], [
  PKG_CHECK_MODULES([libbsd], [libbsd >= 0.8.0], [
    AX_SAVE_FLAGS([ac_cv_libbsd])

    AX_APPEND_FLAG([${libbsd_LIBS}], [LIBS])
    AX_APPEND_FLAG([${libbsd_CFLAGS}], [CFLAGS])

    AC_MSG_CHECKING([if libbsd can be linked correctly])

    AC_LINK_IFELSE([AC_LANG_SOURCE([[int main(void) { return 0; }]])], [
      AC_MSG_RESULT([yes])

      AX_APPEND_FLAG([${libbsd_LIBS}], [LLDP_LDFLAGS])
      AX_APPEND_FLAG([${libbsd_CFLAGS}], [LLDP_CFLAGS])
    ], [
      AC_MSG_RESULT([no])
      AX_RESTORE_FLAGS([ac_cv_libbsd])
    ])
  ])
])

dnl --------------------------------------------------------------------
dnl Checks for header files.
dnl --------------------------------------------------------------------
AX_MSG_BOLD([Checking for required header files])

AC_HEADER_STDC
AC_CHECK_HEADERS([sys/random.h])
AC_CHECK_HEADERS([fcntl.h unistd.h], [], [
  AC_MSG_ERROR([missing $ac_header vital header file])
])

dnl --------------------------------------------------------------------
dnl Checks for typedefs, structures, and compiler characteristics.
dnl --------------------------------------------------------------------
AX_MSG_BOLD([Checking for compiler characteristics])

AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AX_C99_INLINE
AX_GCC_FUNC_ATTRIBUTE([always_inline])
AX_COMPILER_FLAGS
AX_GCC_ARCHFLAG

dnl --------------------------------------------------------------------
dnl Checks for library functions.
dnl --------------------------------------------------------------------
AX_MSG_BOLD([Checking for required library functions])

AC_CHECK_FUNCS([getentropy], [
  CPPFLAGS="-DED25519_NO_SEED ${CPPFLAGS}"
])

AC_CHECK_FUNCS([explicit_bzero], [], [
  AC_MSG_ERROR([missing $ac_func vital function])
])

dnl --------------------------------------------------------------------
dnl Checks for user defined options.
dnl --------------------------------------------------------------------
AX_MSG_BOLD([Checking user defined options])

AC_ARG_ENABLE([x86-features], AC_HELP_STRING([--enable-x86-features],
  [Enable the x86 features check @<:@default=yes@:>@]),
  [ax_cv_enable_x86_features="${enableval}"], [ax_cv_enable_x86_features='yes'])

AC_MSG_CHECKING([whether you want to enable the x86 features check])

if test "x${ax_cv_enable_x86_features}" = 'xyes'; then
  AC_MSG_RESULT([yes])

  case "${host}" in
    i?86-* | amd64-* | x86_64-*)
      AX_CHECK_X86_FEATURES
      ;;
    *)
      ax_cv_enable_x86_features='no'
      AC_MSG_WARN([the x86 features check cannot be performed])
      ;;
  esac
else
  AC_MSG_RESULT([no])
  ax_cv_enable_x86_features='no'
fi

AX_DEFINE_DESCRIPTOR([SKEY_FILENO], [secret key], [6])
AX_DEFINE_DESCRIPTOR([PKEY_FILENO], [public key], [7])
AX_DEFINE_DESCRIPTOR([SIGN_FILENO], [signature], [8])
AX_DEFINE_SIZE([ED25519_SEED_SIZE], [ed25519 seed], [32])
AX_DEFINE_SIZE([ED25519_SIGNATURE_SIZE], [ed25519 signature], [64])
AX_DEFINE_SIZE([ED25519_PUBLIC_KEY_SIZE], [ed25519 public key], [32])
AX_DEFINE_SIZE([ED25519_SECRET_KEY_SIZE], [ed25519 secret key], [64])

dnl --------------------------------------------------------------------
dnl Output.
dnl --------------------------------------------------------------------
AX_MSG_BOLD([Writing output files])

AC_CONFIG_FILES([ \
  Makefile \
  doc/Makefile \
  m4/Makefile \
  include/Makefile \
  src/Makefile \
  src/grenache-put \
  src/grenache-get \
  src/grenache-keygen \
  src/grenache-lookup \
  src/grenache-announce \
  tests/Makefile \
  tests/sign-test-vector-1.sh \
  tests/sign-test-vector-2.sh \
  tests/verify-test-vector-1.sh \
  tests/verify-test-vector-2.sh \
])

AC_OUTPUT

dnl --------------------------------------------------------------------
dnl Output the configuration summary
dnl --------------------------------------------------------------------
AX_MSG_BOLD([grenache-cli $VERSION has been configured as follow])
AX_MSG_OPTION([Configure finished: to build type], [make])
AC_MSG_RESULT([==================================================])
AC_MSG_RESULT
   AX_MSG_OPTION([ Install prefix: ], [${prefix}])
AC_MSG_RESULT
AC_MSG_RESULT
   AX_MSG_OPTION([Functions :])
AC_MSG_RESULT
   AX_MSG_OPTION([ getentropy .............. ], [${ac_cv_func_getentropy}])
   AX_MSG_OPTION([ explicit_bzero .......... ], [${ac_cv_func_explicit_bzero}])
AC_MSG_RESULT
   AX_MSG_OPTION([Functionalities :])
AC_MSG_RESULT
   AX_MSG_OPTION([ Release ................. ], [${ax_is_release}])
   AX_MSG_OPTION([ Debug code .............. ], [${ax_enable_debug}])
   AX_MSG_OPTION([ Enable x86 features ..... ], [${ax_cv_enable_x86_features}])
   AX_MSG_OPTION([ Warnings ................ ], [${ax_enable_compile_warnings}])
   AX_MSG_OPTION([ Secret Key Descriptor ... ], [${SKEY_FILENO}])
   AX_MSG_OPTION([ Public Key Descriptor ... ], [${PKEY_FILENO}])
   AX_MSG_OPTION([ Signature Descriptor .... ], [${SIGN_FILENO}])
   AX_MSG_OPTION([ Ed25519 Seed Size ....... ], [${ED25519_SEED_SIZE} bytes])
   AX_MSG_OPTION([ Ed25519 Signature Size .. ], [${ED25519_SIGNATURE_SIZE} bytes])
   AX_MSG_OPTION([ Ed25519 Public Key Size . ], [${ED25519_PUBLIC_KEY_SIZE} bytes])
   AX_MSG_OPTION([ Ed25519 Secret Key Size . ], [${ED25519_SECRET_KEY_SIZE} bytes])
AC_MSG_RESULT
   AX_MSG_OPTION([Tools :])
AC_MSG_RESULT
   AX_MSG_OPTION([ jq ...................... ], [${JQ}])
   AX_MSG_OPTION([ cat ..................... ], [${CAT}])
   AX_MSG_OPTION([ xxd ..................... ], [${XXD}])
   AX_MSG_OPTION([ date .................... ], [${DATE}])
   AX_MSG_OPTION([ curl .................... ], [${CURL}])
   AX_MSG_OPTION([ mkdir ................... ], [${MKDIR}])
   AX_MSG_OPTION([ getopt .................. ], [${GETOPT}])
   AX_MSG_OPTION([ uuidgen ................. ], [${UUIDGEN}])
   AX_MSG_OPTION([ sha1sum ................. ], [${SHA1SUM}])
   AX_MSG_OPTION([ readlink ................ ], [${READLINK}])
AC_MSG_RESULT
AC_MSG_RESULT([==================================================])
AX_MSG_OPTION([The binary will be optimized using], [${ax_cv_gcc_archflag}])
AX_MSG_OPTION([This version was configured for], [${host_cpu}-${host_os}])
AC_MSG_RESULT
