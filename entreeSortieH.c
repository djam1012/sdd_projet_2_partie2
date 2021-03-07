#include "biblioH.h"
#include "entreeSortieH.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_M 20

BiblioH* charger_n_entrees(char* nomfic, int n){
  BiblioH* resultat=creer_biblio(20);
  char ligne[256];
  int i=0;
  char num[30];
  char titre[30];
  char auteur[30];
  FILE* fic ;
  fic=fopen(nomfic,"r");

  if (!fic){
    printf("Problème lors de l'ouverture du fichier\n");
    return NULL;
  }
  printf("fichier ouvert avec succès\n");

  while (i<n){
    for (int c=0; c<30; c++){
      num[c]='\0';
      titre[c]='\0';
      auteur[c]='\0'; // on les réinitialise
    }
     int j=0;
     char* temp=fgets(ligne , 256, fic);

    while (ligne[j]!=' '){
       strncat(num, &ligne[j], 1);
       j++;
    }
    printf("numero: %s\n", num);

    j++;
    while (ligne[j]!=' '){
      strncat(titre, &ligne[j], 1);
      j++;
    }
    printf("titre: %s\n", titre);

    j++;
    while (ligne[j]!=' '){
      strncat(auteur, &ligne[j], 1);
      j++;
    }
    printf("auteur: %s\n", auteur);

    i++;
    inserer(resultat, atoi(num),titre,auteur);
  }
  fclose(fic);
  return resultat;
}

void enregistrer_biblio(BiblioH *b, char* nomfic){
  FILE* fic ;
  fic=fopen(nomfic,"w");
  if (!fic){
    printf("Problème lors de l'ouverture du fichier\n");
    return;
  }
  if (!b){
    printf("la bibliothèque est vide, on ne peut pas la copier\n");
    return;
  }

  LivreH* cour;
  for (int i=0; i<b->m; i++){
    cour=(b->T)[i];
    while(cour){
      fprintf(fic,"%d %s %s\n",cour->num,cour->titre,cour->auteur);
      if(!cour->suivant){
        fclose(fic);
        return;
      }
      cour=cour->suivant;
    }
  }
  fclose(fic);
}
