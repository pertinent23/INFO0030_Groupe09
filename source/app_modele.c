#include "app_modele.h"

#include <stdlib.h>
#include <assert.h>

struct AppModele_t{
    PieceControleur *current;
    Color ***grill;
    unsigned int width, height;
    unsigned int score;
    unsigned int delay;
};

struct AppModele_t *create_app(void)
{
    struct AppModele_t *result = malloc(sizeof(struct AppModele_t));

    if (result == NULL)
        return NULL;
    
    result->width = GRILL_WIDTH;
    result->height = GRILL_HEIGHT;

    result->grill = malloc(sizeof(Color **) * (result->height+1));

    if (result->grill == NULL)
    {
        free(result);
        return NULL;
    }

    for(int k = 0; k < (int) (result->height+1); k++)
    {
        result->grill[k] = malloc(sizeof(Color *) * (result->width+1));

        if (result->grill[k] ==  NULL)
        {
            for(; k>=0; k--)
                free(result->grill[k]);
            free(result->grill);
            free(result);
            return NULL;
        }
    }

    for (unsigned int x = 0; x < result->width+1; x++)
    {
        for (unsigned int y = 0; y < result->height+1; y++)
        {
            if (x==result->width || y==result->height)
            {
                result->grill[y][x] = &DARK;
            }
            else
            {
                result->grill[y][x] = NULL;
            }
        }
    }
    

    result->current = NULL;

    return result;
}

void destroy_app(struct AppModele_t *app)
{
    assert(app != NULL);

    for (unsigned int i = 0; i < app->height+1; i++)
        free(app->grill[i]);
    
    free(app->grill);

    if (app->current != NULL)
        destroy_piece_controleur(app->current);
        
    free(app);
}

PieceControleur *get_current_pieces(struct AppModele_t *app)
{
    assert(app !=  NULL);

    return app->current;
}

void set_current_pieces(struct AppModele_t *app, PieceControleur *data)
{
    assert(app != NULL);

    app->current = data;
}

unsigned int get_grill_width(struct AppModele_t *app)
{
    assert(app != NULL);

    return app->width;
}

unsigned int get_grill_height(struct AppModele_t *app)
{
    assert(app != NULL);

    return app->height;
}

void set_score(struct AppModele_t *app, unsigned int score)
{
    assert(app != NULL);
    app->score = score;
}

void set_deplay(struct AppModele_t *app, unsigned int delay)
{
    assert(app != NULL);
    app->delay = delay;
}

unsigned int get_score(struct AppModele_t *app)
{
    assert(app != NULL);
    return app->score;
}

unsigned int get_delay(struct AppModele_t *app)
{
    assert(app != NULL);
    return app->delay;
}

Color *get_pixel(struct AppModele_t *app, unsigned int x, unsigned int y)
{
    assert(app != NULL);
    return app->grill[y][x];
}

Color ***get_pixels(struct AppModele_t *app)
{
    assert(app != NULL);
    return app->grill;
}


void set_pixel(struct AppModele_t *app, Color *color, unsigned int x, unsigned y)
{
    assert(app != NULL);
    app->grill[y][x] = color;
}