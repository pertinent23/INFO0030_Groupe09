#ifndef __MODAL_VUE__
#define __MODAL_VUE__

#include "modal_modele.h"
#include <gtk/gtk.h>

#define HELP_MODAL_WIDTH 200
#define HELP_MODAL_HEIGHT 100

#define USERNAME_MODAL_WIDTH 250
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
void add_users(struct ModalVue_t *modal);

GtkWidget *get_modal_window(struct ModalVue_t *modal);
GtkWidget *get_modal_button(struct ModalVue_t *modal);
GtkWidget *get_modal_username_field(struct ModalVue_t *modal);

const char *get_username_from_entry(struct ModalVue_t *modal);

int is_valid_username(struct ModalVue_t *modal);

void set_error(struct ModalVue_t *modal, const char *error);

#endif // !__MODAL_VUE__