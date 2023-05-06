#ifndef __APP_VUE__
#define __APP_VUE__

#include "app_modele.h"

#include <gtk/gtk.h>

typedef struct AppVue_t AppVue;

AppModele *get_modele(struct AppVue_t *vue);

struct AppVue_t *create_app_vue(void);

void destroy_app_vue(struct AppVue_t *vue);

void create_window(struct AppVue_t *vue);
void create_window_container(struct AppVue_t *vue);

GtkWidget *get_window(struct AppVue_t *vue);
GtkWidget *get_window_container(struct AppVue_t *vue);

void build_app_vue(struct AppVue_t *vue);

#endif // !__APP_VUE__