#include <stdio.h>
#include <stdlib.h>

int main() {

    /* Affichage du contenu du répertoire courant sur un
       poste équipé d'un système d'exploitation Unix */

    const char * command = "ls -al"; 
    int cr = system(command);
    if ( cr != 0 ) {
        fprintf( stderr, "Impossible de lancer la commande : %s\n", command );
    }

    return 0;
}
