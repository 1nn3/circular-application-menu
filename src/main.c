/* circular-main-menu
 * Copyright (C) 2008 - Cole Anstey
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * See http://code.google.com/p/circular-application-menu/
 */
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <libgnomevfs/gnome-vfs.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>

#include <glib/gi18n.h>
#include <string.h>

#define GMENU_I_KNOW_THIS_IS_UNSTABLE
#include <gnome-menus-3.0/gmenu-tree.h>

#include "cmmcircularmainmenu.h"

static CaFileLeaf* root_fileleaf = NULL;

/**
 * _ca_circular_application_menu_enable_blur:
 * @widget: The widget to set the blur against.
 *
 * Uses the compiz blur plugin to blur underneath the menus which makes the rendering clearer.
 **/
static void
_ca_circular_application_menu_enable_blur(GtkWidget* window)
{
    Display* xdisplay;
    long data[2];

    /* Blur under the window.  Taken from the blur demo application. */
    xdisplay = GDK_DISPLAY_XDISPLAY (gdk_display_get_default ());

    data[0] = 9;    /* threshold */
    data[1] = 0;    /* filter */

    XChangeProperty (
        xdisplay,
        GDK_WINDOW_XID (gtk_widget_get_window (window)),
        XInternAtom (xdisplay, "_COMPIZ_WM_WINDOW_BLUR", FALSE),
        XA_INTEGER,
        32, PropModeReplace, (guchar *) data,
        2);
}

