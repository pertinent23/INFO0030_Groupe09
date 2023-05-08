#ifndef __MODAL_VUE__
#define __MODAL_VUE__

#include "modal_modele.h"
#include <gtk/gtk.h>

#define HELP_MODAL_WIDTH 250
#define HELP_MODAL_HEIGHT 100

#define USERNAME_MODAL_WIDTH 170
#define USERNAME_MODAL_HEIGHT 250

#define USERS_MODAL_WIDTH 400
#define USERS_MODAL_HEIGHT 500

typedef struct ModalVue_t ModalVue;

struct ModalVue_t *create_modal_vue(void);

void destroy_modal_vue(struct ModalVue_t *modal);

ModalModele *get_modal_modele(struct ModalVue_t *modal);

void init_for_best_score(struct ModalVue_t *modal);
void init_for_help(struct ModalVue_t *modal);
void init_for_username(struct ModalVue_t *modal);

GtkWidget *get_modal_window(struct ModalVue_t *modal);
GtkWidget *get_modal_button(struct ModalVue_t *modal);
GtkWidget *get_modal_username_field(struct ModalVue_t *modal);

#endif // !__MODAL_VUE__