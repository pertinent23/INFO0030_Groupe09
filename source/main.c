#include <stdio.h>
#include <gtk/gtk.h>

#include "app_controleur.h"


int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    AppControleur *app = create_app_controleur();

    if (app == NULL)
        return EXIT_FAILURE;
    
    launch(app);
    destroy_app_controleur(app);

    return EXIT_SUCCESS;
}