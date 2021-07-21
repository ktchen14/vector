#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])

AC_INIT([Vector],
        m4_normalize(m4_include([VERSION])),
        [ktchen14@gmail.com],
        [vector],
        [https://github.com/ktchen14/vector])
AC_CONFIG_SRCDIR([header/vector.h])
AC_CONFIG_AUX_DIR([tool])
AC_CONFIG_MACRO_DIRS([tool])

AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects no-dist-gzip dist-xz])

AM_PROG_AR
LT_INIT
AC_PROG_CC

# On macOS with `dyld`: Alters how symbols are resolved at build time and
# runtime. With -flat_namespace, the linker searches all dylibs on the command
# line and all dylibs those original dylibs depend on. The linker does not
# record which dylib an external symbol came from, so at runtime dyld again
# searches all images and uses the first definition it finds.
AX_CHECK_LINK_FLAG([-Wl,-flat_namespace],
                   [test_vector_la_ldflags=-Wl,-flat_namespace])
AC_SUBST([test_vector_la_ldflags])

PKG_INSTALLDIR

AC_SUBST([PACKAGE_DESCRIPTION], ["An unobtrusive vector implementation in C"])
AC_SUBST([AC_PACKAGE_DESCRIPTION], ["An unobtrusive vector implementation in C"])

AC_CONFIG_FILES([Makefile header/Makefile test/Makefile data/vector.pc])
AC_OUTPUT
