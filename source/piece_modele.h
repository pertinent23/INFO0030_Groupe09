#ifndef __PIECE_MODELE__
#define __PIECE_MODELE__

#include <gtk/gtk.h>

#define SHEMA_EDGES 4
#define GRAVITY_RATE 0.1
#define ROTATION_LEVEL 90

typedef struct PieceModel_t PieceModel;

typedef enum TypePiece_e{
    BATON, BLOC, TE, L_NORMAL, L_INVERSE, BIAIS, BIAIS_INVERSE
} TypePiece;


struct PieceModel_t *create_piece(TypePiece type);
void destroy_piece(struct PieceModel_t *piece);

unsigned int get_position_x(struct PieceModel_t *piece);
unsigned int get_position_y(struct PieceModel_t *piece);
double get_gravity(struct PieceModel_t *piece);

unsigned int get_shema_item(struct PieceModel_t *piece, unsigned int x, unsigned int y);

void set_position_x(struct PieceModel_t *piece, unsigned int x);
void set_position_y(struct PieceModel_t *piece, unsigned int y);
void update_gravity(struct PieceModel_t *piece);

int collision(struct PieceModel_t *piece, unsigned int *wall, unsigned int wall_length);

struct PieceModel_t *rotate_left(struct PieceModel_t *piece);
struct PieceModel_t *rotate_right(struct PieceModel_t *piece);

TypePiece get_piece_type(struct PieceModel_t *piece);




#endif // !__PIECE_MODELE__