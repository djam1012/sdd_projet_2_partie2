#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioLC.h"

Livre* creer_livre(int num,char* titre,char* auteur){
  Livre* nouv=(Livre*)malloc(sizeof(Livre));
  nouv->num=num;
  nouv->titre=strdup(titre); // on duplique les chaines de caractères (malloc implicite)
  nouv->auteur=strdup(auteur);
  nouv->suiv=NULL;
  return nouv;
}

void liberer_livre(Livre* l){
  free(l->titre); // comme strdup sont des mallocs implicite, il faut aussi les libérer
  free(l->auteur);
  free(l); // on libère enfin la mémoire allouée par la structure livre
}

Biblio* creer_biblio(){
  Biblio* nouv=(Biblio*)malloc(sizeof(Biblio)); // on alloue la mémoire pour cette structure
  nouv->L=NULL; // il n'y a pas de livre pour l'instant donc on ne met aucun livre
  return nouv;
}

void liberer_biblio(Biblio* b){ // fonction récursive
  if (!b){
    printf("Impossible de libérer une bibliothèque vide.\n");
    return;
  }
  Livre* cour; // on crée une variable temporaire qui stocke le livre à libérer
  if(b->L!=NULL){
      cour=b->L->suiv; // on passe au livre suivant L
      liberer_livre(b->L); // on libère L
      b->L=cour; // et le premier livre de la liste chainée de livres devient cour
      liberer_biblio(b); // puis on libère le reste récursivement
  }
}

void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur){
  Livre* nouv=creer_livre(num, titre, auteur);
  if (b->L==NULL){
    b->L=nouv;
  }else{
    nouv->suiv=b->L;
    b->L=nouv;
  }
}

void afficher_livre(Livre* l){
  if(!l){
    printf("livre vide\n");
    return;
  }
  printf("Livre numéro: %d\tTitre: %s\t Auteur: %s\n", l->num, l->titre, l->auteur);
}

void afficher_biblio(Biblio* b){
  if (!b){
    printf("La bibliothèque est vide, impossible de l'afficher.\n");
    return;
  }
  Livre* cour=b->L; // on crée une variable temporaire qui stocke le livre à libérer
  while(cour){
    afficher_livre(cour); // on affiche L
    if(b->L->suiv==NULL) return;
    cour=cour->suiv; // on passe au livre suivant L
  }
  printf("\n");
}

Livre* recherche_ouvrage_num(Biblio* b, int num){
  if (!b){
    printf("La bibliothèque est vide.\n");
    return NULL;
  }
  Livre* cour=b->L;
  while(cour){
    if (cour->num==num){
      afficher_livre(cour);
      return cour;
    }
    if(b->L->suiv==NULL) return NULL;
    cour=cour->suiv;
  }
}

Livre* recherche_ouvrage_titre(Biblio* b, char* titre){
  if (!b){
    printf("La bibliothèque est vide.\n");
    return NULL;
  }
  Livre* cour=b->L;
  while(cour){
    if (!strcmp(cour->titre,titre)){
      afficher_livre(cour);
      return cour;
    }
    if(b->L->suiv==NULL) return NULL;
    cour=cour->suiv;
  }
}

Biblio* recherche_ouvrage_auteur(Biblio* b, char* auteur){
  if (!b){
    printf("La bibliothèque est vide.\n");
    return NULL;
  }
  Biblio* resultat=creer_biblio();
  Livre* cour=b->L;
  while(cour){
    if (!strcmp(cour->auteur,auteur)){
      inserer_en_tete(resultat, cour->num, cour->titre, cour->auteur);
    }
    if(b->L->suiv==NULL) return NULL;
    cour=cour->suiv;
  }
  afficher_biblio(resultat);
  return resultat;
}

Biblio* copier_biblio(Biblio* b){ // fonction qui retourne une copie de la bibliothèque passée en paramètre
  Biblio* temp=creer_biblio();
  if (!b){
    printf("La bibliothèque est vide.\n");
    return NULL;
  }
  Livre* cour=b->L;
  while(cour){
    inserer_en_tete(temp, cour->num, cour->titre, cour->auteur);
    if(b->L->suiv==NULL) break;
    cour=cour->suiv;
  }
  Biblio* res=creer_biblio(); // comme la bibliothèque est inversée à cause de l'insertion en tete, on la remplit de nouveau à l'envers
  cour=temp->L;
  while(cour){
    inserer_en_tete(res, cour->num, cour->titre, cour->auteur);
    if(temp->L->suiv==NULL) break;
    cour=cour->suiv;
  }
  liberer_biblio(temp);
  free(temp);
  return res;
}

Biblio* fusion_biblio(Biblio* b1, Biblio* b2){
    if(!b1) return b2;
    Livre* cour=b1->L;
    while(cour->suiv) cour=cour->suiv;
    cour->suiv=b2->L;
    return b1;
}

void supprimer_ouvrage(Biblio* b, int num, char* titre, char* auteur){
  Livre* cour = b->L;
  Livre* prec;
  if (b->L == NULL) {
    return;
  }
  if (cour->num==num&&!strcmp(cour->titre,titre)&&!strcmp(cour->auteur,auteur)){
    b->L = cour->suiv;
    liberer_livre(cour);
    return;
  }
  while (cour != NULL && !(cour->num==num&&!strcmp(cour->titre,titre)&&!strcmp(cour->auteur,auteur))) {
    prec = cour;
    cour = cour->suiv;
  }
  if (cour == NULL){
    return;
  }
  prec->suiv = cour->suiv;
  liberer_livre(cour);
}

Biblio* afficher_exemplaires(Biblio *B){

  int deja_ajoute;
  Biblio *Bs = creer_biblio();
  Livre *l = B->L;

  while (l != NULL) {
    deja_ajoute=0;
    Livre *l1 = B->L;

    while (l1 != NULL) {
      if (strcmp(l->titre, l1->titre) == 0
      && strcmp (l->auteur, l1->auteur) == 0&& l != l1){
        if (deja_ajoute==0){
          inserer_en_tete(Bs, l->num, strdup(l->titre), strdup(l->auteur));
          deja_ajoute=1;
        }
      }
      l1 = l1->suiv;
    }
    l = l->suiv;
  }
  return Bs;
}
