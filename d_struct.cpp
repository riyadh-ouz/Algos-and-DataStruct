//#include <stdio.h>
#include <iostream>
//#include <stdlib.h>
#include "d_struct.h"

using namespace std;

// Listes

Element* creer_liste(int n) {
	Element* tete = NULL,
		* p = NULL;
	//p = (Element*)malloc(sizeof(Element));
	//p = malloc(sizeof(*Element));
	p = new Element;
	cout << "\nEntrez les valeurs de la liste\n";
	//scanf("%d", &p->info);
	cin >> p->info;

	p->suivant = NULL;
	// On affecte p à tete car la mémoire est déja allouée par p
	tete = p;

	// On compte de 0
	for (int i = 1; i < n; i++) {
		//p->suivant = (Element*)malloc(sizeof(Element));
		p->suivant = new Element;
		p = p->suivant;
		//scanf("%d", &p->info);
		cin >> p->info;
	}
	p->suivant = NULL;

	return (tete);
}

void affiche_liste(Element* tete) {
	//printf("\n-------------Liste-------------\n");
	cout << "\n-------------Liste-------------\n";
	// Sans faire l'allocation, elle est déja allouée par tete
	Element* p;
	p = tete;
	if (p == NULL) {
		cout << "Liste vide\n";
		return;
	}
	while (p != NULL) {
		//printf("%d\n", p->info);
		cout << p->info << endl;
		p = p->suivant;
	}
}

void liberer_liste(Element** tete) {
	Element* p;
	while (*tete != NULL) {
		p = *tete;
		*tete = (*tete)->suivant;
		//free(p);
		delete p;
	}
}

void supprimer_element_liste(Element** tete, int position) {
	if (position < 0) //printf("Erreur de position");
		cout << "Erreur de position";
	else if (position == 0) {
		Element* p;
		p = *tete;
		*tete = (*tete)->suivant;
		free(p);
	}
	else {
		// On compte de 0
		int i = 1;
		Element* prcd = (*tete),
			* p = (*tete)->suivant;
		while (p != NULL && i < position) {
			prcd = p;
			p = p->suivant;
			i++;
		}
		if (p != NULL) {
			prcd->suivant = p->suivant;
			free(p);
		}
		else //printf("Erreur de position");
			cout << "Erreur de position";
	}
}

void ajouter_element_liste(Element** tete, int x, int position) {
	if (position < 0) //printf("Erreur de position");
		cout << "Erreur de position";
	else if (position == 0) {
		Element* p = new Element;
		//p = (Element*)malloc(sizeof(Element));
		p->info = x;
		p->suivant = *tete;
		*tete = p;
	}
	else {
		// On compte de 0
		int i = 1;
		Element* prcd = *tete;
		while (prcd != NULL && i < position - 1) {
			prcd = prcd->suivant;
			i++;
		}
		if (prcd == NULL) //printf("Erreur de position");
			cout << "Erreur de position";
		else
		{
			Element* p = new Element;
			//p = (Element*)malloc(sizeof(Element));
			p->info = x;
			p->suivant = prcd->suivant;
			prcd->suivant = p;
		}
	}
}

Element* cons(int val, Element* liste) {
	Element* nouveau = new Element;
	if (nouveau == NULL) exit(EXIT_FAILURE);
	nouveau->info = val;
	nouveau->suivant = liste;
	return nouveau;
}

Element* copie_liste(Element* liste) {
	if (NULL == liste) return NULL;
	return cons(liste->info, copie_liste(liste->suivant));
}

Element* concat_liste(Element* a, Element* b) {

	// Cette version copie d'abord la liste a
	if (a == NULL) return b;
	return cons(a->info, concat_liste(a->suivant, b));

	// Cette version a un effet de bord sur la liste a
	/*
	Element* p = a;
	while (p->suivant != NULL) {
		p = p->suivant;
	}
	p->suivant = b;
	return a;
	*/
}

