#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([sqlite3_helper], [1.0], [leon_mike@live.com.mx])
AM_INIT_AUTOMAKE([foreign dist-bzip2])
AC_CONFIG_SRCDIR([Database.cpp])
AC_CONFIG_HEADERS([config.h])
: ${CFLAGS="-g -O0"}
: ${CXXFLAGS="-g -O0"}

# Checks for programs.
AC_PROG_CXX
#AC_PROG_RANLIB
AC_ENABLE_SHARED
AC_DISABLE_STATIC
AC_PROG_LIBTOOL(libtool)

# Checks for libraries.
AC_CHECK_LIB([sqlite3], [sqlite3_open_v2], , [AC_MSG_ERROR( [libsqlite3 is required] ) ])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
AC_FUNC_MKTIME

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
