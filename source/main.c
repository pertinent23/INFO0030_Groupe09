#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gtk/gtk.h>

#include "app_controleur.h"


int main(int argc, char **argv)
{
    time_t t;

    gtk_init(&argc, &argv);
    srand((unsigned int) time(&t));

    AppControleur *app = create_app_controleur();

    if (app == NULL)
        return EXIT_FAILURE;
    
    launch(app);
    destroy_app_controleur(app);

    return EXIT_SUCCESS;
}