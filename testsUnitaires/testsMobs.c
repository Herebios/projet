#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <math.h>
#include <stdlib.h>

#include "../src/perso.h"
#include "../src/mob.h"


void test_distance_mob(void) {
    perso_t p;
    mob_t m;

    p.pos_map.x = 0;
    p.pos_map.y = 0;
    m.pos_map.x = 3;
    m.pos_map.y = 4;

    int dist = distance_mob(&p, &m);

    // √(3² + 4²) = √25 = 5
    CU_ASSERT_EQUAL(dist, 5);
}

void test_joueur_plus_proche_mob(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = 1;
    perso1->pos_map.y = 1;
    perso2->pos_map.x = -1;
    perso2->pos_map.y = -1;
    perso3->pos_map.x = -3;
    perso3->pos_map.y = 1;
    perso4->pos_map.x = 2;
    perso4->pos_map.y = -3;
    
    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = -5;
    mob->pos_map.y = 1;
    mob->stats[speed] = 1; // Se déplace de 1 en 1 dans le repère

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso3);
    
    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

int main() {
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    CU_pSuite suite = CU_add_suite("Tests sur les fonctions monstres : ", NULL, NULL);
    CU_add_test(suite, "test distance entre un perso et monstre", test_distance_mob);
    CU_add_test(suite, "test joueur le plus proche du monstre", test_joueur_plus_proche_mob);


    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
