#ifndef __PIECE_CONTROLEUR__
#define __PIECE_CONTROLEUR__

#include "piece_modele.h"
#include "piece_vue.h"

#include <gtk/gtk.h>

typedef struct PieceControleur_t PieceControleur;

struct PieceControleur_t *create_piece_controleur(TypePiece type);

PieceVue *get_piece_vue(struct PieceControleur_t *controleur);

void draw_case(cairo_t *context, Color *color, double x, double y, double gravity, unsigned int edges, unsigned int line);
void draw_piece(struct PieceControleur_t *piece, cairo_t *context, unsigned int edges, unsigned int line);

void destroy_piece_controleur(struct PieceControleur_t *controleur);

#endif // !__PIECE_CONTROLEUR__