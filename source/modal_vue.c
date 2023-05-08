#include "modal_vue.h"

#include <stdlib.h>
#include <assert.h>

struct ModalVue_t{
    ModalModele *modele;
    GtkWidget *window;
    GtkWidget *container;
    GtkWidget *button;

    struct {
        GtkWidget *field;
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
    modal->container = gtk_vbox_new(FALSE, 10);
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

    gtk_box_pack_start(GTK_BOX(modal->container), modal->help_widget.label, TRUE, TRUE, 25);
    gtk_box_pack_start(GTK_BOX(modal->container), modal->button, FALSE, FALSE, 15);
}

void init_for_username(struct ModalVue_t *modal)
{
    assert(modal != NULL);

    modal->username_widget.label = gtk_label_new("Pseudo:");
    modal->username_widget.field = gtk_entry_new();

    init_modal(modal);
    set_modal_type(modal->modele, TYPE_USERNAME);
    gtk_entry_set_max_length(GTK_ENTRY(modal->username_widget.field), USERNAME_MAX_LENGTH);
    gtk_button_set_label(GTK_BUTTON(modal->button), "Confirm");
    gtk_window_set_default_size(GTK_WINDOW(modal->window), USERNAME_MODAL_WIDTH, USERNAME_MODAL_HEIGHT);

    gtk_box_pack_start(GTK_BOX(modal->container), modal->username_widget.label, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(modal->container), modal->username_widget.field, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(modal->container), modal->button, FALSE, FALSE, 0);
}

void init_for_best_score(struct ModalVue_t *modal)
{
    assert(modal != NULL);
    
    init_modal(modal);
    set_modal_type(modal->modele, TYPE_PLAYER_LIST);
    gtk_window_set_default_size(GTK_WINDOW(modal->window), USERS_MODAL_WIDTH, USERS_MODAL_HEIGHT);
    gtk_box_pack_start(GTK_BOX(modal->container), modal->button, FALSE, FALSE, 0);
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

    if (modal->window)
        gtk_widget_destroy(modal->window);
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