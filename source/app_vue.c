#include "app_vue.h"
#include "app_modele.h"
#include "tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct AppVue_t{
    AppModele *modele;

    GtkWidget *window;
    GtkWidget *menu;
    GtkWidget *menu_bar;
    GtkWidget *windowContainer;
    GtkWidget *footer;
    GtkWidget *grill_side;
    GtkWidget *options;

    struct {
        GtkWidget *new;
        GtkWidget *quit;
        GtkWidget *best;
        GtkWidget *help;
        GtkWidget *round;
    } menu_items;

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

    struct {
        GtkWidget *score; 
        GtkWidget *delay; 
    } labels;
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
    assert(vue != NULL);
    return vue->modele;
}

void destroy_app_vue(struct AppVue_t *vue)
{
    assert(vue != NULL);

    destroy_app(vue->modele);

    free(vue);
}

void create_window(struct AppVue_t *vue)
{
    assert(vue != NULL);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GdkGeometry geometry;

    geometry.min_width = WINDOW_WIDTH;
    geometry.min_height = WINDOW_HEIGHT;

    gtk_window_set_title(GTK_WINDOW(window), "TETRIS");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_geometry_hints(GTK_WINDOW(window), NULL, &geometry, GDK_HINT_MIN_SIZE);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    set_color(window, "#282A36");

    vue->window = window;
}


void create_window_container(struct AppVue_t *vue)
{
    assert(vue != NULL);

    vue->windowContainer = gtk_table_new(11, 12, TRUE);

    create_menu(vue);
    create_footer(vue);
    create_grill_side(vue);
    create_options(vue);

    gtk_table_attach(GTK_TABLE(vue->windowContainer), vue->menu_bar, 0, 12, 0, 1, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(vue->windowContainer), vue->grill_side, 1, 7, 2, 8, GTK_EXPAND, GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(vue->windowContainer), vue->footer, 3, 5, 9, 10, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(vue->windowContainer), vue->options, 8, 11, 2, 8, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
}

void create_menu(struct AppVue_t *vue)
{
    assert(vue != NULL);

    vue->menu_bar = gtk_menu_bar_new();
    vue->menu = gtk_menu_new();

    vue->menu_items.quit = gtk_menu_item_new_with_mnemonic("_Quit");
    vue->menu_items.best = gtk_menu_item_new_with_mnemonic("_Best Score");
    vue->menu_items.new = gtk_menu_item_new_with_mnemonic("_New");
    vue->menu_items.help = gtk_menu_item_new_with_mnemonic("_Help");
    vue->menu_items.round = gtk_menu_item_new_with_label("Round");

    gtk_menu_shell_append(GTK_MENU_SHELL(vue->menu), vue->menu_items.new);
    gtk_menu_shell_append(GTK_MENU_SHELL(vue->menu), vue->menu_items.best);
    gtk_menu_shell_append(GTK_MENU_SHELL(vue->menu), gtk_separator_menu_item_new());
    gtk_menu_shell_append(GTK_MENU_SHELL(vue->menu), vue->menu_items.quit);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(vue->menu_items.round), vue->menu);

    gtk_menu_shell_append(GTK_MENU_SHELL(vue->menu_bar), vue->menu_items.round);
    gtk_menu_shell_append(GTK_MENU_SHELL(vue->menu_bar), vue->menu_items.help);
}

void create_footer(struct AppVue_t *vue)
{
    assert(vue != NULL);

    vue->footer = gtk_table_new(5, 3, TRUE);


    gtk_table_attach(
        GTK_TABLE(vue->footer), 
        create_arrow(vue, GTK_ARROW_UP),
        1, 2, 0, 1, GTK_EXPAND, GTK_EXPAND, 0, 0
    );

    gtk_table_attach(
        GTK_TABLE(vue->footer), 
        create_arrow(vue, GTK_ARROW_DOWN),
        1, 2, 2, 3, GTK_EXPAND, GTK_EXPAND, 0, 0
    );

    gtk_table_attach(
        GTK_TABLE(vue->footer), 
        create_arrow(vue, GTK_ARROW_LEFT),
        0, 1, 1, 2, GTK_EXPAND, GTK_EXPAND, 0, 0
    );

    gtk_table_attach(
        GTK_TABLE(vue->footer), 
        create_arrow(vue, GTK_ARROW_RIGHT),
        2, 3, 1, 2, GTK_EXPAND, GTK_EXPAND, 0, 0
    );

    GtkWidget 
        *label[3];
        label[0] = create_label("MOVE LEFT", 3);
        label[1] = create_label("ROTATE", 3);
        label[2] = create_label("MOVE RIGHT", 3);

    gtk_table_attach(
        GTK_TABLE(vue->footer), 
        label[0], 0, 1, 4, 5, 
        GTK_EXPAND, GTK_EXPAND, 0, 0
    );

    gtk_table_attach(
        GTK_TABLE(vue->footer), 
        label[1], 1, 2, 4, 5, 
        GTK_EXPAND, GTK_EXPAND, 0, 0
    );

    gtk_table_attach(
        GTK_TABLE(vue->footer), 
        label[2], 2, 3, 4, 5, 
        GTK_EXPAND, GTK_EXPAND, 0, 0
    );

    set_font_color(label[0], "#B091F2");
    set_font_color(label[1], "#B091F2");
    set_font_color(label[2], "#B091F2");
}

