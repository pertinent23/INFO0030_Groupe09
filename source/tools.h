#ifndef __TOOLS__
#define __TOOLS__

#include <gtk/gtk.h>

#define UNUSED(x) (void)(x)

typedef struct Color_t{
    unsigned int r, g, b;
} Color;

GtkWidget *create_label(const char *name, unsigned int size);

void set_font_color(GtkWidget *widget, const char *color_text);
void set_color(GtkWidget *widget, const char *color_text);

extern Color CIAN;
extern Color YELLOW;
extern Color PURPLE;
extern Color ORANGE;
extern Color BLUE;
extern Color RED;
extern Color GREEN;
extern Color DARK;

#endif // !__TOOLS__