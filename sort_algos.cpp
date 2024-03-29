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

void tri_shell(int T[], int premier, int dernier) {

	int h = (dernier - premier + 1) / 2,
		j, tmp;

	while (h > 0) {

		for (int i = h; i <= dernier; i++) {
			j = i;
			tmp = T[i];
			while (j >= h && T[j - h] > tmp) {
				T[j] = T[j - h];
				j -= h;
			}
			T[j] = tmp;
		}

		h /= 2;
	}
}

void fusion(int T[], int premier, int milieu, int dernier) {

	int* gauche = new int[milieu - premier + 1]; // Le milieu est inclu dans la partie gauche
	// Copie du demi-tableau gauche
	for (int i = premier; i <= milieu; i++) gauche[i - premier] = T[i];

	int i = premier,
		j = 0,
		k = milieu + 1;
	
	for (; j <= (milieu - premier) && k <= dernier; i++)
		if (gauche[j] <= T[k]) T[i] = gauche[j++];
		else T[i] = T[k++];

	while (j <= milieu - premier) T[i++] = gauche[j++];

	while (k <= dernier) T[i++] = T[k++];

	delete[] gauche;
}

void tri_fusion_tableau_pre(int T[], int premier, int dernier) {
	if (premier >= dernier) return;
	int milieu = (premier + dernier) / 2;
	tri_fusion_tableau_pre(T, premier, milieu);
	tri_fusion_tableau_pre(T, milieu + 1, dernier);
	fusion(T, premier, milieu, dernier);
}

void tri_fusion_tableau(int T[], int taille) {
	return tri_fusion_tableau_pre(T, 0, taille - 1);
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

// Avec des Arbres

// tri d'un tableau avec une ABR
void ABR_vers_tableau(Noeud* ABR, int T[], int taille) {
	static int i = 0;
	if (i >= taille || !ABR) return;
	ABR_vers_tableau(ABR->gauche, T, taille);
	T[i] = ABR->info;
	i++;
	ABR_vers_tableau(ABR->droite, T, taille);
}

void tri_ABR(int T[], int dernier, int premier) {
	Noeud* ABR = NULL;

	for (int i = premier; i <= dernier; i++) noeud_inserer(&ABR, T[i]);

	ABR_vers_tableau(ABR, T, dernier - premier + 1);

	noeud_liberer(&ABR);
}


// tri d'un tableau avec un tas

void reorganise_tas(int T[], int n, int i) {
	int max = i,
		gauche = 2 * i + 1,
		droit = 2 * i + 2,
		x;

	if (gauche < n && T[gauche] > T[max]) max = gauche;
	if (droit < n && T[droit] > T[max]) max = droit;

	if (max != i) {
		x = T[max];
		T[max] = T[i];
		T[i] = x;
		reorganise_tas(T, n, max);
	}

}
void initialise_tas(int T[], int n) {
	// Le dernier �l�ment qui n'est pas une feuille (n'a pas d'enfants) est d'indice n / 2 - 1;
	// On commence de ce dernier on organise chaque sous arbre (sous tas) jusqu'� la racine;
	for (int i = n / 2 - 1; i >= 0; i--) reorganise_tas(T, n, i);
}
void tri_tas(int T[], int n) {
	initialise_tas(T, n);
	int x;
	for (int i = n - 1; i >= 0; i--) {
		x = T[i];
		T[i] = T[0];
		T[0] = x;
		// On d�cremente la taille � chaque appel
		reorganise_tas(T, i, 0);
	}
}