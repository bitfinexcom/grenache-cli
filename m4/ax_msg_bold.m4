dnl @synopsis AX_MSG_BOLD([BOLD_TEXT])
dnl @synopsis AX_MSG_OPTION([NORMAL TEXT], [BOLD_TEXT])
dnl
dnl Prints  messages  using  a  nice  visual effect;  you  should  set the
dnl (shell) variables  SB and  EB in  your  configure.{ac,in}  file  using 
dnl something like this:
dnl
dnl SB=`$srcdir/shtool echo -n -e %B`
dnl EB=`$srcdir/shtool echo -n -e %b`
dnl
dnl Examples:
dnl    AX_MSG_BOLD([foobar])
dnl
dnl    AX_MSG_OPTION([ foo .................... ], [${BAR}])
dnl
dnl @category Misc
dnl @author Davide Scola <davide@bitfinex.com>
dnl @version 2017-04-20
dnl @license AllPermissive

AC_DEFUN([AX_MSG_BOLD], [
  AC_MSG_RESULT
  AC_MSG_RESULT([${SB}$1...${EB}])
  AC_MSG_RESULT
])dnl AX_MSG_BOLD

AC_DEFUN([AX_MSG_OPTION], [
  AC_MSG_RESULT([$1 ${SB}$2${EB}])
])dnl AX_MSG_OPTION
