#include "modal_modele.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct ModalModele_t{
    ModalType type;
    ModalUser *users;
    char *username;
};

struct ModalModele_t *create_modal_modele(void)
{
    struct ModalModele_t *result = malloc(sizeof(struct ModalModele_t));

    if (result == NULL)
        return NULL;
    
    result->users = NULL;
    result->username = NULL;
    

    return result;
}

void destroy_modal_modele(struct ModalModele_t *modal)
{
    assert(modal != NULL);

    if(modal->users != NULL)
    {
        ModalUser *user = modal->users, *tmp;

        while (user->next)
        {
            tmp = user;
            user = user->next;
            free(tmp);
        }

        free(user);
    }

    if(modal->username != NULL)
        free(modal->username);
    free(modal);
}

void set_username(struct ModalModele_t *modal, char *username)
{
    assert(modal != NULL);
    modal->username = username;
}

char *get_username(struct ModalModele_t *modal)
{
    assert(modal != NULL);

    return modal->username;
}

ModalUser *get_user_list(struct ModalModele_t *modal)
{
    assert(modal != NULL);
    return modal->users;
}

void add_user(struct ModalModele_t *modal, ModalUser *user)
{
    assert(modal != NULL);
    user->next = modal->users;
    if(modal->users != NULL)
        modal->users->prev = user;
    modal->users = user;
}

void set_modal_type(struct ModalModele_t *modal, ModalType type)
{
    assert(modal != NULL);
    modal->type = type;
}

ModalType get_modal_type(struct ModalModele_t *modal)
{
    assert(modal != NULL);
    return modal->type;
}

void swap_user( ModalUser* m1, ModalUser* m2){
    int val_score = m1->score;
    m1->score = m2->score;
    m2->score = val_score;

    char tmp[USERNAME_MAX_LENGTH + 1]; 
    strcpy(tmp, m1->username); 
    strcpy(m1->username, m2->username); 
    strcpy(m2->username, tmp); 

}

void sort_modal_user(struct ModalModele_t *modal){
    int swapped = 1;
    while (swapped == 1){
        swapped = 0;
        ModalUser* tmp = modal-> users;
        while(tmp->next != NULL){
            if ( tmp ->score > tmp ->next->score ){
                swap_user(tmp, tmp->next);
                swapped = 1;
            }
            tmp = tmp -> next;
        }
    }
}

