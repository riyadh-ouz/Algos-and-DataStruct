#include "sort_algos.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    /*
    int T[100];

    srand(89);
    for (int i = 0; i < 100; i++) T[i] = rand() % 100;

    tri_insertion(T, 0, 99);
    cout << "\nInsertion trie\n";

    srand(89);
    for (int i = 0; i < 100; i++) T[i] = rand() % 100;

    tri_tas(T, 100);
    cout << "\ntas trie\n";
    for (int i = 0; i < 100; i++) cout << "\n" << T[i];
    */
    
    
    /*
    t_Hach* a = initialise_hach(10);
    for (int i = 0; i < 10; i++) {
        Eleve* e = new Eleve;
        e->age = 17 + rand() % 5;
        cin >> e->nom;
        e->suivant = NULL;
        ajouter_t_hach(a, e);
    }
    cout << extraire_element(a, "Riyadh")->age << endl;
    affiche_t_hach(a);
    */
    
    /*
    File* f = initialise_file();
    for (int i = 0; i < 10; i++) enfiler(f, rand() % 20);
    affiche_file(f);
    defiler(f);
    defiler(f);
    affiche_file(f);
    */

    /*
    Pile* p = initialise_pile();
    for (int i = 0; i < 10; i++) empiler(p, rand() % 20);
    affiche_pile(p);
    depiler(p);
    depiler(p);
    empiler(p, rand() % 20);
    affiche_pile(p);
    */
    
    /*
    Arbre I = { 'I', NULL, NULL };
    Arbre H = { 'H', &I, NULL };
    Arbre G = { 'G', &H, NULL };
    Arbre F = { 'F', NULL, &G };
    Arbre E = { 'E', NULL, NULL };
    Arbre D = { 'D', &E, NULL };
    Arbre C = { 'C', NULL, &F };
    Arbre B = { 'B', &C, &D };
    Arbre A = { 'A', NULL, &B };
    //cout << taille_arbre(&A) << "\n";
    //cout << hauteur_arbre(&A) << "\n";
    //liste_elements_DFS(&A);
    //liste_elements_BFS_bis(&A);
    //affiche_liste(liste_elements_DFS_bis(&A));
    //affiche_file(liste_elements_BFS(&A));
    */

    return 0;
}
