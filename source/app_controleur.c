#include "app_controleur.h"
#include "app_modele.h"
#include "app_vue.h"
#include "tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <gdk/gdkkeysyms.h>

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

static void on_key_pressed(GtkWidget *window, GdkEventKey *event, gpointer data)
{
    switch (event->keyval)
    {
        case GDK_KEY_Up:
            break;
        
        case GDK_KEY_Down:
            break;
        
        case GDK_KEY_Right:
            break;
        
        case GDK_KEY_Left:
            break;

        default:
            break;
    }

    UNUSED(window);
    UNUSED(data);
}

static void connect_app_event(struct AppControleur_t *app)
{
    assert(app != NULL);

    g_signal_connect(
        G_OBJECT(app->window), "destroy",
        G_CALLBACK(destroy_window), NULL
    );   

    g_signal_connect(
        G_OBJECT(app->window), "key-press-event", 
        G_CALLBACK(on_key_pressed), NULL
    );
}

static void load_app_data(struct AppControleur_t *app)
{
    assert(app != NULL);

    app->window = get_window(app->vue);
    app->arrow_down = get_arrow_down(app->vue);
    app->arrow_left = get_arrow_left(app->vue);
    app->arrow_right = get_arrow_right(app->vue);
    app->arrow_up = get_arrow_up(app->vue);
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
    assert(app != NULL);

    build_app_vue(app->vue);
    
    load_app_data(app);
    connect_app_event(app);

    gtk_widget_show_all(get_window(app->vue));
    gtk_main();
}

void destroy_app_controleur(struct AppControleur_t *app)
{
    assert(app != NULL);
    
    destroy_app_vue(app->vue);
    free(app);
}