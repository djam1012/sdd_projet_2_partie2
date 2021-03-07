#include "biblioLC.h"
#include "entreeSortieLC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  if (argc!=3){
    printf("Il faut un seul fichier d'entrée et un seul entier > 0.\n");
    return 1;
  }
  if (atoi(argv[2])==0){
    printf("Il faut charger au moins une entrée.\n");
    return 1;
  }
  Biblio* b1 = charger_n_entrees(argv[1], atoi(argv[2]));
  enregistrer_biblio(b1, "Biblio_rangee.txt");


///////////////////////////////////////////////////////////

  Biblio* bib = creer_biblio();
  inserer_en_tete(bib, 45, "tata", "tutu");
  inserer_en_tete(bib, 2015, "tefx", "rzf");
  inserer_en_tete(bib, 77, "boal", "toto");
  inserer_en_tete(bib, 75, "tefx", "rzf");
  inserer_en_tete(bib, 88, "dsqdqs", "toto");
  inserer_en_tete(bib, 3698, "dsqdqs", "toto");
  inserer_en_tete(bib, 405, "plonf", "toto");
  inserer_en_tete(bib, 1, "1984", "G.Orwell");
  inserer_en_tete(bib, 2, "1984", "G.Orwell");
  inserer_en_tete(bib, 3, "1984", "G.Orwell");
  inserer_en_tete(bib, 4, "1984", "G.Orwell");
  inserer_en_tete(bib, 5, "1984", "G.Orwell");
  printf("recherche d'un livre par numero\n");
  recherche_ouvrage_num(bib, 75);
  printf("recherche d'un livre par titre\n");
  recherche_ouvrage_titre(bib, "dsqdqs");
  printf("recherche d'un ou plusieurs livres par auteur\n");
  Biblio* bib2 = recherche_ouvrage_auteur(bib, "toto");

  /*afficher_biblio(bib);
  printf("suppression de tefx.\n");
  supprimer_ouvrage(bib, 75, "tefx", "rzf");
  afficher_biblio(bib);*/

  printf("bibliothèque b1: \n\n");
  afficher_biblio(b1);
  printf("bibliothèque bib: \n\n");
  afficher_biblio(bib);

  printf("copie de b1: \n\n");
  Biblio* b2 = copier_biblio(b1);
  afficher_biblio(b2);

  printf("fusion de deux bibliothèques\n\n");
  fusion_biblio(b1, bib); //bib a été fusionné donc libéré dans la fonction
  afficher_biblio(b1);

  printf("bibliothèque mise à jour:\n\n");
  afficher_biblio(bib);

  printf("exemplaires multiples dans une bibliothèque\n\n");
  Biblio* bib3=afficher_exemplaires(b1);
  afficher_biblio(bib3);

  liberer_biblio(bib3);
  free(bib3);
  liberer_biblio(b2);
  free(b2);
  liberer_biblio(b1);
  free(b1);  // on libère le pointeur sur bibliothèque
  free(bib);
  liberer_biblio(bib2);
  free(bib2);

  return 0;
}
