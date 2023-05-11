#ifndef __MODAL_MODELE__
#define __MODAL_MODELE__

#define USERNAME_MAX_LENGTH 20

typedef struct ModalModele_t ModalModele;

typedef struct ModaleUser_t{
    char username[USERNAME_MAX_LENGTH + 1];
    unsigned int score;
    struct ModaleUser_t *next, *prev;
} ModalUser;

typedef enum ModalType_e{
    TYPE_PLAYER_LIST = 17, TYPE_USERNAME, TYPE_HELP
} ModalType;

struct ModalModele_t *create_modal_modele(void);

void destroy_modal_modele(struct ModalModele_t *modal);

void set_username(struct ModalModele_t *modal, char *username);

void set_modal_type(struct ModalModele_t *modal, ModalType type);

char *get_username(struct ModalModele_t *modal);

ModalUser *get_user_list(struct ModalModele_t *modal);

ModalType get_modal_type(struct ModalModele_t *modal);

void add_user(struct ModalModele_t *modal, ModalUser *user);

void swap_user( ModalUser* m1, ModalUser* m2)

void sort_modele(struct ModalModele_t *modal);

#endif // !__MODAL_MODELE__