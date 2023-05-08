#include "modal_controleur.h"
#include "tools.h"

#include <stdlib.h>
#include <assert.h>
#include <gtk/gtk.h>

struct ModalControleur_t{
    ModalVue *vue;
    GtkWidget *window;
};

struct ModalControleur_t *create_modal_controleur(void)
{
    struct ModalControleur_t *result = malloc(sizeof(struct ModalControleur_t));

    if(result == NULL)
        return NULL;
    
    result->vue = create_modal_vue();

    if (result->vue == NULL)
    {
        free(result);
        return NULL;
    }

    return result;
}

void destroy_modal_controleur(struct ModalControleur_t *modal)
{
    assert(modal != NULL);
    destroy_modal_vue(modal->vue);
    free(modal);
}

void modal_init(struct ModalControleur_t *modal, ModalType type)
{
    assert(modal != NULL);

    switch (type)
    {
        case TYPE_HELP:
            init_for_help(modal->vue);
            break;

        case TYPE_PLAYER_LIST:
            init_for_best_score(modal->vue);
            break;

        case TYPE_USERNAME:
            init_for_username(modal->vue);
        break;
    }

    modal->window = get_modal_window(modal->vue);
}

void modal_launch(struct ModalControleur_t *modal)
{
    assert(modal != NULL);
    gtk_widget_show_all(get_modal_window(modal->vue));
    gtk_dialog_run(GTK_DIALOG(get_modal_window(modal->vue)));
}

void modal_on_response(struct ModalControleur_t *modal, gpointer needed, void (* callback)(GtkWidget *widget, gpointer data))
{
    assert(modal != NULL && callback != NULL);
    g_signal_connect(
        G_OBJECT(get_modal_button(modal->vue)), "released",  
        G_CALLBACK(*callback), needed
    );
}

void modal_on_close(struct ModalControleur_t *modal, gpointer needed, gboolean (* callback)(GtkWidget *widget, GdkEvent *event, gpointer data))
{
    assert(modal != NULL && callback != NULL);
    g_signal_connect(
        G_OBJECT(get_modal_window(modal->vue)), "delete-event",  
        G_CALLBACK(*callback), needed
    );
}

struct ModalControleur_t *new_modal(ModalType type)
{
    struct ModalControleur_t *result = create_modal_controleur();

    if (result == NULL)
        return NULL;

    modal_init(result, type);

    return result;   
}

ModalVue *get_modal_vue(struct ModalControleur_t *modal)
{
    assert(modal != NULL);
    return modal->vue;
}