Element* tableau_vers_liste(int tab[], int n) {
	Element* tete = NULL,
		* p = NULL;
	p = new Element;
	p->info = tab[0];
	p->suivant = NULL;

	tete = p;

	for (int i = 1; i < n; i++) {
		p->suivant = new Element;
		p = p->suivant;
		p->info = tab[i];
	}
	p->suivant = NULL;

	return tete;
}

int* liste_vers_tableau(Element* tete) {
	Element* p = tete;
	int n = 0;

	while (p != NULL) {
		n++;
		p = p->suivant;
	}

	int* tab = new int[n], i = 0;
	p = tete;
	while (p != NULL && i < n) {
		tab[i] = p->info;
		i++;
		p = p->suivant;
	}
	// La taille est en: O(N) + Les copies en: O(N) => Une compléxité linéaire O(N)
	return tab;
}



// Piles

Pile* initialise_pile() {
	Pile* pile = new Pile;
	if (pile == NULL) exit(EXIT_FAILURE);
	pile->premier = NULL;
	return pile;
}

void liberer_pile(Pile* pile) {
	liberer_liste(&(pile->premier));
}

void affiche_pile(Pile* pile) {

	if (pile == NULL) exit(EXIT_FAILURE);

	cout << "\n-------------Pile-------------\n";
	Element* p = pile->premier;
	if (p == NULL) {
		cout << "Pile vide\n";
		return;
	}
	while (p != NULL) {
		cout << p->info << endl;
		p = p->suivant;
	}
}

bool pile_vide(Pile* pile) {
	if (pile == NULL) exit(EXIT_FAILURE);
	return pile->premier == NULL;
}

int taille_pile(Pile* pile) {
	if (pile == NULL) exit(EXIT_FAILURE);
	Element* p = pile->premier;
	int i = 0;
	while (p != NULL) {
		i++;
		p = p->suivant;
	}
	return i;
}

void empiler(Pile* pile, int x) {
	Element* nouveau = new Element;
	if (pile == NULL || nouveau == NULL) exit(EXIT_FAILURE);

	nouveau->info = x;
	nouveau->suivant = pile->premier;
	pile->premier = nouveau;
}

int depiler(Pile* pile) {
	if (pile == NULL) exit(EXIT_FAILURE);

	int x = -1;
	Element* p = pile->premier;

	if (p != NULL) {
		x = p->info;
		pile->premier = p->suivant;
		delete p;
	}
	return x;
}



// Files

File* initialise_file() {
	File* file = new File;
	if (file == NULL) exit(EXIT_FAILURE);
	file->premier = NULL;
	file->dernier = NULL;
	return file;
}

void liberer_file(File* file) {
	liberer_liste(&(file->premier));
}

void affiche_file(File* file) {

	if (file == NULL) exit(EXIT_FAILURE);

	cout << "\n-------------File-------------\n";
	Element* p = file->premier;
	if (p == NULL) {
		cout << "File vide\n";
		return;
	}
	while (p != NULL) {
		cout << p->info << endl;
		p = p->suivant;
	}
}

bool file_vide(File* file) {
	if (file == NULL) exit(EXIT_FAILURE);
	return file->dernier == NULL;
}

int taille_file(File* file) {
	if (file == NULL) exit(EXIT_FAILURE);
	Element* p = file->premier;
	int i = 0;
	while (p != NULL) {
		i++;
		p = p->suivant;
	}
	return i;
}

void enfiler(File* file, int x) {

	Element* nouveau = new Element;
	nouveau->info = x;
	nouveau->suivant = NULL;

	if (file == NULL || nouveau == NULL) exit(EXIT_FAILURE);

	if (file_vide(file)) file->premier = nouveau;

	else file->dernier->suivant = nouveau;

	file->dernier = nouveau;
}

int defiler(File* file) {

	if (file == NULL) exit(EXIT_FAILURE);

	int x = -1;
	Element* p = file->premier;

	if (p != NULL) {
		file->premier = p->suivant;
		x = p->info;
		delete p;
	}
	return x;
}



