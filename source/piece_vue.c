#include "piece_vue.h"
#include <stdlib.h>
#include <assert.h>

struct PieceVue_t
{
    PieceModel *modele;
    unsigned int color_r;
    unsigned int color_g;
    unsigned int color_b;
};

static void init_color(struct PieceVue_t * vue)
{
    switch (get_piece_type(vue->modele))
    {
        case BLOC:
            vue->color_r = 242;
            vue->color_g = 226;
            vue->color_b = 5;
            break;
        
        case TE:
            vue->color_r = 147;
            vue->color_g = 5;
            vue->color_b = 242;
            break;
        
        case L_NORMAL:
            vue->color_r = 255;
            vue->color_g = 165;
            vue->color_b = 0;
            break;
        
        case L_INVERSE:
            vue->color_r = 0;
            vue->color_g = 0;
            vue->color_b = 255;
            break;
        
        case BIAIS:
            vue->color_r = 242;
            vue->color_g = 5;
            vue->color_b = 5;
            break;
        
        case BIAIS_INVERSE:
            vue->color_r = 13;
            vue->color_g = 242;
            vue->color_b = 5;
            break;
        
        case BATON:
            vue->color_r = 0;
            vue->color_g = 255;
            vue->color_b = 255;
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

unsigned int get_color_r(struct PieceVue_t *vue)
{
    assert(vue != NULL);
    return vue->color_r;
}

unsigned int get_color_g(struct PieceVue_t *vue)
{
    assert(vue != NULL);
    return vue->color_g;
}

unsigned int get_color_b(struct PieceVue_t *vue)
{
    assert(vue != NULL);
    return vue->color_b;
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