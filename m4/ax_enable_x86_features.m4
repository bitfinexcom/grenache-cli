dnl @synopsis AX_ENABLE_X86_FEATURES([foo], [bar])
dnl
dnl Macro to conditionally enable the x86 features check.
dnl
dnl Examples:
dnl    AX_ENABLE_X86_FEATURES
dnl    AX_ENABLE_X86_FEATURES([foo], [bar])
dnl
dnl @category Misc
dnl @author Davide Scola <davide@bitfinex.com>
dnl @version 2017-11-09
dnl @license AllPermissive

AC_DEFUN([AX_ENABLE_X86_FEATURES], [
  AC_ARG_ENABLE([x86-features], AC_HELP_STRING([--enable-x86-features],
    [Enable the x86 features check @<:@default=yes@:>@]),
    [ax_cv_enable_x86_features="${enableval}"], [ax_cv_enable_x86_features='yes'])

  AC_MSG_CHECKING([whether you want to enable the x86 features check])

  AS_IF([test "x${ax_cv_enable_x86_features}" = 'xyes'], [
    AC_MSG_RESULT([yes])
    AX_CHECK_X86_FEATURES([$1], [$2])], [
    AC_MSG_RESULT([no])
  ])
])dnl AX_ENABLE_X86_FEATURES