// Les tables de hachages

t_Hach* initialise_hach(int n) {
	t_Hach* T = new t_Hach;
	T->taille = n;
	// L'allocation pour n pointeur vers la structure
	T->tab = new Eleve * [n];
	for (int i = 0; i < n; i++) {
		T->tab[i] = NULL;
	}
	return T;
}

void affiche_t_hach(t_Hach* T) {
	if (T == NULL) exit(EXIT_FAILURE);

	cout << "\n-------------Table de Hachage-------------\n";
	Eleve* e = NULL;
	for (int i = 0; i < T->taille; i++) {
		e = T->tab[i];
		while (e != NULL) {
			cout << e->nom << ": " << e->age << "\t";
			e = e->suivant;
		}
		cout << endl;
	}
}

int hachage(string const& chaine, int taille) {
	int indice = 0;
	for (int i = 0; i < chaine.length(); i++) {
		indice += chaine[i];
	}
	indice %= taille;
	return indice;
}

void ajouter_t_hach(t_Hach* T, Eleve* nouveau) {

	if (T == NULL) exit(EXIT_FAILURE);

	int indice = hachage(nouveau->nom, T->taille);
	Eleve* e = T->tab[indice];
	if (e == NULL) T->tab[indice] = nouveau;
	else {
		while (e->suivant != NULL) {
			e = e->suivant;
		}
		e->suivant = nouveau;
	}
}

Eleve* extraire_element(t_Hach* T, std::string const& chaine) {
	if (T == NULL) exit(EXIT_FAILURE);
	Eleve* e = T->tab[hachage(chaine, T->taille)];
	while (e->nom != chaine && e != NULL) {
		e = e->suivant;
	}
	if (e == NULL) return NULL;
	return e;
}

void liberer_t_hach(t_Hach* T) {

	for (int i = 0; i < T->taille; i++) {
		Eleve* e;
		while (T->tab[i] != NULL) {
			e = T->tab[i];
			T->tab[i] = T->tab[i]->suivant;
			delete e;
		}
	}

	delete[] T->tab;
}



// Les arbres

int taille_arbre(Arbre* arbre) {

	// if (arbre == NULL) exit(EXIT_FAILURE);

	int compteur = 1;
	for (Arbre* a = arbre->enfant; a != NULL; a = a->frere) {
		compteur += taille_arbre(a);
	}
	return compteur;
}

int hauteur_arbre(Arbre* arbre) {

	// if (arbre == NULL) return 0;

	int max = 0;
	int h;
	for (Arbre* a = arbre->enfant; a != NULL; a = a->frere) {
		h = hauteur_arbre(a);
		if (h > max) max = h;
	}

	return 1 + max;
}

Element* liste_elements_DFS(Arbre* arbre) {

	Element* liste = cons(arbre->info, NULL);
	for (Arbre* a = arbre->enfant; a != NULL; a = a->frere) {
		Element* temp = liste;
		liste = concat_liste(liste, liste_elements_DFS(a));
		// On libère la mémoire laissée par  'liste';
		// Car la fonction  'concat_liste'  fait "une copie" de  'liste';
		// On peut utiliser une autre version de 'concat_liste' qui a un effet de bord au lieu d'une copie;
		liberer_liste(&temp);
	}
	return liste;
}

Element* liste_elements_DFS_bis(Arbre* arbre) {
	Element* liste_elements = NULL;

	stack<Arbre*> pile_elements; // File de couche
	pile_elements.push(arbre);

	while (!pile_elements.empty()) {

		liste_elements = cons(pile_elements.top()->info, liste_elements);

		cout << (char)pile_elements.top()->info;

		Arbre* a = pile_elements.top()->enfant;

		pile_elements.pop();

		for (; a != NULL; a = a->frere) pile_elements.push(a);

	}

	return liste_elements;
}

