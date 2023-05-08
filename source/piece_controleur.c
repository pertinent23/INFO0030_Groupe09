#include "piece_controleur.h"
#include "tools.h"
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

void draw_case(cairo_t *context, Color *color, double x, double y, double gravity, unsigned int edges, unsigned int line)
{
    cairo_set_source_rgb(
        context, 
        (double) color->r/255, 
        (double) color->g/255, 
        (double) color->b/255
    );

    cairo_rectangle(context, x*edges+(x+1)*line, y*edges+(y+1)*line+gravity, edges, edges);
    cairo_fill_preserve(context);
    cairo_set_line_width(context, line);
    cairo_set_source_rgb(context, DARK.r/255, DARK.g/255, DARK.b/255);
    cairo_stroke(context);
}

void draw_piece(struct PieceControleur_t *piece, cairo_t *context, unsigned int edges, unsigned int line)
{
    PieceModel *piece_m = get_piece_model(piece->vue);
    Color *color = get_color(piece->vue);
    unsigned int xp = get_position_x(piece_m);
    unsigned int yp = get_position_y(piece_m);
    double gravity = get_gravity(piece_m);

    for(int x = 0; x<SHEMA_EDGES; x++)
    {
        for(int y = 0; y<SHEMA_EDGES; y++)
        {
            if (get_shema_item(piece_m, x, y))
            {
                draw_case(context, color, x+xp, y+yp, gravity, edges, line);   
            }
        }
    }
}

void destroy_piece_controleur(struct PieceControleur_t *controleur)
{
    assert(controleur != NULL);
    destroy_piece_vue(controleur->vue);
    free(controleur);
}