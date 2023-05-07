#ifndef __APP_VUE__
#define __APP_VUE__

#include "app_modele.h"

#include <gtk/gtk.h>

typedef struct AppVue_t AppVue;

AppModele *get_modele(struct AppVue_t *vue);

struct AppVue_t *create_app_vue(void);

void destroy_app_vue(struct AppVue_t *vue);

void create_menu(struct AppVue_t *vue);
void create_footer(struct AppVue_t *vue);
void create_grill_side(struct AppVue_t *vue);
void create_options(struct AppVue_t *vue);
void create_window(struct AppVue_t *vue);
void create_window_container(struct AppVue_t *vue);

GtkWidget *create_buttons(struct AppVue_t *vue);
GtkWidget *create_labels(struct AppVue_t *vue);
GtkWidget *create_arrow(struct AppVue_t *vue, GtkArrowType type);

GtkWidget *get_arrow_up(struct AppVue_t *vue);
GtkWidget *get_arrow_down(struct AppVue_t *vue);
GtkWidget *get_arrow_left(struct AppVue_t *vue);
GtkWidget *get_arrow_right(struct AppVue_t *vue);

GtkWidget *get_menu_new(struct AppVue_t *vue);
GtkWidget *get_menu_quit(struct AppVue_t *vue);
GtkWidget *get_menu_best(struct AppVue_t *vue);
GtkWidget *get_menu_help(struct AppVue_t *vue);

GtkWidget *get_button_new(struct AppVue_t *vue);
GtkWidget *get_button_quit(struct AppVue_t *vue);

GtkWidget *get_window(struct AppVue_t *vue);
GtkWidget *get_grill(struct AppVue_t *vue);
GtkWidget *get_window_container(struct AppVue_t *vue);

void update_score_label(struct AppVue_t *vue);
void update_delay_label(struct AppVue_t *vue);
void build_app_vue(struct AppVue_t *vue);

#endif // !__APP_VUE__