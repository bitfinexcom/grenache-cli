dnl @synopsis AX_DEFINE_SIZE([NAME], [DESCRIPTION], [DEFAULT-VALUE])
dnl
dnl Macro to define  a buffer size; it  must be a non-negative  number and a
dnl power of 2. If  a value below 16  or higher than 512 is  given, an error
dnl message will be displayed.
dnl
dnl Examples:
dnl    AX_DEFINE_SIZE([FOO_SIZE], [foo], [1024])
dnl
dnl @category Misc
dnl @author Davide Scola <davide@bitfinex.com>
dnl @version 2017-08-28
dnl @license AllPermissive

AC_DEFUN([AX_DEFINE_SIZE], [
  AS_LITERAL_IF([$1], [], [AC_FATAL([$0: requires literal arguments])])
  AS_LITERAL_IF([$2], [], [AC_FATAL([$0: requires literal arguments])])
  AS_LITERAL_IF([$3], [], [AC_FATAL([$0: requires literal arguments])])

  AC_ARG_WITH(m4_tolower($1), AC_HELP_STRING(m4_tolower(--with-$1),
    [Set the $2 size in bytes @<:@default=$3@:>@]),
    ac_cv_[]m4_tolower($1)="${withval:-yes}", ac_cv_[]m4_tolower($1)="$3")

  AC_MSG_CHECKING([whether you want to set the $2 size in bytes])

  AS_IF([test "x${ac_cv_[]m4_tolower($1)[]}" = "x$3"],
    [AC_MSG_RESULT([no])], [AC_MSG_RESULT([yes])])

  echo "${ac_cv_[]m4_tolower($1)[]}" | grep ['[^0123456789]'] >/dev/null 2>&1 &&
    AC_MSG_ERROR([the $2 size in bytes must be a non negative integer])

  AS_IF([test "$(( 10[#]${ac_cv_[]m4_tolower($1)[]} & -10[#]${ac_cv_[]m4_tolower($1)[]} ))" -ne "$(( 10[#]${ac_cv_[]m4_tolower($1)[]} ))"],
    [AC_MSG_ERROR([the $2 size in bytes must be a power of two])])

  AS_IF([test "$(( 10[#]${ac_cv_[]m4_tolower($1)[]} ))" -lt 16 -o "$(( 10[#]${ac_cv_[]m4_tolower($1)[]} ))" -gt 512],
    [AC_MSG_ERROR([the $2 size in bytes out of a reasonable range])])

  AC_SUBST(m4_toupper($1), [$(( 10[#]${ac_cv_[]m4_tolower($1)[]} ))])

  AH_TEMPLATE(m4_toupper($1), [Define the $2 size in bytes.])
  AC_DEFINE_UNQUOTED(m4_toupper($1), [($(( 10[#]${ac_cv_[]m4_tolower($1)[]} ))UL)], [Define the $2 size in bytes.])
])dnl AX_DEFINE_SIZE

