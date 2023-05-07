#include "app_controleur.h"

#include "tools.h"
#include "app_vue.h"
#include "app_modele.h"
#include "piece_modele.h"
#include "piece_controleur.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <gdk/gdkkeysyms.h>

struct AppControleur_t{
    AppVue *vue;
    unsigned int can_draw;
    unsigned int play;
    unsigned int pause;
    GtkWidget *window;
    GtkWidget *grill;
    GtkWidget *arrow_up;
    GtkWidget *arrow_down;
    GtkWidget *arrow_left;
    GtkWidget *arrow_right;
};

static void clear_grill(cairo_t *cairo)
{
    cairo_set_source_rgb(cairo, FILL_R, FILL_G, FILL_B);
    cairo_paint(cairo);
}

static void destroy_window(GtkWidget *window, gpointer data)
{
    gtk_main_quit();
    UNUSED(window);
    UNUSED(data);
}

static void arrow_down_pressed(gpointer data)
{
    struct AppControleur_t *app = (struct AppControleur_t *) data;
    PieceControleur *piece = get_current_pieces(get_modele(app->vue));
    PieceModel *piece_m = get_piece_model(get_piece_vue(piece));

    modify_piece_model(get_piece_vue(piece), rotate_right(piece_m));
}

static void on_button_arrow_down_pressed(GtkWidget * widget, gpointer data)
{
    arrow_down_pressed(data);
    UNUSED(widget);
}

static void arrow_up_pressed(gpointer data)
{
    struct AppControleur_t *app = (struct AppControleur_t *) data;
    PieceControleur *piece = get_current_pieces(get_modele(app->vue));
    PieceModel *piece_m = get_piece_model(get_piece_vue(piece));

    modify_piece_model(get_piece_vue(piece), rotate_left(piece_m));
}

static void on_button_arrow_up_pressed(GtkWidget * widget, gpointer data)
{
    arrow_up_pressed(data);
    UNUSED(widget);
}

static void on_key_pressed(GtkWidget *window, GdkEventKey *event, gpointer data)
{
    switch (event->keyval)
    {
        case GDK_KEY_Up:
            arrow_up_pressed(data);
            break;
        
        case GDK_KEY_Down:
            arrow_down_pressed(data);
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

static gboolean on_realize(GtkWidget * widget, gpointer data){
    struct AppControleur_t *app = (struct AppControleur_t *) data;
    app->can_draw = 1;

    gtk_widget_queue_draw(widget);
    UNUSED(data);
    return TRUE;
}

static gboolean on_expose(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
    struct AppControleur_t *app = (struct AppControleur_t *) data;
    GdkWindow *window = gtk_widget_get_window(widget);
    cairo_t *context = gdk_cairo_create(window);
    PieceControleur *piece = get_current_pieces(
        get_modele(app->vue)
    );

    if (piece != NULL)
    {
        clear_grill(context);
        draw_piece(
            piece, context, 
            GRILL_CELL_SIZE, GRILL_CELL_MARGING
        );
    }

    cairo_destroy(context);

    UNUSED(data);
    UNUSED(event);
    return TRUE;
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
        G_CALLBACK(on_key_pressed), (gpointer) app
    );

    g_signal_connect(
        GTK_OBJECT(app->grill), "realize", 
        G_CALLBACK(on_realize), (gpointer) app
    );

    g_signal_connect(
        G_OBJECT(app->grill), "expose_event", 
        G_CALLBACK(on_expose), (gpointer) app
    );

    g_signal_connect(
        G_OBJECT(app->arrow_down), "clicked", 
        G_CALLBACK(on_button_arrow_down_pressed), (gpointer) app
    );

    g_signal_connect(
        G_OBJECT(app->arrow_up), "clicked", 
        G_CALLBACK(on_button_arrow_up_pressed), (gpointer) app
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
    app->grill = get_grill(app->vue);
}

static void frame_rate(struct AppControleur_t *app)
{
    PieceControleur *current = get_current_pieces(
        get_modele(app->vue)
    );

    if (current == NULL)
    {
        current = create_piece_controleur(L_NORMAL);
        set_current_pieces(get_modele(app->vue), current);
        set_position_x(get_piece_model(get_piece_vue(current)), 0);
        set_position_y(get_piece_model(get_piece_vue(current)), 0);
    }

    if (app->can_draw)
    {
        gtk_widget_queue_draw(app->grill);
        update_gravity(
            get_piece_model(
                get_piece_vue(current)
            )
        );
    }
}

static int frame_clock(gpointer data)
{
    struct AppControleur_t *app = (struct AppControleur_t *) data;

    if (app->play)
    {
        if(!app->pause)
            frame_rate(app);
        g_timeout_add(CLOCK, frame_clock, (gpointer) app);
    }

    return 0;
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

    result->play = 1;
    result->pause = 0;
    result->can_draw = 0;
    
    return result;
}

void launch(struct AppControleur_t *app)
{
    assert(app != NULL);

    build_app_vue(app->vue);
    
    load_app_data(app);
    connect_app_event(app);

    g_timeout_add(CLOCK, frame_clock, (gpointer) app);

    gtk_widget_show_all(get_window(app->vue));
    gtk_main();
}

void destroy_app_controleur(struct AppControleur_t *app)
{
    assert(app != NULL);
    
    destroy_app_vue(app->vue);
    free(app);
}