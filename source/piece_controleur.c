#include "piece_controleur.h"
#include <assert.h>

struct PieceControleur_t{
    PieceVue *vue;
    unsigned int collision_left;
    unsigned int collision_right;
    unsigned int collision_bottom;
};

struct PieceControleur_t *create_piece_controleur(TypePiece type)
{
    struct PieceControleur_t *result = malloc(sizeof(struct PieceControleur_t));

    if (result == NULL)
        return NULL;
    
    result->vue = create_piece_vue(type);

    if (result->vue == NULL)
    {
        free(result);
        return NULL;
    }

    result->collision_bottom = 0;
    result->collision_right = 0;
    result->collision_left = 0;

    return result;
}

PieceVue *get_piece_vue(struct PieceControleur_t *controleur)
{
    assert(controleur != NULL);
    return controleur->vue;
}

void destroy_piece_controleur(struct PieceControleur_t *controleur)
{
    assert(controleur != NULL);
    destroy_piece_vue(controleur->vue);
    free(controleur);
}