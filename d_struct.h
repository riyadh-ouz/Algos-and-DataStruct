#pragma once
#ifndef D_STRUCT_H
#define D_STRUCT_H

#include <string>
#include <stack>
#include <queue>

// Listes
typedef struct Element Element;
struct Element {
	int info;
	Element* suivant;
};

Element* creer_liste(int n = 1);
void affiche_liste(Element* tete);

void liberer_liste(Element** tete);
void supprimer_element_liste(Element** tete, int position = 0);
void ajouter_element_liste(Element** tete, int x, int position = 0);

Element* cons(int val, Element* liste);
// Fonction de copie pour éviter cas des effets de bord
Element* copie_liste(Element* liste);
Element* concat_liste(Element* a, Element* b);


// Entre Listes et Tableaux
/*
	Accès arbitraire: tableau O(1), liste O(N)
	Ajout:            tableau O(N), liste O(1)
	Taille:           tableau O(1), liste O(N)***
	Concaténation:    tableau O(N+M), liste O(N) ***
		M est la taille du deuxième tableau
	Filtrage:         tableau O(N*N), liste O(N) ***

	*** Pour la taille d'une liste on peut réduire la compléxité à O(1)
		en modifiant la structure (ajout d'un champs taille) mais cela
		a ses incovénients;
	*** Pour la concaténation des listes on copie chaque élément de A vers B,
		on peut pointer le dernier element de A vers la tète de B, mais cela
		engendre un effet de bord sur la liste A qui serait la CONCAT(A, B);
	*** Pour le filtrage cas du tableau on peut réduire la compléxité en O(N) faisant deux
		parcours pour récupérer la taille de tableau de filtrage, sinon on fait
		un ajout à chaque rencontre (les éléments qui renvoient True), en effet:
		si on trouve k element alors on fait k ajouts donc:
		1 + 2 + 3 + ... + (k-1) = k*k/2 => O(N*N);

*/

// La conversion au cas d'un programme découpé en plusieurs phases traitants des opérations différentes:
Element* tableau_vers_liste(int tab[], int n); // O(N)
int* liste_vers_tableau(Element* tete); // O(N)



// Piles LIFO
/* EX concret: le système d'exploitation utilise une pile pour retenir l'ordre dans lequel les
fonctions d'un programme ont été appelées (call stack)*/

typedef struct Pile Pile;
struct Pile {
	Element* premier;
};

Pile* initialise_pile();
void liberer_pile(Pile* pile);
void affiche_pile(Pile* pile);
bool pile_vide(Pile* pile);
int taille_pile(Pile* pile);
/* Ici on passe la structure de controle sans double pointeur(**),
son role est juste d'accéder au premier élément, c'est ce dernier qui
subit les changement et pas la pile en elle mème */
void empiler(Pile* pile, int x);
int depiler(Pile* pile);



// Files FIFO
typedef struct File File;
struct File {
	Element* premier;
	Element* dernier;
};

File* initialise_file();
void liberer_file(File* file);
void affiche_file(File* file);
bool file_vide(File* file);
int taille_file(File* file);
/* Mème principe passage sans double pointeur */
void enfiler(File* file, int x);
int defiler(File* file);



// Les tables de hachage

// définition des structure
typedef struct eleve Eleve;
struct eleve {
	std::string nom;
	int age;
	Eleve* suivant;
};

typedef struct table_de_hachage t_Hach;
struct table_de_hachage {
	int taille;
	Eleve** tab;
};

t_Hach* initialise_hach(int n);
void affiche_t_hach(t_Hach* T);
// A voir les 2 algos de hachage SH1 et MD5
int hachage(std::string const& chaine, int taille);
void ajouter_t_hach(t_Hach* T, Eleve* e);
// Recherche par chainage, note aussi l'addressage ouvert (deuxième méthode pour gérer les collisions)
Eleve* extraire_element(t_Hach* T, std::string const& chaine);
void liberer_t_hach(t_Hach* T);



// Les arbres

typedef struct Arbre Arbre;
struct Arbre {
	int info;
	Arbre* frere;
	Arbre* enfant;
};

int taille_arbre(Arbre* arbre);
int hauteur_arbre(Arbre* arbre);
Element* liste_elements_DFS(Arbre* arbre); // DFS avec récursivité
Element* liste_elements_DFS_bis(Arbre* arbre); // Avec une pile

File* liste_elements_BFS(Arbre* arbre); // BFS Avec une file
void liste_elements_BFS_bis(Arbre* arbre); // BFS avec deux files representant des couches

// Entre DFS et BFS
/*
	Compléxité en temps: DFS O(N), BFS O(N) ***
	Compléxité en mémoire: DFS O(H), BFS O(L) ***

	*** Pour la compléxité en temps les deux parcours visitent les noeuds de
		l'arbre une seule fois, avec quelques opérations avant et après ( ajout,
		l'enleve d'un element ...) reste en temps constant;
	*** H: désigne la hauteur de l'arbre, DFS stocke le parcours dans une
		pile, (en DFS avec pile, ou meme DFS récursive sachant que la récursivité
		stocke les appels des fonctions en une pile "callstack");
		L: désigne la plus grande largeur d'une arbre;
		==> dans le pire des cas la compléxité en mémoire est de O(N);
	*** Le DFS répond aux questions " le nombre total..., la liste des elements,
		le plus long chemin..." et le BFS répond aux "le noeud le plus proches 
		que ..., la plus petite distance qui...";

*/



// Arbres binaires de recherche
typedef struct Noeud Noeud;
struct Noeud {
	int info;
	Noeud* droite;
	Noeud* gauche;
};


void noeud_inserer(Noeud** arbre,int x);
int noeud_taille(Noeud* arbre);
bool noeud_rechercher(Noeud* arbre, int x);
void noeud_afficher(Noeud* arbre);
void noeud_afficher_inverse(Noeud* arbre);
void noeud_liberer(Noeud** arbre);



// Tas
typedef struct {
	int capacite, taille;
	int* T;
} Tas;

Tas* tas_initialiser(int capacite);
void tas_liberer(Tas* tas);
void tas_inserer(Tas* tas, int val);
// Cette fonction est juste pour reorganiser le tas apres insertion
void tas_reorganiser(Tas* tas);
void tas_afficher(Tas* tas);

#endif // !D_STRUCT_H