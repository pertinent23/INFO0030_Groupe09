#include "app_vue.h"
#include "app_modele.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct AppVue_t{
    AppModele *modele;
    
    GtkWidget *window;
    GtkWidget *menu;
    GtkWidget *windowContainer;
    GtkWidget *footer;
    GtkWidget *grill_side;
    GtkWidget *options;

    struct {
        GtkWidget *arrow_up;
        GtkWidget *arrow_down;
        GtkWidget *arrow_left;
        GtkWidget *arrow_right;
    } arrows;

    struct {
        GtkWidget *new; 
        GtkWidget *end; 
    } buttons;
};

struct AppVue_t *create_app_vue(void)
{
    struct AppVue_t *result = malloc(sizeof(struct AppVue_t));


    if(result == NULL)
        return NULL;
    
    result->modele = create_app();

    if (result->modele == NULL)
    {
        free(result);
        return NULL;
    }
    
    return result;
}

AppModele *get_modele(struct AppVue_t *vue)
{
    return vue->modele;
}

void destroy_app_vue(struct AppVue_t *vue)
{
    assert(vue != NULL);

    if (vue->windowContainer != NULL)
        gtk_widget_destroy(GTK_WIDGET(vue->windowContainer));
        
    if (vue->window != NULL)
        gtk_widget_destroy(GTK_WIDGET(vue->window));

    destroy_app(vue->modele);

    free(vue);
}

void create_window(struct AppVue_t *vue)
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "TETRIS");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);

    vue->window = window;
}


void create_window_container(struct AppVue_t *vue)
{
    vue->windowContainer = gtk_table_new(8, 8, TRUE);
}

GtkWidget *get_window(struct AppVue_t *vue)
{
    return vue->window;
}

GtkWidget *get_window_container(struct AppVue_t *vue)
{
    return vue->windowContainer;
}

void build_app_vue(struct AppVue_t *vue)
{
    create_window(vue);
    create_window_container(vue);
}