int
main (int argc, char **argv)
{
    GtkWidget* window;
    GdkScreen* screen;
    GdkVisual* visual;
    GtkWidget* circular_application_menu;
    GOptionContext* optioncontext;
    GError* error = NULL;
    GMenuTreeFlags flags;
    GMenuTree* tree;
    GMenuTreeDirectory* root;
    /* Default values. */
    gboolean hide_preview = FALSE;
    gboolean warp_pointer_off = FALSE;
    gint glyph_size = 3;
    gboolean blur_off = FALSE;
    gchar* emblem = NULL;
    gboolean render_reflection = FALSE;
    gboolean render_tabbed_only = FALSE;
    gchar *menu_file = NULL;
    /*gboolean  monitor = FALSE;*/
    gboolean include_excluded = FALSE;
    gboolean include_nodisplay = FALSE;
    gboolean hide_tooltip = FALSE;
    gchar* color = NULL;

    GOptionEntry options[] =
    {
        { "color", 'c', 0, G_OPTION_ARG_STRING, &color, _("Specifies the colors (colon separated) to use for segments and text."), "NORMAL[:PRELIGHT[:TEXT]]" },
        { "hide-preview", 'h', 0, G_OPTION_ARG_NONE, &hide_preview, "Hides the menu preview displayed when the mouse is over a menu.", NULL },
        { "hide-tooltip", 's', 0, G_OPTION_ARG_NONE, &hide_tooltip, _("Hides the tooltip displayed when the mouse is over a menuitem."), NULL },
        { "warp-pointer-off", 'w', 0, G_OPTION_ARG_NONE, &warp_pointer_off, "Stops the pointer e.g. the mouse from warping to the centre of the screen whenever a menu is shown.", NULL },
        { "glyph-size", 'g', 0, G_OPTION_ARG_INT, &glyph_size, "The size of the glyphs [S: 1=small 2=medium 3=large (default)]. ", "S"  },
        { "blur-off", 'b', 0, G_OPTION_ARG_NONE, &blur_off, "Stops the blur from underneath the menu.", NULL },
        { "emblem", 'e', 0, G_OPTION_ARG_STRING, &emblem, "Specifies the (colon separated) emblems to use for the root menu.", "NORMAL:PRELIGHT" },
        { "render-reflection", 'r', 0, G_OPTION_ARG_NONE, &render_reflection, "Stops the reflection from being rendered.", NULL },
        { "render-tabbed-only", 't', 0, G_OPTION_ARG_NONE, &render_tabbed_only, "Only renders the currently tabbed menu.", NULL },        
        { "file", 'f', 0, G_OPTION_ARG_STRING, &menu_file, N_("Menu file."), N_("MENU_FILE") },
        /*{ "monitor", 'm', 0, G_OPTION_ARG_NONE, &monitor, N_("Monitor for menu changes", NULL },*/
        { "include-excluded", 'i', 0, G_OPTION_ARG_NONE, &include_excluded, N_("Include Excluded menu entries."), NULL },
        { "include-nodisplay", 'n', 0, G_OPTION_ARG_NONE, &include_nodisplay, N_("Include NoDisplay=true menu entries."), NULL },
        { NULL }
    };

    /* Initialise. */
    gtk_init (&argc, &argv);
    gnome_vfs_init();

    /* Parse the arguments. */
    optioncontext = g_option_context_new("- circular-application-menu.");
    g_option_context_add_main_entries(optioncontext, options, "circular_applications");
    g_option_context_parse(optioncontext, &argc, &argv, NULL);

    if (!g_option_context_parse (optioncontext, &argc, &argv, &error))
    {
        g_print (_("Option parsing failed: %s\n"), error->message);

        return -1;
    }

    g_option_context_free(optioncontext);

    flags = GMENU_TREE_FLAGS_NONE;
    if (include_excluded)
        flags |= GMENU_TREE_FLAGS_INCLUDE_EXCLUDED;
    if (include_nodisplay)
        flags |= GMENU_TREE_FLAGS_INCLUDE_NODISPLAY;
    
    tree = gmenu_tree_new (menu_file ? menu_file : "applications.menu", flags);
    g_assert (tree != NULL);

    if (!gmenu_tree_load_sync (tree, &error))
    {
        g_printerr ("Failed to load tree: %s\n", error->message);
        return -1;
    }

    g_message ("Loaded menu from %s\n", gmenu_tree_get_canonical_menu_path (tree));

    root = gmenu_tree_get_root_directory (tree);

    if (root == NULL)
    {
        g_warning (_("The menu tree is empty."));
    }

    if (FALSE == gdk_display_supports_composite(gdk_display_get_default()))
    {
        g_message(_("The circular-main-menu only displays correctly with composited desktops."));
    }
    screen = gdk_screen_get_default ();

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /* Assign an alpha colormap to the window. */
    screen = gtk_widget_get_screen (GTK_WIDGET (window)); // screen = gdk_screen_get_default ();
    visual = gdk_screen_get_rgba_visual (screen);

    if (visual == NULL)
        visual = gdk_screen_get_system_visual (screen);

    gtk_widget_set_visual (window, visual);
    /*
    Does not seem to be required.
    gdk_window_set_decorations(window->window, 0);
    */
    gtk_widget_realize (window);    /* This is required otherwise gdk_pixmap_new() will assert. */

    /* Constructs a new dockband widget. */
    circular_application_menu = ca_circular_application_menu_new (
        gtk_widget_get_window (GTK_WIDGET (window)),
        hide_preview,
        hide_tooltip,
        warp_pointer_off,
        glyph_size,
        emblem,
        render_reflection,
        render_tabbed_only,
        color);
    gtk_container_add (GTK_CONTAINER (window), circular_application_menu);

    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    /* Make the application full screen, without this it will be below any top edged panel. */
    gtk_window_fullscreen(GTK_WINDOW(window));

    /* Check whether blur is enabled. */
    if (FALSE == blur_off)
    {
        /* Use the compiz blur plugin to blur underneath the menus which makes the rendering clearer. */
        _ca_circular_application_menu_enable_blur(window);
    }

    gtk_widget_show_all (window);

    /* Shows the menu tree directory which becomes the root file leaf. */
    root_fileleaf = ca_circular_application_menu(CA_CIRCULAR_APPLICATION_MENU(circular_application_menu), root);

    /* Invalidate the widget. */
    gtk_widget_queue_draw(window);

    gtk_main ();

    gmenu_tree_item_unref (root);

    return 0;
}
