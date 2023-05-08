#ifndef __MODAL_CONTROLEUR__
#define __MODAL_CONTROLEUR__

#include "modal_vue.h"
#include "modal_modele.h"
#include <gtk/gtk.h>

typedef struct ModalControleur_t ModalControleur;

struct ModalControleur_t *create_modal_controleur(void);

struct ModalControleur_t *new_modal(ModalType type);

ModalVue *get_modal_vue(struct ModalControleur_t *modal);

void destroy_modal_controleur(struct ModalControleur_t *modal);

void modal_init(struct ModalControleur_t *modal, ModalType type);

void modal_on_close(struct ModalControleur_t *modal, gpointer needed, gboolean (* callback)(GtkWidget *widget, GdkEvent *event, gpointer data));

void modal_on_response(struct ModalControleur_t *modal, gpointer needed, void (* callback)(GtkWidget *widget, gpointer data));

void modal_launch(struct ModalControleur_t *modal);

#endif // !__MODAL_CONTROLEUR__