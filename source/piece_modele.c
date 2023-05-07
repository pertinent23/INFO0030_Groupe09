#include "piece_modele.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

struct PieceModel_t{
    TypePiece type;
    unsigned int shema[SHEMA_EDGES][SHEMA_EDGES];
    unsigned int x, y;
    double gravity;
    int angle;
};

static void initialize_piece(struct PieceModel_t *piece, TypePiece type)
{
    for(unsigned int i = 0; i < SHEMA_EDGES; i++)
    {
        for(unsigned int j = 0; j < SHEMA_EDGES; j++)
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
    result->gravity = 0.0;

    initialize_piece(result, type);

    return result;
}

void destroy_piece(struct PieceModel_t *piece)
{
    assert(piece != NULL);

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

    return piece->y + (unsigned int) floor(piece->gravity);
}

double get_gravity(struct PieceModel_t *piece)
{
    return piece->gravity - floor(piece->gravity);
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

void update_gravity(struct PieceModel_t *piece)
{
    piece->gravity += GRAVITY_RATE;
}

int collision(struct PieceModel_t *piece, unsigned int *wall, unsigned int wall_length)
{
    assert(piece != NULL && wall != NULL && wall_length > 0);
    for(unsigned int i = piece->x, j = 0; i<wall_length && j < SHEMA_EDGES; i++, j++)
    {
        for (unsigned int k = 0; k < SHEMA_EDGES; k++)
        {
            if (wall[i] + piece->shema[3][j] == 2 )
                return 1;
        }
    }

    return 0;
}

struct PieceModel_t *rotate_left(struct PieceModel_t *piece)
{
    assert(piece != NULL);

    struct PieceModel_t *result = create_piece(piece->type);

    if (result == NULL)
        return NULL;

    for(int i = 0; i < SHEMA_EDGES; i++)
    {
        for(int j = 0; j < SHEMA_EDGES; j++)
            result->shema[j][-i+SHEMA_EDGES-1] = piece->shema[i][j];
    }

    result->angle += ROTATION_LEVEL;
    result->angle %= 360;
    result->x = piece->x;
    result->y = piece->y;
    result->gravity = piece->gravity;

    return result;
}

struct PieceModel_t *rotate_right(struct PieceModel_t *piece)
{
    assert(piece != NULL);

    struct PieceModel_t *result = create_piece(piece->type);

    if (result == NULL)
        return NULL;

    for(int i = 0; i < SHEMA_EDGES; i++)
    {
        for(int j = 0; j < SHEMA_EDGES; j++)
            result->shema[-j+SHEMA_EDGES-1][i] = piece->shema[i][j];
    }

    result->angle -= ROTATION_LEVEL;
    result->angle %= 360;
    result->x = piece->x;
    result->y = piece->y;
    result->gravity = piece->gravity;

    return result;
}

TypePiece get_piece_type(struct PieceModel_t *piece)
{
    assert(piece != NULL);
    return piece->type;
}

unsigned int get_shema_item(struct PieceModel_t *piece, unsigned int x, unsigned int y)
{
    assert(piece != NULL && x < SHEMA_EDGES && y < SHEMA_EDGES);
    return piece->shema[x][y];
}