#include "app_modele.h"

#include <stdlib.h>
#include <assert.h>

struct AppModele_t{
    PieceControleur *current;
    unsigned int **grill;
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

    result->grill = malloc(sizeof(unsigned int *) * result->width);

    if (result->grill == NULL)
    {
        free(result);
        return NULL;
    }

    for(int k = 0; k < (int) result->width; k++)
    {
        result->grill[k] = malloc(sizeof(unsigned int) * result->height);

        if (result->grill[k] ==  NULL)
        {
            for(; k>=0; k--)
                free(result->grill[k]);
            free(result->grill);
            free(result);
            return NULL;
        }
    }

    result->current = NULL;

    return result;
}

void destroy_app(struct AppModele_t *app)
{
    assert(app != NULL);

    for (unsigned int i = 0; i < app->width; i++)
        free(app->grill[i]);
    
    free(app->grill);
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