#pragma once
#ifndef SORT_ALGOS_H
#define SORT_ALGOS_H

#include "d_struct.h"

// Pour les listes

void tri_selection_liste(Element** tete);

Element* retire_min(Element* liste, Element* non_mins, int min_actuel);
Element* tri_selection_liste_bis(Element* liste);

Element* fusion(Element* gauche, Element* droite);
void decoupe(Element* liste, Element** gauche, Element** droite);
Element* tri_fusion_liste(Element* liste);

// Pour les tableaux

void tri_selection(int T[], int premier, int dernier);
void tri_insertion(int T[], int premier, int dernier);

void fusion(int T[], int premier, int milieu, int dernier);
void tri_fusion_tableau_pre(int T[], int premier, int dernier);
void tri_fusion_tableau(int T[], int taille);

int partitionner(int T[], int premier, int dernier);
void tri_rapide(int T[], int premier, int dernier);

// Avec des arbres

// tri d'un tableau avec une ABR
void ABR_vers_tableau(Noeud* ABR, int T[], int taille);
void tri_ABR(int T[], int dernier, int premier = 0);

// tri par tas

// tri avec un Tas
/* On note qu'un tas est une ABR compl�te, Il en r�sulte que:
	** Si i est l'indice d'un �l�ment alors 2*i+1 soit l'indice du fils gauche
	et 2*i+2 l'indice du fils droit;
	** Aussi si i est l'indice d'un �l�ment alors (i-1)/2 soit l'indice du parent;
	** Note l'existence de MAX-Heap & MIN-heap, selon la racine est ses enfants;
*/

void reorganise_tas(int T[], int n, int i); // heapify en anglais
void initialise_tas(int T[], int n); // build a Max-heap
void tri_tas(int T[], int n);


#endif // !SORT_ALGOS_H