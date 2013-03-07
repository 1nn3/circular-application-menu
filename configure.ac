#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Circular-Application-Menu], [0.0.0r58], [inne@sdfeu.org], [circular-application-menu], [http://github.com/1nn3/circular-application-menu])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_AWK
AC_PROG_CPP
AC_PROG_MKDIR_P

# Checks for libraries.
PKG_CHECK_MODULES([glib], [glib-2.0])
AC_SUBST(glib_LIBS)
AC_SUBST(glib_CFLAGS)

PKG_CHECK_MODULES([gnome_vfs], [gnome-vfs-2.0])
AC_SUBST(gnome_vfs_LIBS)
AC_SUBST(gnome_vfs_CFLAGS)

PKG_CHECK_MODULES([gtk], [gtk+-3.0])
AC_SUBST(gtk_LIBS)
AC_SUBST(gtk_CFLAGS)

PKG_CHECK_MODULES([libgnome_menu], [libgnome-menu-3.0])
AC_SUBST(libgnome_menu_LIBS)
AC_SUBST(libgnome_menu_CFLAGS)

# Checks for header files.
AC_PATH_X
AC_CHECK_HEADERS([string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([sqrt])

AC_CONFIG_FILES([
	Makefile
	man/Makefile
	pixmaps/Makefile
	src/Makefile
])
AC_OUTPUT
