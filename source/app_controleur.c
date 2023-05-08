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
    cairo_set_source_rgb(
        cairo, 
        (double) DARK.r/255, 
        (double) DARK.g/255, 
        (double) DARK.b/255
    );

    cairo_paint(cairo);
}

static unsigned int is_right_collision(struct AppControleur_t *app, PieceModel *piece_m)
{
    void ***wall;
    unsigned int x = get_position_x(piece_m), collision = 0, z = 1;

    while (z<=SHEMA_EDGES && x+z <= GRILL_WIDTH && collision==0)
    {
        wall = (void ***) get_pixels(get_modele(app->vue));
        collision = collision_right(piece_m, wall, GRILL_HEIGHT, x+z);
        z++;
    }

    return collision;
}

static unsigned int is_left_collision(struct AppControleur_t *app, PieceModel *piece_m)
{
    void ***wall;
    unsigned int x = get_position_x(piece_m), collision = 0, z = 1;

    if (x==0)
        return 1;

    while (z<=SHEMA_EDGES && (int) x- (int) z >= 0 && collision==0)
    {
        wall = (void ***) get_pixels(get_modele(app->vue));
        collision = collision_left(piece_m, wall, GRILL_HEIGHT, x-z);
        z++;
    }

    return collision;
}

static unsigned int is_down_collision(struct AppControleur_t *app, PieceModel *piece_m)
{
    void ***wall;
    unsigned int y = get_position_y(piece_m), collision = 0, z = 1;

    while (z<=SHEMA_EDGES && y+z <= GRILL_HEIGHT && collision==0)
    {
        wall = (void ***) get_pixels(get_modele(app->vue));
        collision = collision_down(piece_m, wall, GRILL_WIDTH, y+z);
        z++;
    }

    return collision;
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

static void arrow_right_pressed(gpointer data)
{
    struct AppControleur_t *app = (struct AppControleur_t *) data;
    PieceControleur *piece = get_current_pieces(get_modele(app->vue));
    PieceModel *piece_m = get_piece_model(get_piece_vue(piece));

    if (!is_right_collision(app, piece_m))
    {
        set_position_x(piece_m, get_position_x(piece_m)+1);
    }
}

static void on_button_arrow_right_pressed(GtkWidget * widget, gpointer data)
{
    arrow_right_pressed(data);
    UNUSED(widget);
}

static void arrow_left_pressed(gpointer data)
{
    struct AppControleur_t *app = (struct AppControleur_t *) data;
    PieceControleur *piece = get_current_pieces(get_modele(app->vue));
    PieceModel *piece_m = get_piece_model(get_piece_vue(piece));

    if (get_position_x(piece_m) && !is_left_collision(app, piece_m))
    {
        set_position_x(piece_m, get_position_x(piece_m)-1);
    }
}

static void on_button_arrow_left_pressed(GtkWidget * widget, gpointer data)
{
    arrow_left_pressed(data);
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
            arrow_right_pressed(data);
            break;
        
        case GDK_KEY_Left:
            arrow_left_pressed(data);
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

static void draw_grill(struct AppControleur_t *app, cairo_t *context)
{
    Color ***grill = get_pixels(get_modele(app->vue));

    unsigned int width = get_grill_width(get_modele(app->vue));
    unsigned int height = get_grill_height(get_modele(app->vue));

    for (unsigned int y = 0; y < height; y++)
    {
        for (unsigned int x = 0; x < width; x++)
        {
            if (grill[y][x] != NULL)
            {
                draw_case(context, grill[y][x], x, y, 0, GRILL_CELL_SIZE, GRILL_CELL_MARGING);
            }
        }
    }
}

static void fill_grill(struct AppControleur_t *app, PieceControleur *current)
{
    AppModele *model = get_modele(app->vue);
    PieceVue *piece_v = get_piece_vue(current);
    PieceModel *piece_m = get_piece_model(piece_v);
    Color *color = get_color(piece_v);
    unsigned int x = get_position_x(piece_m);
    unsigned int y = get_position_y(piece_m);

    for(unsigned int a = x, ap = 0; a<GRILL_WIDTH && ap<SHEMA_EDGES; a++, ap++)
    {
        for(unsigned int b = y, bp = 0; b<GRILL_HEIGHT && bp < SHEMA_EDGES; b++, bp++)
        {
            if (get_shema_item(piece_m, ap, bp))
                set_pixel(model, color, a, b);
        }
    }
}

static int is_line_filled(void **line, unsigned int length)
{
    assert(line != NULL && length >0);

    for (unsigned int i = 0; i < length; i++)
    {
        if (line[i] == NULL)
            return 0;
    }

    return 1;
}

static void summerize(struct AppControleur_t *app)
{
    AppModele *modele = get_modele(app->vue);
    unsigned int points = 0, score = 0;
    int width = (int) get_grill_width(modele);
    int height = (int) get_grill_height(modele);
    void ***grill = (void ***) get_pixels(modele);

    for (int y = height-1; y >= 0; y--)
    {
        if(is_line_filled(grill[y], width)) 
        {
            points++;
            for(int yp = y - 1; yp >= 0; yp--)
            {
                for(int x = 0; x < width; x++)
                {
                    set_pixel(modele, grill[yp][x], x, yp+1);
                    set_pixel(modele, NULL, x, yp);
                }
            }
        }
    }

    switch (points)
    {
        case 0:
            score = 0;
            break;

        case 1:
            score = 40;
            break;
        
        case 2:
            score = 100;
            break;
        
        case 3:
            score = 300;
            break;
    
        default:
            score = 1200;
            break;
    }

    set_score(modele, get_score(modele) + score);
    set_deplay(modele, get_delay(modele) + 1);
}

static gboolean on_expose(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
    struct AppControleur_t *app = (struct AppControleur_t *) data;

    GdkWindow *window = gtk_widget_get_window(widget);
    cairo_t *context = gdk_cairo_create(window);
    PieceControleur *piece = get_current_pieces(get_modele(app->vue));

    clear_grill(context);
    summerize(app);
    draw_grill(app, context);

    if (piece != NULL)
    {
        draw_piece(
            piece, context, 
            GRILL_CELL_SIZE, 
            GRILL_CELL_MARGING
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

    g_signal_connect(
        G_OBJECT(app->arrow_right), "clicked", 
        G_CALLBACK(on_button_arrow_right_pressed), (gpointer) app
    );

    g_signal_connect(
        G_OBJECT(app->arrow_left), "clicked", 
        G_CALLBACK(on_button_arrow_left_pressed), (gpointer) app
    );
}

static PieceControleur *generate_piece()
{
    PieceControleur *result;
    TypePiece type;

    switch (abs(rand())%7)
    {
        case 0:
            type = TE;
            break;
        
        case 1:
            type = L_NORMAL;
            break;
        
        case 2:
            type = L_INVERSE;
            break;
        
        case 3:
            type = BIAIS;
            break;
        
        case 4:
            type = BIAIS_INVERSE;
            break;
        
        case 5:
            type = BATON;
            break;
        
        case 6:
            type = BLOC;
            break;
    
        default:
            break;
    }

    result = create_piece_controleur(type);
    set_position_y(get_piece_model(get_piece_vue(result)), 0);
    set_position_x(get_piece_model(get_piece_vue(result)), (unsigned int) (GRILL_WIDTH/2 - SHEMA_EDGES/2));

    return result;
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
        current = generate_piece();
        set_current_pieces(get_modele(app->vue), current);
    }

    if (app->can_draw)
    {
        gtk_widget_queue_draw(app->grill);

        PieceModel *piece_m = get_piece_model(get_piece_vue(current));
        

        if (!is_down_collision(app, piece_m))
        {
            update_gravity(
                get_piece_model(
                    get_piece_vue(current)
                )
            );
        }
        else
        {
            fill_grill(app, current);
            destroy_piece_controleur(current);
            current = generate_piece();
            set_current_pieces(get_modele(app->vue), current);
        }
    }

    update_score_label(app->vue);
    update_delay_label(app->vue);
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