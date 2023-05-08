#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int write_score(char* nom_joueur, int score, char* filename) {
    assert(filename!=NULL && nom_joueur !=NULL) ;
    FILE* fichier = fopen(filename, "w");
    if (fichier == NULL){
        return 1;
    }else{
        fprintf(fichier, "joueur : %s, score :  %d", nom_joueur, score);    
        return 0;
        fclose(fichier);
}
}
