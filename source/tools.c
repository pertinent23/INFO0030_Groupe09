#include "tools.h"

Color CIAN = {.r= 0, .g=255, .b=255};
Color YELLOW = {.r= 242, .g=226, .b=5};
Color PURPLE = {.r= 147, .g=5, .b=242};
Color ORANGE = {.r= 255, .g=165, .b=0};
Color BLUE = {.r= 0, .g=0, .b=255};
Color RED = {.r= 242, .g=5, .b=5};
Color GREEN = {.r= 13, .g=242, .b=5};
Color DARK = {.r= 30, .g=31, .b=41};

GtkWidget *create_label(const char *name, unsigned int size)
{
    GtkWidget *label = gtk_label_new(name);
    PangoFontDescription *font = pango_font_description_new();

    pango_font_description_set_size(font, size * PANGO_SCALE);
    gtk_widget_modify_font(label, font);
    pango_font_description_free(font);

    return label;
}

void set_color(GtkWidget *widget, const char *color_text)
{
    GdkColor color;
    gdk_color_parse(color_text, &color);
    gtk_widget_modify_bg(widget, GTK_STATE_NORMAL, &color);
    gtk_widget_modify_bg(widget, GTK_STATE_ACTIVE, &color);
    gtk_widget_modify_bg(widget, GTK_STATE_PRELIGHT, &color);
}

void set_font_color(GtkWidget *widget, const char *color_text)
{
    GdkColor color;
    gdk_color_parse(color_text, &color);

    gtk_widget_modify_fg(widget, GTK_STATE_NORMAL, &color);
}