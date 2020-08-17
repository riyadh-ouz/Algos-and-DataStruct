#include "sort_algos.h"

// Listes

void tri_selection_liste(Element** tete) {
	int x;
	Element* p, * t, * pmin;

	for (p = *tete; p->suivant != NULL; p = p->suivant) {
		pmin = p;

		for (t = p->suivant; t != NULL; t = t->suivant)
			if (t->info < pmin->info) pmin = t;

		if (pmin != p) {
			x = pmin->info;
			pmin->info = p->info;
			p->info = x;
		}
	}
}

Element* retire_min(Element* liste, Element* non_mins, int min_actuel) {
	if (NULL == liste) return cons(min_actuel, non_mins);

	int min = (liste->info < min_actuel ? liste->info : min_actuel);
	int non_min = (liste->info > min_actuel ? liste->info : min_actuel);

	return retire_min(liste->suivant, cons(non_min, non_mins), min);
}

Element* tri_selection_liste_bis(Element* liste) {
	if (NULL == liste) return NULL;

	Element* selection, * resultat;
	selection = retire_min(liste->suivant, NULL, liste->info);
	resultat = cons(selection->info, tri_selection_liste_bis(selection->suivant));
	delete selection;
	return resultat;
}

Element* fusion(Element* gauche, Element* droite) {
	if (gauche == NULL) return copie_liste(droite);
	if (droite == NULL) return copie_liste(gauche);
	if (gauche->info <= droite->info) return cons(gauche->info, fusion(gauche->suivant, droite));
	else return cons(droite->info, fusion(gauche, droite->suivant));
}

void decoupe(Element* liste, Element** gauche, Element** droite) {

	do {
		if (liste != NULL) {
			*gauche = cons(liste->info, *gauche);
			liste = liste->suivant;
		}
		if (liste != NULL) {
			*droite = cons(liste->info, *droite);
			liste = liste->suivant;
		}
	} while (NULL != liste);
}

Element* tri_fusion_liste(Element* liste) {
	if (liste == NULL || liste->suivant == NULL) return copie_liste(liste);
	Element* gauche = NULL, * droite = NULL;
	decoupe(liste, &gauche, &droite);
	Element* gauche_triee, * droite_triee;
	gauche_triee = tri_fusion_liste(gauche);
	droite_triee = tri_fusion_liste(droite);
	liberer_liste(&gauche);
	liberer_liste(&droite);
	Element* resultat = fusion(gauche, droite);
	liberer_liste(&gauche_triee);
	liberer_liste(&droite_triee);
	return resultat;
}



// Pour les tableaux

void tri_selection(int T[], int premier, int dernier) {
	int imin, x;
	for (int i = premier; i < dernier; i++) {
		imin = i;
		for (int j = i + 1; j <= dernier; j++)
			if (T[j] < T[imin]) imin = j;
		if (imin != i) {
			x = T[imin];
			T[imin] = T[i];
			T[i] = x;
		}
	}
}

void tri_insertion(int T[], int premier, int dernier) {
	int x, j = premier;
	for (int i = premier + 1; i <= dernier; i++) {
		j = i - 1;
		x = T[i];
		while (j >= 0 && T[j] > x) {
			T[j + 1] = T[j];
			j--;
		}
		if (j != i - 1) T[j + 1] = x;
	}
}

int partitionner(int T[], int premier, int dernier) {
	int j = premier, i, x;
	for (i = premier; i < dernier; i++)
		if (T[i] <= T[dernier]) {
			x = T[i];
			T[i] = T[j];
			T[j] = x;
			j++;
		}
	x = T[dernier];
	T[dernier] = T[j];
	T[j] = x;
	return j;
}

void tri_rapide(int T[], int premier, int dernier) {
	int pivot;
	if (premier < dernier) {
		pivot = partitionner(T, premier, dernier);
		tri_rapide(T, premier, pivot - 1);
		tri_rapide(T, pivot + 1, dernier);
	}
}

