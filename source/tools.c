#include "tools.h"

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