dnl @synopsis AX_DEFINE_DESCRIPTOR([NAME], [DESCRIPTION], [DEFAULT-VALUE])
dnl
dnl Macro to define a file descriptor;  it must be a non-negative number and
dnl greater than 2. If a value greater than 1023 is given, a warning message
dnl will be issued that informs user about ulimits.
dnl
dnl Examples:
dnl    AX_DEFINE_DESCRIPTOR([FOO_FILENO], [wonderful foo], [99])
dnl
dnl @category Misc
dnl @author Davide Scola <davide@bitfinex.com>
dnl @version 2017-08-28
dnl @license AllPermissive

AC_DEFUN([AX_DEFINE_DESCRIPTOR], [
  AS_LITERAL_IF([$1], [], [AC_FATAL([$0: requires literal arguments])])
  AS_LITERAL_IF([$2], [], [AC_FATAL([$0: requires literal arguments])])
  AS_LITERAL_IF([$3], [], [AC_FATAL([$0: requires literal arguments])])

  AC_ARG_WITH(m4_tolower($1), AS_HELP_STRING(m4_tolower(--with-$1),
    [Set the $2 file descriptor @<:@default=$3@:>@]),
    ac_cv_[]m4_tolower($1)="${withval:-yes}", ac_cv_[]m4_tolower($1)="$3")

  AC_MSG_CHECKING([whether you want to set the $2 file descriptor])

  AS_IF([test "x${ac_cv_[]m4_tolower($1)[]}" = "x$3"],
    [AC_MSG_RESULT([no])], [AC_MSG_RESULT([yes])])

  echo "${ac_cv_[]m4_tolower($1)[]}" | grep ['[^0123456789]'] >/dev/null 2>&1 &&
    AC_MSG_ERROR([the $2 file descriptor must be a non negative integer])

  AS_IF([test "$(( 10[#]${ac_cv_[]m4_tolower($1)[]} ))" -lt 3],
    [AC_MSG_ERROR([the $2 file descriptor cannot be STDIN, STDOUT or STDERR.])])

  AS_IF([test "$(( 10[#]${ac_cv_[]m4_tolower($1)[]} ))" -gt 1023],
    [AC_MSG_WARN([the $2 file descriptor can be out of your available descriptors; check your ulimits.])])

  AC_SUBST(m4_toupper($1), [$(( 10[#]${ac_cv_[]m4_tolower($1)[]} ))])

  AH_TEMPLATE(m4_toupper($1), [Define the $2 file descriptor.])
  AC_DEFINE_UNQUOTED(m4_toupper($1), [($(( 10[#]${ac_cv_[]m4_tolower($1)[]} )))], [Define the $2 file descriptor.])
])dnl AX_DEFINE_DESCRIPTOR

