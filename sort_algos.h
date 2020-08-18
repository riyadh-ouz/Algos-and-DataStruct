#pragma once
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