File* liste_elements_BFS(Arbre* arbre) {

	File* liste_elements = initialise_file();

	queue<Arbre*> file_elements; // File de couche
	file_elements.push(arbre);

	while (!file_elements.empty()) {

		enfiler(liste_elements, file_elements.front()->info);

		Arbre* a = file_elements.front()->enfant;

		file_elements.pop();

		for (; a != NULL; a = a->frere) file_elements.push(a);

	}

	return liste_elements;
}

void liste_elements_BFS_bis(Arbre* arbre) {

	queue<Arbre*> a, b;
	a.push(arbre);
	int d = 1;

	do {

		while (!b.empty()) {
			a.push(b.front());
			b.pop();
		}

		cout << "\nCouche: " << d++ << endl;

		while (!a.empty()) {

			cout << (char)a.front()->info << endl;

			for (Arbre* i = a.front()->enfant; i != NULL; i = i->frere) b.push(i);

			a.pop();
		}

	} while (!b.empty());
}



// Arbres binaires de recherche

void noeud_inserer(Noeud** arbre, int x) {

	Noeud* nouveau = new Noeud;
	if (!nouveau) exit(EXIT_FAILURE);

	else {
		nouveau->info = x;
		nouveau->gauche = NULL;
		nouveau->droite = NULL;
		
		Noeud* tempArbre = *arbre,
			* tempNoeud = NULL;
		if (tempArbre) {
			do {
				tempNoeud = tempArbre;

				if (x <= tempArbre->info) {
					tempArbre = tempArbre->gauche;
					if (!tempArbre) tempNoeud->gauche = nouveau;
				}
				else {
					tempArbre = tempArbre->droite;
					if (!tempArbre) tempNoeud->droite = nouveau;
				}
			} while (tempArbre);
		}
		else *arbre = nouveau;
	}
}

int noeud_taille(Noeud* arbre) {
	if (!arbre) return 0;
	return 1 + noeud_taille(arbre->gauche) + noeud_taille(arbre->droite);
}

bool noeud_rechercher(Noeud* arbre, int x) {
	while (arbre) {
		if (arbre->info == x) return true;
		else if (x <= arbre->info) arbre = arbre->gauche;
		else arbre = arbre->droite;
	}
	return false;
}

void noeud_afficher(Noeud* arbre) {
	if (!arbre) return;
	noeud_afficher(arbre->gauche);
	cout << "\n" << arbre->info;
	noeud_afficher(arbre->droite);
}

void noeud_afficher_inverse(Noeud* arbre) {
	if (!arbre) return;
	noeud_afficher_inverse(arbre->droite);
	cout << "\n" << arbre->info;
	noeud_afficher_inverse(arbre->gauche);
}

void noeud_liberer(Noeud** arbre) {
	if (!(*arbre)) return;
	noeud_liberer(&(*arbre)->gauche);
	noeud_liberer(&(*arbre)->droite);
	delete* arbre;
	*arbre = NULL;
}


// Tas

Tas* tas_initialiser(int capacite) {
	Tas* tas = new Tas;
	if (!tas) return NULL;
	tas->capacite = capacite;
	tas->T = new int[capacite];
	tas->taille = 0;
	return tas;
}

void tas_liberer(Tas* tas) {
	delete[] tas->T;
	tas->taille = 0;
}

void tas_inserer(Tas* tas, int x) {
	if (!tas) exit(EXIT_FAILURE);
	tas->T[tas->taille] = x;
	tas->taille++;
	tas_reorganiser(tas);
}

void tas_reorganiser(Tas* tas) {
	if (tas->taille == 0) return;

	int location = tas->taille,
		i_parent = (location - 1) / 2,
		temp;
	while (location && tas->T[location] > tas->T[i_parent]) {
		temp = tas->T[location];
		tas->T[location] = tas->T[i_parent];
		tas->T[i_parent] = temp;

		location = i_parent;
		i_parent = (location - 1) / 2;
	}

}

void tas_afficher(Tas* tas) {
	for (int i = 0; i <= tas->taille; i++)
		cout << tas->T[i] << endl;
}