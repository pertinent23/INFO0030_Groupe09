#ifndef __PIECE_VUE__
#define __PIECE_VUE__

#include "piece_modele.h"
#include "tools.h"

typedef struct PieceVue_t PieceVue;

struct PieceVue_t *create_piece_vue(TypePiece type);

PieceModel *get_piece_model(struct PieceVue_t *vue);

Color *get_color(struct PieceVue_t *vue);

void modify_piece_model(struct PieceVue_t *vue, PieceModel *modele);

void destroy_piece_vue(struct PieceVue_t *vue);

#endif // !__PIECE_VUE__