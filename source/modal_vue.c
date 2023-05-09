#include "modal_vue.h"

#include <stdlib.h>
#include <assert.h>

enum{
    COLUMN_ID,
    COLUMN_PSEUDO,
    COLUMN_SCORE,
    NUM_COLUMNS
};

struct ModalVue_t{
    ModalModele *modele;
    GtkWidget *scrolled;
    GtkWidget *view;
    GtkWidget *window;
    GtkWidget *container;
    GtkWidget *button;

    struct {
        GtkWidget *field;
        GtkWidget *error;
        GtkWidget *label;
    } username_widget;

    struct {
        GtkWidget *label;
    } help_widget;
};

static void init_modal(struct ModalVue_t *modal)
{
    assert(modal != NULL);

    modal->window = gtk_dialog_new();
    modal->container = gtk_table_new(7, 7, TRUE);
    modal->button = gtk_button_new_with_label("Ok");

    gtk_container_add(
        GTK_CONTAINER(
            gtk_dialog_get_content_area(
                GTK_DIALOG(modal->window)
            )
        ),
        modal->container
    );
}

void init_for_help(struct ModalVue_t *modal)
{
    assert(modal != NULL);

    modal->help_widget.label = gtk_label_new("Made by Franck Duval HEUBA & Nabila ANBARI");

    init_modal(modal);
    set_modal_type(modal->modele, TYPE_HELP);
    gtk_window_set_default_size(GTK_WINDOW(modal->window), HELP_MODAL_WIDTH, HELP_MODAL_HEIGHT);

    gtk_table_attach(
        GTK_TABLE(modal->container), modal->help_widget.label,
        1, 6, 1, 4, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0
    );

    gtk_table_attach(
        GTK_TABLE(modal->container), modal->button,
        2, 5, 5, 6, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0
    );
}

void init_for_username(struct ModalVue_t *modal)
{
    assert(modal != NULL);

    modal->username_widget.label = gtk_label_new("Pseudo:");
    modal->username_widget.error = gtk_label_new(NULL);
    modal->username_widget.field = gtk_entry_new();

    init_modal(modal);
    set_modal_type(modal->modele, TYPE_USERNAME);

    gtk_button_set_label(GTK_BUTTON(modal->button), "Confirm");
    gtk_entry_set_max_length(GTK_ENTRY(modal->username_widget.field), USERNAME_MAX_LENGTH);
    gtk_window_set_default_size(GTK_WINDOW(modal->window), USERNAME_MODAL_WIDTH, USERNAME_MODAL_HEIGHT);

    gtk_table_attach(
        GTK_TABLE(modal->container), modal->username_widget.label,
        1, 2, 1, 2, GTK_EXPAND, GTK_EXPAND|GTK_FILL, 0, 0
    );

    gtk_table_attach(
        GTK_TABLE(modal->container), modal->username_widget.field,
        1, 6, 2, 3, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0
    );

    gtk_table_attach(
        GTK_TABLE(modal->container), modal->username_widget.error,
        1, 2, 3, 4, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0
    );

    gtk_table_attach(
        GTK_TABLE(modal->container), modal->button,
        2, 5, 5, 6, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0
    );
}

void add_users(struct ModalVue_t *modal)
{
    modal->view = gtk_tree_view_new();

    /**
     * @brief 
     * Creation of the list store which will
     * stock all data
    */

    GtkTreeIter iter;
    unsigned int id = 0;
    ModalUser *user = get_user_list(modal->modele);
    GtkListStore *list = gtk_list_store_new(NUM_COLUMNS, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT);

    while(user != NULL)
    {
        gtk_list_store_append(list, &iter);
        gtk_list_store_set(list, &iter, COLUMN_ID, id, COLUMN_PSEUDO, user->username, COLUMN_SCORE, user->score, -1);
        user = user->next;
    }

    /**
     * @brief 
     * Creation of the tree which will
     * stock all columns 
    */

    GtkTreeModel *model = GTK_TREE_MODEL(list);

    gtk_tree_view_insert_column_with_attributes(
        GTK_TREE_VIEW(modal->view), -1, "ID",
        gtk_cell_renderer_text_new(), "text", 
        COLUMN_ID, NULL
    );

    gtk_tree_view_insert_column_with_attributes(
        GTK_TREE_VIEW(modal->view), -1, "Pseudo",
        gtk_cell_renderer_text_new(), "text", 
        COLUMN_PSEUDO, NULL
    );

    gtk_tree_view_insert_column_with_attributes(
        GTK_TREE_VIEW(modal->view), -1, "Score",
        gtk_cell_renderer_text_new(), "text", 
        COLUMN_SCORE, NULL
    );

    gtk_tree_view_set_model(GTK_TREE_VIEW(modal->view), model);
    g_object_unref(model);

    gtk_container_add(GTK_CONTAINER(modal->scrolled), modal->view);
}

void init_for_best_score(struct ModalVue_t *modal)
{
    assert(modal != NULL);

    modal->scrolled = gtk_scrolled_window_new(NULL, NULL);
    
    init_modal(modal);
    set_modal_type(modal->modele, TYPE_PLAYER_LIST);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(modal->scrolled), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_table_resize(GTK_TABLE(modal->container), 11, 11);
    gtk_window_set_default_size(GTK_WINDOW(modal->window), USERS_MODAL_WIDTH, USERS_MODAL_HEIGHT);

    gtk_table_attach(
        GTK_TABLE(modal->container), modal->scrolled,
        0, 11, 1, 9, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0
    );
    
    gtk_table_attach(
        GTK_TABLE(modal->container), modal->button,
        4, 7, 10, 11, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0
    );
}

struct ModalVue_t *create_modal_vue(void)
{
    struct ModalVue_t *result = malloc(sizeof(struct ModalVue_t));

    if(result == NULL)
        return NULL;
    
    result->modele = create_modal_modele();

    if (result->modele == NULL)
    {
        free(result);
        return NULL;
    }

    return result;
}

void destroy_modal_vue(struct ModalVue_t *modal)
{
    assert(modal != NULL);
    if (modal->window)
        gtk_widget_destroy(modal->window);
    destroy_modal_modele(modal->modele);
    free(modal);
}


ModalModele *get_modal_modele(struct ModalVue_t *modal)
{
    assert(modal != NULL);
    return modal->modele;
}

GtkWidget *get_modal_window(struct ModalVue_t *modal)
{
    assert(modal != NULL);
    return modal->window;
}

GtkWidget *get_modal_button(struct ModalVue_t *modal)
{
    assert(modal != NULL);
    return modal->button;
}

GtkWidget *get_modal_username_field(struct ModalVue_t *modal)
{
    assert(modal != NULL);
    return modal->username_widget.field;
}