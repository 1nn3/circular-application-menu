/* circular-main-menu
 * Copyright: 2008-2013 Cole Anstey <cole.anstey@gmail.com>
 *                      Steffen Rumberger <inne@sdfeu.org>
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
 * See http://github.com/1nn3/circular-application-menu
 */
#ifndef __CA_CIRCULAR_APPLICATION_MENU_H__
#define __CA_CIRCULAR_APPLICATION_MENU_H__

#include "main.h"

G_BEGIN_DECLS

#define CA_TYPE_CIRCULAR_APPLICATION_MENU          (ca_circular_application_menu_get_type ())
#define CA_CIRCULAR_APPLICATION_MENU(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), CA_TYPE_CIRCULAR_APPLICATION_MENU, CaCircularApplicationMenu))
#define CA_CIRCULAR_APPLICATION_MENU_CLASS(obj)    (G_TYPE_CHECK_CLASS_CAST ((obj), CA_CIRCULAR_APPLICATION_MENU, CaCircularApplicationMenuClass))
#define CA_IS_CIRCULAR_APPLICATION_MENU(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CA_TYPE_CIRCULAR_APPLICATION_MENU))
#define CA_IS_CIRCULAR_APPLICATION_MENU_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((obj), EFF_TYPE_CIRCULAR_APPLICATION_MENU))
#define CA_CIRCULAR_APPLICATION_MENU_GET_CLASS     (G_TYPE_INSTANCE_GET_CLASS ((obj), CA_TYPE_CIRCULAR_APPLICATION_MENU, CaCircularApplicationMenuClass))

/* Leaf types. */
typedef enum
{
    ROOT_LEAF,
    FILE_LEAF,
    SUB_FILE_LEAF
} LeafType;

/* Gylph types. */
typedef enum
{
    GLYPH_UNKNOWN,
    GLYPH_ROOT_CENTRE,
    GLYPH_FILE_MENU_CENTRE,
    GLYPH_FILE,
    GLYPH_FILE_MENU,
    GLYPH_TAB
} GlyphType;

/* The current animation state of a leaf. */
typedef enum
{
    NO_STATE,
    INITIAL_OPEN
} AnimationState;

typedef struct _CaCircularApplicationMenu        CaCircularApplicationMenu;
typedef struct _CaCircularApplicationMenuClass   CaCircularApplicationMenuClass;

struct _CaCircularApplicationMenu
{
    GtkDrawingArea parent;

    /*< private >*/

    /*< public >*/
};

struct _CaCircularApplicationMenuClass
{
    GtkDrawingAreaClass parent_class;
};

typedef struct _CaMenuRender CaMenuRender;
typedef struct _CaSegmentRender CaSegmentRender;
typedef struct _CaFileItem CaFileItem;
typedef struct _CaFileLeaf CaFileLeaf;

/* Structure to hold calculated menu values for rendering. */
/* Held here to stop them being calculated more than once. */
struct _CaMenuRender
{
    // Render a child menu.
    /*
     C   E
     B   F
    A     A
    A     A
    A     A
     AAAAA
    */
    gint Bcircle_x;
    gint Bcircle_y;
    gint Ccircle_x;
    gint Ccircle_y;
    gint Ecircle_x;
    gint Ecircle_y;
    gint Fcircle_x;
    gint Fcircle_y;
    gint Bcircle_arc_x;
    gint Bcircle_arc_y;
    gint Ccircle_arc_x;
    gint Ccircle_arc_y;
    gdouble lowest_angle_nearest;
    gdouble highest_angle_nearest;
    gdouble Bcircle_lowest_angle;
    gdouble Bcircle_highest_angle;
    gdouble Fcircle_lowest_angle;
    gdouble Fcircle_highest_angle;
    gdouble lowest_angle_farthest;
    gdouble highest_angle_farthest;
    gdouble Ccircle_lowest_angle;
    gdouble Ccircle_highest_angle;
    gdouble Ecircle_lowest_angle;
    gdouble Ecircle_highest_angle;

    gdouble tab_glyph_radius;
    gint tab_glyph_x;
    gint tab_glyph_y;
};

/* Structure to hold calculated segment values for rendering. */
/* Held here to stop them being calculated more than once.    */
struct _CaSegmentRender
{
    /*
    Segment

    CDC
    BAB
    */
    gint Aradius;
    gint Bradius;
    gint Cradius;
    gint Dradius;
    gdouble Afrom_angle;
    gdouble Bfrom_angle;
    gdouble Cfrom_angle;
    gdouble Dfrom_angle;
    gdouble Ato_angle;
    gdouble Bto_angle;
    gdouble Cto_angle;
    gdouble Dto_angle;
    gint B_lowest_circle_x;
    gint B_lowest_circle_y;
    gint C_lowest_circle_x;
    gint C_lowest_circle_y;
    gint B_highest_circle_x;
    gint B_highest_circle_y;
    gint C_highest_circle_x;
    gint C_highest_circle_y;

    // Arrow.
    gdouble arrow_percentage;
    gdouble common_angle;
    gint arrow_point_x;
    gint arrow_point_y;
    gint arrow_side_x;
    gint arrow_side_y;
    gint arrow_radius;
    gdouble arrow_angle;
};

/* The file-item which resides on a file-leaf. */
struct _CaFileItem
{
    GlyphType _type;
    gpointer _menutreeitem; /* GMenuTreeDirectory* */
    const gchar* _icon;
    GdkPixbuf* _pixbuf;
    CaFileLeaf* _assigned_fileleaf;
    CaFileItem* _associated_fileitem;
    gdouble _parent_angle;
    gdouble _circular_angle_share;
    gdouble _parent_radius;
    CaSegmentRender* _segment_render;

    /*< Drawing >*/
    gint x;
    gint y;
    gint size;
};

/* The file-leaf containing 0-* file-items. */
struct _CaFileLeaf
{
    LeafType _type;
    GList* _fileitem_list;
    gint _fileitem_list_count;
    AnimationState _current_animation_state;
    gint _current_animation_tick;
    CaFileLeaf* _parent_fileleaf;
    CaFileLeaf* _child_fileleaf;
    GList* _sub_fileleaves_list;
    CaFileItem* _central_glyph;
    CaMenuRender* _menu_render;

    /*< Drawing >*/
    gint x;
    gint y;
    gint radius;
};

/* Construction */
GtkWidget* ca_circular_application_menu_new (GdkWindow *window, gboolean hide_preview, gboolean hide_tooltip, gboolean warp_pointer_off, gint glyph_size, gchar* emblem, gboolean render_reflection_off, gboolean render_tabbed_only, gchar* color);
GType ca_circular_application_menu_get_type(void);

/* Implementation */
CaFileLeaf* ca_circular_application_menu(CaCircularApplicationMenu* circular_application_menu, GMenuTreeDirectory* menutreedirectory);
CaFileLeaf* ca_circular_application_menu_show_leaf(CaCircularApplicationMenu* circular_application_menu, GMenuTreeDirectory* menutreedirectory, LeafType leaftype, CaFileItem* fileitem, gboolean disassociated);
void ca_circular_application_menu_close_fileleaf(CaFileLeaf* fileleaf);

/* Private functions. */

G_END_DECLS

#endif