void create_grill_side(struct AppVue_t *vue)
{
    assert(vue != NULL);

    vue->grill_side = gtk_drawing_area_new();

    set_color(vue->grill_side, "#1E1F29");
    gtk_widget_set_size_request(
        vue->grill_side, 
        GRILL_CELL_SIZE * GRILL_WIDTH, 
        GRILL_CELL_SIZE * GRILL_HEIGHT
    );
}

void create_options(struct AppVue_t *vue)
{
    assert(vue != NULL);

    vue->options = gtk_table_new(6, 1, TRUE);

    gtk_table_attach(
        GTK_TABLE(vue->options), create_buttons(vue),
        0, 1, 0, 2, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0
    );

    gtk_table_attach(
        GTK_TABLE(vue->options), create_labels(vue),
        0, 1, 4, 6, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0
    );
}

GtkWidget *create_buttons(struct AppVue_t *vue) 
{
    assert(vue != NULL);

    GtkWidget *container = gtk_table_new(3, 1, TRUE);

    set_color(container, "#1E1F29");

    vue->buttons.end = gtk_button_new_with_mnemonic("_Finish");
    vue->buttons.new = gtk_button_new_with_mnemonic("_New");

    gtk_table_attach(
        GTK_TABLE(container), vue->buttons.new,
        0, 1, 0, 1, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0
    );

    gtk_table_attach(
        GTK_TABLE(container), vue->buttons.end,
        0, 1, 2, 3, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0
    );

    return container;
}

GtkWidget *create_labels(struct AppVue_t *vue) 
{
    assert(vue != NULL);

    GtkWidget *container = gtk_table_new(3, 1, TRUE);

    vue->labels.score = gtk_label_new("Score: 0");
    vue->labels.delay = gtk_label_new("Delay: 0");

    gtk_table_attach(
        GTK_TABLE(container), vue->labels.score,
        0, 1, 0, 1, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0
    );

    gtk_table_attach(
        GTK_TABLE(container), vue->labels.delay,
        0, 1, 2, 3, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0
    );

    return container;
}

GtkWidget *create_arrow(struct AppVue_t *vue, GtkArrowType type)
{
    assert(vue != NULL);

    GtkWidget *arrow = gtk_arrow_new(type, GTK_SHADOW_OUT);
    GtkWidget *button = gtk_button_new();

    switch (type)
    {
        case GTK_ARROW_DOWN:
            vue->arrows.arrow_down = button;
            break;
        
        case GTK_ARROW_RIGHT:
            vue->arrows.arrow_right = button;
            break;
        
        case GTK_ARROW_LEFT:
            vue->arrows.arrow_left = button;
            break;
        
        case GTK_ARROW_UP:
            vue->arrows.arrow_up = button;
            break;

        default:
            break;
    }

    gtk_container_add(GTK_CONTAINER(button), arrow);
    set_color(arrow, "#B091F2");

    return button;
}

void build_app_vue(struct AppVue_t *vue)
{
    assert(vue != NULL);

    create_window(vue);
    create_window_container(vue);

    gtk_container_add(GTK_CONTAINER(vue->window), vue->windowContainer);
}

GtkWidget *get_window(struct AppVue_t *vue)
{
    assert(vue != NULL);
    return vue->window;
}

GtkWidget *get_window_container(struct AppVue_t *vue)
{
    assert(vue != NULL);
    return vue->windowContainer;
}

GtkWidget *get_grill(struct AppVue_t *vue)
{
    assert(vue != NULL);
    return vue->grill_side;
}

GtkWidget *get_arrow_up(struct AppVue_t *vue)
{
    assert(vue != NULL);
    return vue->arrows.arrow_up;
}

GtkWidget *get_arrow_down(struct AppVue_t *vue)
{
    assert(vue != NULL);
    return vue->arrows.arrow_down;
}

GtkWidget *get_arrow_left(struct AppVue_t *vue)
{
    assert(vue != NULL);
    return vue->arrows.arrow_left;
}

GtkWidget *get_arrow_right(struct AppVue_t *vue)
{
    assert(vue != NULL);
    return vue->arrows.arrow_right;
}

GtkWidget *get_menu_new(struct AppVue_t *vue)
{
    assert(vue != NULL);
    return vue->menu_items.new;
}

GtkWidget *get_menu_quit(struct AppVue_t *vue)
{
    assert(vue != NULL);
    return vue->menu_items.quit;
}

GtkWidget *get_menu_best(struct AppVue_t *vue)
{
    assert(vue != NULL);
    return vue->menu_items.best;
}

GtkWidget *get_menu_help(struct AppVue_t *vue)
{
    assert(vue != NULL);
    return vue->menu_items.help;
}

GtkWidget *get_button_new(struct AppVue_t *vue)
{
    assert(vue != NULL);
    return vue->buttons.new;
}

GtkWidget *get_button_quit(struct AppVue_t *vue)
{
    assert(vue != NULL);
    return vue->buttons.end;
}

void update_score_label(struct AppVue_t *vue)
{
    assert(vue != NULL);
    
    char data[25];
    sprintf(data, "Score: %u", get_score(vue->modele));
    gtk_label_set_label(GTK_LABEL(vue->labels.score), data);
}

void update_delay_label(struct AppVue_t *vue)
{
    assert(vue != NULL);

    char data[25];
    sprintf(data, "Delay: %u", get_score(vue->modele));
    gtk_label_set_label(GTK_LABEL(vue->labels.delay), data);
}