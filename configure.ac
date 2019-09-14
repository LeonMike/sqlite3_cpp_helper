#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE([foreign dist-bzip2])
AC_CONFIG_SRCDIR([main.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
AC_CHECK_LIB([sqlite3], [sqlite3_open_v2], , [AC_MSG_ERROR( [libsqlite3 is required] ) ])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
AC_FUNC_MKTIME

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
