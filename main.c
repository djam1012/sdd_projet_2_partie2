#include "biblioH.h"
#include "entreeSortieH.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_M 20

int main(int argc, char *argv[]){
  if (argc!=3){
    printf("Il faut un seul fichier d'entrée et un seul entier > 0.\n");
    return 1;
  }
  if (atoi(argv[2])==0){
    printf("Il faut charger au moins une entrée.\n");
    return 1;
  }
  BiblioH* b1 = charger_n_entrees(argv[1], atoi(argv[2]));
  enregistrer_biblio(b1, "Biblio_rangee.txt");
  printf("il y a %d livre(s) dans b\n", b1->nE);
  afficher_biblio(b1);
  liberer_biblio(b1);


  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

  LivreH* l=creer_livre(852, "un_titre", "un_auteur");
  BiblioH* b=creer_biblio(TAILLE_M);
  inserer(b, l->num, l->titre, l->auteur); // on crée une copie de ce livre il faut libérer l aussi
  inserer(b, 4561, "un_autre_titre", l->auteur);
  inserer(b, 41235, "title", "author");
  printf("il y a %d livre(s) dans b\n", b->nE);
  liberer_livre(l);
  liberer_biblio(b);

  return 0;
}
