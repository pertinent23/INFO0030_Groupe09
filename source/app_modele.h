#ifndef __APP_MODELE__
#define __APP_MODELE__

#include "piece_modele.h"

#define WINDOW_WIDTH 550
#define WINDOW_HEIGHT 600

typedef struct AppModele_t AppModele;

struct AppModele_t *create_app(void);

PieceModel *get_current_pieces(struct AppModele_t *app);

void destroy_app(struct AppModele_t *app);

void set_current_pieces(struct AppModele_t *app, PieceModel *data);

unsigned int get_grill_width(struct AppModele_t *app);
unsigned int get_grill_height(struct AppModele_t *app);


#endif // !__APP_MODELE__