#include "modal_modele.h"

#include <stdlib.h>
#include <assert.h>

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
        ModalUser *user, *tmp;

        while (user->next)
        {
            tmp = user;
            user = user->next;

            free(tmp->username);
            free(tmp);
        }

        free(user->username);
        free(user);
    }

    if(modal->username != NULL)
    {
        free(modal->username);
    }

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
    assert(modal != modal);
    user->next = modal->users;
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

void sort_modal_user(struct ModalModele_t *modal)
{
    assert(modal != NULL);

    if (modal->users != NULL)
    {
        unsigned int permutation = -1;
        ModalUser *users, *tmp1, *tmp2;

        while (permutation != 0)
        {
            permutation = 0;
            users = modal->users;
            while (users->next)
            {
                if (users->next->score > users->score)
                {
                    tmp1 = users;
                    tmp2 = users->next;

                    tmp1->next = tmp2->next;
                    tmp2->prev = tmp1->prev;
                    tmp1->prev = tmp2;
                    tmp2->next = tmp1;

                    users = tmp2;

                    permutation++;
                }

                users = users->next;
            }

            while (users->prev)
                users = users->prev;

            modal->users = users;
        }
    }
}