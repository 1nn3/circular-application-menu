#ifndef __MAIN_H__
#define __MAIN_H__

#define G_DISABLE_DEPRECATED
#define GSEAL_ENABLE
#define GTK_DISABLE_DEPRECATED
#define GTK_DISABLE_SINGLE_INCLUDES
#define GTK_MULTIHEAD_SAFE
#define GTK_MULTIDEVICE_SAFE
#define GDK_DISABLE_DEPRECATED
#define GDK_PIXBUF_DISABLE_DEPRECATED
#define GMENU_I_KNOW_THIS_IS_UNSTABLE

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <gdk/gdkx.h>
#include <gio/gdesktopappinfo.h>
#include <libgnomevfs/gnome-vfs.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <glib/gi18n.h>
#include <gnome-menus-3.0/gmenu-tree.h>

#include <math.h>
#include <unistd.h>
#include <string.h>

#include "../config.h"
#include "cmmcircularmainmenu.h"

#include "../pixmaps/close-menu-prelight.h"
#include "../pixmaps/close-menu-normal.h"
#include "../pixmaps/open-sub-menu-prelight.h"
#include "../pixmaps/open-sub-menu-normal.h"
#include "../pixmaps/reflection.h"

#endif
