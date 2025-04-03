#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include <stdio.h>
#include <stdlib.h>

#include "../src/liste.c"

void test_creer_liste(){

	liste * liste_test = creer_liste();
	CU_ASSERT_NOT_EQUAL(liste_test, NULL);
	puts("\nLa liste est créée.");

	detruire_liste(&liste_test);
	CU_ASSERT_EQUAL(liste_test, NULL);
	puts("La liste est détruite.\n");
}

void test_ajout_liste(){
	liste * liste_test = creer_liste();

	puts("\nOn crée un tableau d'entiers dynamiquement.");
	int nb_int = 10;
	int *tab_int = malloc(nb_int * sizeof(int));
	for (int i=0; i<nb_int; i++)
		tab_int[i]=i;

	puts("On l'ajoute dans la liste.");
	ajout_debut_liste(liste_test, tab_int, nb_int * sizeof(int));

	puts("On teste le nombre d'éléments de la liste (1 attendu).");
	CU_ASSERT_EQUAL(taille_liste(liste_test), 1);

	puts("On désalloue l'élement, il n'existe plus que dans la liste.");
	free(tab_int);

	puts("Récupération de l'élément.");
	tete_liste(liste_test);
	int * ptr_tab_int = get_liste(liste_test);

	puts("On vérifie les valeurs.\n");
	for(int i=0; i<nb_int; i++)
		CU_ASSERT_EQUAL(ptr_tab_int[i], i);

	detruire_liste(&liste_test);
}

int int_comparer(int * i1, int * i2){
	return *i1 - *i2;
}

void test_parcours_liste(){
	liste * liste_test = creer_liste();

	puts("On ajoute des entiers dans la liste.");
	int tab_int[10] = {0,1,2,3,4,5,6,7,8,9};
	for (int i=0; i<10; i++)
		ajout_droit_liste(liste_test, tab_int + i, sizeof(int));

	puts("On cherche un entier en particulier.");
	int entier_cherche = 5;
	int * ptr = trouver_liste(liste_test, &entier_cherche, (void*)int_comparer);
	CU_ASSERT_EQUAL(*ptr, entier_cherche);

	detruire_liste(&liste_test);
}

int main() {

	if (CU_initialize_registry() != CUE_SUCCESS)
    	return CU_get_error();

	CU_pSuite suite = CU_add_suite("Tests sur une liste : ", NULL, NULL);
	CU_add_test(suite, "\ntest création et destruction de liste\n", test_creer_liste);
	CU_add_test(suite, "\ntest ajout puis récupération d'un élément\n", test_ajout_liste);
	CU_add_test(suite, "\ntest parcours d'une liste de plusieurs éléments\n", test_parcours_liste);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}
