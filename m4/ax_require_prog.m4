dnl @synopsis AX_REQUIRE_PROG([name])
dnl
dnl Macro to require  system tools; a variable named as  uppercase tool name
dnl will be created containing the absolute path of the program.
dnl
dnl Examples:
dnl    AX_PROG_UUIDGEN
dnl    AX_REQUIRE_PROG([foo])
dnl
dnl @category Misc
dnl @author Davide Scola <davide@bitfinex.com>
dnl @version 2017-08-28
dnl @license AllPermissive

AC_DEFUN([AX_PROG_JQ], [
  AX_REQUIRE_PROG([jq])
])dnl AX_PROG_JQ

AC_DEFUN([AX_PROG_CAT], [
  AX_REQUIRE_PROG([cat])
])dnl AX_PROG_CAT

AC_DEFUN([AX_PROG_XXD], [
  AX_REQUIRE_PROG([xxd])
])dnl AX_PROG_XXD

AC_DEFUN([AX_PROG_DATE], [
  AX_REQUIRE_PROG([date])
])dnl AX_PROG_DATE

AC_DEFUN([AX_PROG_CURL], [
  AX_REQUIRE_PROG([curl])
])dnl AX_PROG_CURL

AC_DEFUN([AX_PROG_MKDIR], [
  AX_REQUIRE_PROG([mkdir])
])dnl AX_PROG_MKDIR

AC_DEFUN([AX_PROG_GETOPT], [
  AX_REQUIRE_PROG([getopt])
])dnl AX_PROG_GETOPT

AC_DEFUN([AX_PROG_UUIDGEN], [
  AX_WITH_PROG([UUIDGEN], [uuidgen])

  AS_IF([test -z "${UUIDGEN}"], [
    AC_PATH_PROG([UUIDGEN], [dbus-uuidgen])

    AS_IF([test -z "${UUIDGEN}"], [
      AC_MSG_CHECKING([whether your kernel provides an UUID generation mechanism])

      AS_IF([test -f '/proc/sys/kernel/random/uuid'], [
        AC_MSG_RESULT([yes])

        AX_PROG_CAT
        UUIDGEN="${CAT} /proc/sys/kernel/random/uuid"
      ], [
        AC_MSG_RESULT([no])
        AC_MSG_ERROR([unable to find the uuidgen application (or equivalent)])
      ])
    ])
  ])
])

AC_DEFUN([AX_PROG_SHA1SUM], [
  AX_REQUIRE_PROG([sha1sum])
])dnl AX_PROG_SHA1SUM

AC_DEFUN([AX_PROG_READLINK], [
  AX_REQUIRE_PROG([readlink])
])dnl AX_PROG_READLINK

AC_DEFUN([AX_REQUIRE_PROG], [
  AS_LITERAL_IF([$1], [], [AC_FATAL([$0: requires literal arguments])])

  AX_WITH_PROG(translit(m4_toupper($1), [-], [_]), [$1], [no])

  AS_IF([test "x${translit(m4_toupper($1), [-], [_])[]}" = 'xno'], [
    AC_MSG_ERROR([$1 cannot be found, please provide the full path.])
  ])
])dnl AX_REQUIRE_PROG
