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
            piece->shema[0][0] = piece->shema[0][1] = piece->shema[1][1] = piece->shema[1][2] = 1;
            break;
        
        case BIAIS_INVERSE:
            piece->shema[0][1] = piece->shema[0][2] = piece->shema[1][0] = piece->shema[1][1] = 1;
            break;
    
        default:
            break;
    }
} 

static void recenter(struct PieceModel_t *piece)
{
    while (
        piece->shema[0][0] == piece->shema[0][1] && 
        piece->shema[0][1] == piece->shema[0][2] && 
        piece->shema[0][2] == piece->shema[0][3] && 
        piece->shema[0][3] == 0
    )
    {
        for(int x = 1; x<SHEMA_EDGES; x++)
        {
            for (int y = 0; y < SHEMA_EDGES; y++)
            {
                piece->shema[x-1][y] = piece->shema[x][y];
                piece->shema[x][y] = 0;
            }
        }
    }

    while (
        piece->shema[0][0] == piece->shema[1][0] && 
        piece->shema[1][0] == piece->shema[2][0] && 
        piece->shema[2][0] == piece->shema[3][0] && 
        piece->shema[3][0] == 0
    )
    {
        for(int y = 1; y<SHEMA_EDGES; y++)
        {
            for (int x = 0; x < SHEMA_EDGES; x++)
            {
                piece->shema[x][y-1] = piece->shema[x][y];
                piece->shema[x][y] = 0;
            }
        }
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

int collision_down(struct PieceModel_t *piece, void ***wall, unsigned int wall_length, unsigned int h)
{
    assert(piece != NULL && wall != NULL && h >= get_position_y(piece));

    unsigned int y = h - get_position_y(piece) - 1;
    unsigned int a = get_position_x(piece), b = 0;

    while(a + b < wall_length && b < SHEMA_EDGES)
    {
        if (wall[h][a + b] != NULL && piece->shema[y][b] == 1)
        {
            return 1;
        }

        b++;
    }

    return 0;
}

int collision_right(struct PieceModel_t *piece, void ***wall, unsigned int wall_length, unsigned int h)
{
    assert(piece != NULL && wall != NULL && h >= get_position_x(piece));

    unsigned int x = h - get_position_x(piece) - 1;
    unsigned int a = get_position_y(piece), b = 0;

    while(a + b < wall_length && b < SHEMA_EDGES)
    {
        if (wall[a + b][h] != NULL && piece->shema[b][x] == 1)
        {
            return 1;
        }
        
        b++;
    }

    return 0;
}

int collision_left(struct PieceModel_t *piece, void ***wall, unsigned int wall_length, unsigned int h)
{
    assert(piece != NULL && wall != NULL && h >= get_position_x(piece));

    unsigned int x = get_position_x(piece) - h - 1;
    unsigned int a = get_position_y(piece), b = 0;

    while(a + b < wall_length && b < SHEMA_EDGES)
    {
        if (wall[a + b][h] != NULL && piece->shema[b][x] == 1)
        {
            return 1;
        }
        
        b++;
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

    recenter(result);

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

    recenter(result);

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
    return piece->shema[y][x];
}