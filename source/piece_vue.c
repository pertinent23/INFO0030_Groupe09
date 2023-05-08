#include "piece_vue.h"
#include <stdlib.h>
#include <assert.h>

struct PieceVue_t
{
    PieceModel *modele;
    Color *color;
};

static void init_color(struct PieceVue_t * vue)
{
    switch (get_piece_type(vue->modele))
    {
        case BLOC:
            vue->color = &YELLOW;
            break;
        
        case TE:
            vue->color = &PURPLE;
            break;
        
        case L_NORMAL:
            vue->color = &ORANGE;
            break;
        
        case L_INVERSE:
            vue->color = &BLUE;
            break;
        
        case BIAIS:
            vue->color = &RED;
            break;
        
        case BIAIS_INVERSE:
            vue->color = &GREEN;
            break;
        
        case BATON:
            vue->color = &CIAN;
            break;

        default:
            break;
    }
}

struct PieceVue_t *create_piece_vue(TypePiece type)
{
    struct PieceVue_t *result = malloc(sizeof(struct PieceVue_t));

    if (result == NULL)
        return NULL;

    result->modele = create_piece(type);

    if (result->modele == NULL)
    {
        free(result);
        return NULL;
    }

    init_color(result);

    return result;
}

Color *get_color(struct PieceVue_t *vue)
{
    return vue->color;
}

PieceModel *get_piece_model(struct PieceVue_t *vue)
{
    assert(vue != NULL);
    return vue->modele;
}

void destroy_piece_vue(struct PieceVue_t *vue)
{
    assert(vue != NULL);
    destroy_piece(vue->modele);
    free(vue);
}

void modify_piece_model(struct PieceVue_t *vue, PieceModel *modele)
{
    assert(vue != NULL && modele != NULL);
    if(vue->modele != NULL)
        destroy_piece(vue->modele);
    vue->modele = modele;
}