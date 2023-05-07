#ifndef __PIECE_VUE__
#define __PIECE_VUE__

#include "piece_modele.h"

typedef struct PieceVue_t PieceVue;

struct PieceVue_t *create_piece_vue(TypePiece type);

PieceModel *get_piece_model(struct PieceVue_t *vue);

unsigned int get_color_r(struct PieceVue_t *vue);
unsigned int get_color_g(struct PieceVue_t *vue);
unsigned int get_color_b(struct PieceVue_t *vue);

void destroy_piece_vue(struct PieceVue_t *vue);

#endif // !__PIECE_VUE__