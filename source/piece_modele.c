#include "piece_modele.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SHEMA_EDGES 4

struct PieceModel_t{
    TypePiece type;
    unsigned int shema[SHEMA_EDGES][SHEMA_EDGES];
    unsigned int x, y;
    int angle;
};

static void initialize_piece(struct PieceModel_t *piece, TypePiece type)
{
    for(int i = 0; i < SHEMA_EDGES; i++)
    {
        for(int j = 0; j < SHEMA_EDGES; j++)
            piece->shema[i][j] = 0;
    }

    switch (type)
    {
        case BLOC:
            piece->shema[0][0] = piece->shema[0][1] = piece->shema[1][0] = piece->shema[1][1] = 1;
            break;

        case TE:
            piece->shema[0][0] = piece->shema[0][1] = piece->shema[0][2] = piece->shema[1][1] = 1;
            break;

        case BATON:
            piece->shema[0][0] = piece->shema[0][1] = piece->shema[0][2] = piece->shema[0][3] = 1;
            break;
        
        case L_NORMAL:
            piece->shema[0][0] = piece->shema[0][1] = piece->shema[0][2] = piece->shema[1][0] = 1;
            break;
        
        case L_INVERSE:
            piece->shema[0][0] = piece->shema[0][1] = piece->shema[0][2] = piece->shema[1][2] = 1;
            break;

        case BIAIS:
            piece->shema[0][0] = piece->shema[0][1] = piece->shema[1][2] = piece->shema[1][3] = 1;
            break;
        
        case BIAIS_INVERSE:
            piece->shema[0][2] = piece->shema[0][3] = piece->shema[1][0] = piece->shema[1][1] = 1;
            break;
    
        default:
            break;
    }
} 

struct PieceModel_t *create_piece(TypePiece type) 
{
    struct PieceModel_t *result = malloc(sizeof(struct PieceModel_t));

    if (result == NULL)
        return NULL;
    
    result->type = type;
    result->angle = 0;

    initialize_piece(result, type);

    return result;
}

void destroy_piece(struct PieceModel_t *piece)
{
    aseert(piece != NULL);

    free(piece);
}

unsigned int get_position_x(struct PieceModel_t *piece)
{
    assert(piece != NULL);

    return piece->x;
}

unsigned int get_position_y(struct PieceModel_t *piece)
{
    assert(piece != NULL);

    return piece->y;
}

void set_position_x(struct PieceModel_t *piece, unsigned int x)
{
    assert(piece != NULL);

    piece->x = x;
}

void set_position_y(struct PieceModel_t *piece, unsigned int y)
{
    assert(piece != NULL);

    piece->y = y;
}

int collision(struct PieceModel_t *piece, unsigned int *wall, unsigned int wall_length)
{
    for(int i = piece->x, j = 0; i<wall_length && j < SHEMA_EDGES; i++ && j++)
    {
        if (wall[i] + piece->shema[j] == 2 )
            return 1;
    }

    return 0;
}

void rotate_left(struct PieceModel_t *piece)
{
    unsigned int tmp;

    for(int i = 0; i < SHEMA_EDGES; i++)
    {
        for(int j = 0; j < SHEMA_EDGES; j++)
        {
            switch (piece->angle)
            {
                case 0:
                    tmp = piece->shema[i][j];
                    piece->shema[i][j] = piece->shema[j][i];
                    piece->shema[j][i] = tmp;
                    break;
                
                case 90:
                    tmp = piece->shema[i][j];
                    break;

                default:
                    break;
            }
        }
    }
}