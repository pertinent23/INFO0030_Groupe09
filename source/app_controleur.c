#include "app_controleur.h"
#include "app_modele.h"
#include "app_vue.h"
#include "tools.h"

#include <stdio.h>
#include <stdlib.h>

struct AppControleur_t{
    AppVue *vue;
    GtkWidget *window;
    GtkWidget *arrow_up;
    GtkWidget *arrow_down;
    GtkWidget *arrow_left;
    GtkWidget *arrow_right;
};

static void destroy_window(GtkWidget *window, gpointer data)
{
    gtk_main_quit();
    UNUSED(window);
    UNUSED(data);
}

static void connect_app_event(struct AppControleur_t *app)
{
    g_signal_connect(
        G_OBJECT(get_window(app->vue)), "destroy",
        G_CALLBACK(destroy_window), NULL
    );   
}

static void load_app_data(struct AppControleur_t *app)
{
    app->window = get_window(app->vue);
}

struct AppControleur_t *create_app_controleur(void)
{
    struct AppControleur_t *result = malloc(sizeof(struct AppControleur_t));

    if (result ==  NULL)
        return NULL;
    
    result->vue = create_app_vue();

    if (result->vue == NULL)
    {
        free(result);
        return NULL;
    }
    
    return result;
}

void launch(struct AppControleur_t *app)
{
    build_app_vue(app->vue);
    
    load_app_data(app);
    connect_app_event(app);

    gtk_widget_show_all(get_window(app->vue));
    gtk_main();
}

void destroy_app_controleur(struct AppControleur_t *app)
{
    destroy_app_vue(app->vue);
    free(app);
}