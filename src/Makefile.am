# Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
	$(glib_CFLAGS) \
	$(gnome_vfs_CFLAGS) \
	$(gtk_CFLAGS) \
	$(libgnome_menu_CFLAGS)

AM_LDFLAGS = \
	$(glib_LIBS) \
	$(gnome_vfs_LIBS) \
	$(gtk_LIBS) \
	$(libgnome_menu_LIBS)

bin_PROGRAMS = \
	cmm

cmm_SOURCES = \
	cmmcircularmainmenu.c \
	main.c
