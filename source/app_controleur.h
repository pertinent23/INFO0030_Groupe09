#ifndef __APP_CONTROLEUR__
#define __APP_CONTROLEUR__

#include <gtk/gtk.h>

#define CLOCK 40

typedef struct AppControleur_t AppControleur;

struct AppControleur_t *create_app_controleur(void);

void launch(struct AppControleur_t *app);
void destroy_app_controleur(struct AppControleur_t *app);

#endif // !__APP_CONTROLEUR__