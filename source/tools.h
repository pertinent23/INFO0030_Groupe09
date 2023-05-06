#ifndef __TOOLS__
#define __TOOLS__

#include <gtk/gtk.h>

#define UNUSED(x) (void)(x)

GtkWidget *create_label(const char *name, unsigned int size);

void set_font_color(GtkWidget *widget, const char *color_text);
void set_color(GtkWidget *widget, const char *color_text);

#endif // !__TOOLS__