#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([MuOnlineServerFiles], [1.0], [mikiones@gmail.com])
AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE
##WITH_MYSQL()
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB	
AC_INCLUDES_DEFAULT
# Checks for libraries.
#AX_PYTHON
#AX_BOOST
#AX_BOOST_SYSTEM
#AX_BOOST_ASIO
#AX_BOOST_PYTHON
#AX_LIB_MYSQL
# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([arpa/inet.h netinet/in.h stdlib.h string.h sys/socket.h unistd.h])
AC_CHECK_HEADER(winsock2.h)
AC_CHECK_HEADER(mysql.h)

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([gethostbyname inet_ntoa memset socket])
AC_CONFIG_FILES([
makefile
LibSrc/makefile
LibSrc/DB/makefile
LibSrc/MuObiects/makefile
LibSrc/Protocol/makefile
LibSrc/ConfFile/makefile
LibSrc/Encryption/makefile
LibSrc/GSPyScripts/makefile
LibSrc/HexBuffer/makefile
LibSrc/Server/makefile
LibSrc/Socket/makefile
LibSrc/Task/makefile
Src/makefile
Src/GSEmu/makefile
Src/MuBoot/makefile
])
AC_OUTPUT
