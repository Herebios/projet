#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <math.h>
#include <stdlib.h>

#include "../src/perso.h"
#include "../src/mob.h"


void test_distance_mob1(void) {
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
void test_distance_mob2(void) {
    perso_t p;
    mob_t m;

    p.pos_map.x = 0;
    p.pos_map.y = 0;
    m.pos_map.x = 0;
    m.pos_map.y = 0;

    int dist = distance_mob(&p, &m);

    CU_ASSERT_EQUAL(dist, 0);
}
void test_distance_mob3(void) {
    perso_t p;
    mob_t m;

    p.pos_map.x = 0;
    p.pos_map.y = 0;
    m.pos_map.x = 0;
    m.pos_map.y = 2;

    int dist = distance_mob(&p, &m);

    CU_ASSERT_EQUAL(dist, 2);
}
void test_distance_mob4(void) {
    perso_t p;
    mob_t m;

    p.pos_map.x = 0;
    p.pos_map.y = 0;
    m.pos_map.x = 4;
    m.pos_map.y = 0;
    int dist = distance_mob(&p, &m);

    CU_ASSERT_EQUAL(dist, 4);
}
void test_distance_mob5(void) {
    perso_t p;
    mob_t m;

    p.pos_map.x = 0;
    p.pos_map.y = 0;
    m.pos_map.x = 0;
    m.pos_map.y = 10;

    int dist = distance_mob(&p, &m);

    CU_ASSERT_EQUAL(dist, 10);
}
void test_distance_mob6(void) {
    perso_t p;
    mob_t m;

    p.pos_map.x = -5;
    p.pos_map.y = -5;
    m.pos_map.x = 0;
    m.pos_map.y = 0;

    int dist = distance_mob(&p, &m); // √(25 + 25) = √50 ≈ 7.07 → int => 7
    CU_ASSERT_EQUAL(dist, 7);
}

void test_distance_mob7(void) {
    perso_t p = {.pos_map = {0, 0}};
    mob_t m = {.pos_map = {-3, -4}};
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 5);
}

void test_distance_mob8(void) {
    perso_t p = {.pos_map = {100, 100}};
    mob_t m = {.pos_map = {100, 110}};
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 10);
}

void test_distance_mob9(void) {
    perso_t p = {.pos_map = {7, 3}};
    mob_t m = {.pos_map = {2, 9}};
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 7);
}

void test_distance_mob10(void) {
    perso_t p = {.pos_map = {0, 0}};
    mob_t m = {.pos_map = {6, 8}};
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 10);
}

void test_distance_mob11(void) {
    perso_t p = {.pos_map = {-7, -4}};
    mob_t m = {.pos_map = {-1, -1}};
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 6);
}

void test_distance_mob12(void) {
    perso_t p = {.pos_map = {3, 3}};
    mob_t m = {.pos_map = {3, 3}};
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 0);
}

void test_distance_mob13(void) {
    perso_t p = {.pos_map = {-10, 0}};
    mob_t m = {.pos_map = {10, 0}};
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 20);
}

void test_distance_mob14(void) {
    perso_t p = {.pos_map = {1, 1}};
    mob_t m = {.pos_map = {2, 2}};
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 1);
}

void test_distance_mob15(void) {
    perso_t p = {.pos_map = {-2, -2}};
    mob_t m = {.pos_map = {2, 1}};
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 5);
}
void test_distance_mob16(void) {
    perso_t p = {.pos_map = {2, 3}};
    mob_t m = {.pos_map = {6, 6}};
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 5);
}

void test_distance_mob17(void) {
    perso_t p = {.pos_map = {-5, -5}};
    mob_t m = {.pos_map = {-1, -9}};
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 5);
}

void test_distance_mob18(void) {
    perso_t p = {.pos_map = {0, 0}};
    mob_t m = {.pos_map = {-6, -8}};
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 10);
}

void test_distance_mob19(void) {
    perso_t p = {.pos_map = {3, 4}};
    mob_t m = {.pos_map = {6, 8}};
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 5);
}

void test_distance_mob20(void) {
    perso_t p = {.pos_map = {-10, -10}};
    mob_t m = {.pos_map = {-13, -14}};
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 5);
}

void test_distance_mob21(void) {
    perso_t p = {.pos_map = {0, 0}};
    mob_t m = {.pos_map = {1, 1}};
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 1);
}

void test_distance_mob22(void) {
    perso_t p = {.pos_map = {50, 50}};
    mob_t m = {.pos_map = {55, 55}};
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 7);
}

void test_distance_mob23(void) {
    perso_t p = {.pos_map = {-3, 7}};
    mob_t m = {.pos_map = {1, 3}};
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 5);
}

void test_distance_mob24(void) {
    perso_t p = {.pos_map = {2, -2}};
    mob_t m = {.pos_map = {-2, -6}};
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 5);
}

void test_distance_mob25(void) {
    perso_t p = {.pos_map = {0, 0}};
    mob_t m = {.pos_map = {8, 6}};
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 10);
}
void test_distance_mob26(void) {
    perso_t p = { .pos_map = {4, 4} };
    mob_t m = { .pos_map = {4, -4} }; // diff = (0,8), distance = 8
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 8);
}

void test_distance_mob27(void) {
    perso_t p = { .pos_map = {0, 0} };
    mob_t m = { .pos_map = {1, 2} }; // distance = √5 ≈ 2.23
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 2);
}

void test_distance_mob28(void) {
    perso_t p = { .pos_map = {9, 6} };
    mob_t m = { .pos_map = {6, 2} }; // diff = (3,4), distance = 5
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 5);
}

void test_distance_mob29(void) {
    perso_t p = { .pos_map = {2, 2} };
    mob_t m = { .pos_map = {-2, -2} }; // diff = (4,4), distance = √32 ≈ 5.65
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 5);
}

void test_distance_mob30(void) {
    perso_t p = { .pos_map = {1, 1} };
    mob_t m = { .pos_map = {2, 3} }; // diff = (1,2), distance = √5 ≈ 2.23
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 2);
}

void test_distance_mob31(void) {
    perso_t p = { .pos_map = {5, 5} };
    mob_t m = { .pos_map = {10, 10} }; // diff = (5,5), distance = √50 ≈ 7.07
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 7);
}

void test_distance_mob32(void) {
    perso_t p = { .pos_map = {7, 3} };
    mob_t m = { .pos_map = {7, 10} }; // diff = (0,7), distance = 7
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 7);
}

void test_distance_mob33(void) {
    perso_t p = { .pos_map = {0, 0} };
    mob_t m = { .pos_map = {-6, -8} }; // distance = √100 = 10
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 10);
}

void test_distance_mob34(void) {
    perso_t p = { .pos_map = {3, 4} };
    mob_t m = { .pos_map = {0, 0} }; // diff = (3,4), distance = 5
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 5);
}

void test_distance_mob35(void) {
    perso_t p = { .pos_map = {-10, -5} };
    mob_t m = { .pos_map = {-5, -9} }; // diff = (5,4), distance = √41 ≈ 6.4
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 6);
}
void test_distance_mob36(void) {
    perso_t p = { .pos_map = {10, 10} };
    mob_t m = { .pos_map = {13, 14} }; // diff = (3,4), distance = 5
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 5);
}

void test_distance_mob37(void) {
    perso_t p = { .pos_map = {-1, -1} };
    mob_t m = { .pos_map = {-4, -5} }; // diff = (3,4), distance = 5
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 5);
}

void test_distance_mob38(void) {
    perso_t p = { .pos_map = {0, 0} };
    mob_t m = { .pos_map = {7, 24} }; // distance = 25
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 25);
}

void test_distance_mob39(void) {
    perso_t p = { .pos_map = {-7, -24} };
    mob_t m = { .pos_map = {0, 0} }; // distance = 25
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 25);
}

void test_distance_mob40(void) {
    perso_t p = { .pos_map = {-3, -4} };
    mob_t m = { .pos_map = {0, 0} }; // distance = 5
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 5);
}

void test_distance_mob41(void) {
    perso_t p = { .pos_map = {100, 100} };
    mob_t m = { .pos_map = {104, 103} }; // diff = (4,3), distance = 5
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 5);
}

void test_distance_mob42(void) {
    perso_t p = { .pos_map = {6, 9} };
    mob_t m = { .pos_map = {2, 6} }; // diff = (4,3), distance = 5
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 5);
}

void test_distance_mob43(void) {
    perso_t p = { .pos_map = {-8, 5} };
    mob_t m = { .pos_map = {-11, 9} }; // diff = (3,4), distance = 5
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 5);
}

void test_distance_mob44(void) {
    perso_t p = { .pos_map = {0, 0} };
    mob_t m = { .pos_map = {0, 1} }; // distance = 1
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 1);
}

void test_distance_mob45(void) {
    perso_t p = { .pos_map = {0, 0} };
    mob_t m = { .pos_map = {3, 3} }; // distance = √18 ≈ 4.24
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 4);
}
void test_distance_mob46(void) {
    perso_t p = { .pos_map = {5, 5} };
    mob_t m = { .pos_map = {10, 5} }; // diff = (5,0), distance = 5
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 5);
}

void test_distance_mob47(void) {
    perso_t p = { .pos_map = {5, 5} };
    mob_t m = { .pos_map = {5, 10} }; // diff = (0,5), distance = 5
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 5);
}

void test_distance_mob48(void) {
    perso_t p = { .pos_map = {3, 3} };
    mob_t m = { .pos_map = {6, 7} }; // diff = (3,4), distance = 5
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 5);
}

void test_distance_mob49(void) {
    perso_t p = { .pos_map = {-5, -5} };
    mob_t m = { .pos_map = {-10, -10} }; // diff = (5,5), distance ≈ 7.07
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 7);
}

void test_distance_mob50(void) {
    perso_t p = { .pos_map = {0, 0} };
    mob_t m = { .pos_map = {6, 8} }; // diff = (6,8), distance = 10
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 10);
}

void test_distance_mob51(void) {
    perso_t p = { .pos_map = {10, 10} };
    mob_t m = { .pos_map = {0, 0} }; // diff = (10,10), distance ≈ 14.14
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 14);
}

void test_distance_mob52(void) {
    perso_t p = { .pos_map = {-10, 0} };
    mob_t m = { .pos_map = {0, 0} }; // diff = (10,0), distance = 10
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 10);
}

void test_distance_mob53(void) {
    perso_t p = { .pos_map = {0, -10} };
    mob_t m = { .pos_map = {0, 0} }; // diff = (0,10), distance = 10
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 10);
}

void test_distance_mob54(void) {
    perso_t p = { .pos_map = {-1, -1} };
    mob_t m = { .pos_map = {1, 1} }; // diff = (2,2), distance ≈ 2.83
    CU_ASSERT_EQUAL((int) distance_mob(&p, &m), 2);
}

void test_distance_mob55(void) {
    perso_t p = { .pos_map = {1, 2} };
    mob_t m = { .pos_map = {4, 6} }; // diff = (3,4), distance = 5
    CU_ASSERT_EQUAL(distance_mob(&p, &m), 5);
}



void test_joueur_plus_proche_mob1(void) {
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
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso3);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob2(void) {
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
    mob->pos_map.x = 2;
    mob->pos_map.y = -3;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso4);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob3(void) {
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
    mob->pos_map.x = -1;
    mob->pos_map.y = -1;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso2);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob4(void) {
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
    mob->pos_map.x = 1;
    mob->pos_map.y = 1;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso1);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob5(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = 0;
    perso1->pos_map.y = 0;
    perso2->pos_map.x = 5;
    perso2->pos_map.y = 5;
    perso3->pos_map.x = -5;
    perso3->pos_map.y = -5;
    perso4->pos_map.x = 10;
    perso4->pos_map.y = 10;

    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = 0;
    mob->pos_map.y = 0;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso1);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob8(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = 1;
    perso1->pos_map.y = 2;
    perso2->pos_map.x = 3;
    perso2->pos_map.y = 4;
    perso3->pos_map.x = 5;
    perso3->pos_map.y = 6;
    perso4->pos_map.x = 7;
    perso4->pos_map.y = 8;

    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = 0;
    mob->pos_map.y = 0;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso1);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob10(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = -1;
    perso1->pos_map.y = 2;
    perso2->pos_map.x = 4;
    perso2->pos_map.y = -1;
    perso3->pos_map.x = 3;
    perso3->pos_map.y = 6;
    perso4->pos_map.x = -5;
    perso4->pos_map.y = -6;

    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = 0;
    mob->pos_map.y = 0;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso1);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob11(void) {
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

void test_joueur_plus_proche_mob12(void) {
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
    mob->pos_map.x = 2;
    mob->pos_map.y = -3;
    mob->stats[speed] = 1; // Se déplace de 1 en 1 dans le repère

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso4);
    
    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob13(void) {
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
    mob->pos_map.x = -1;
    mob->pos_map.y = -1;
    mob->stats[speed] = 1; // Se déplace de 1 en 1 dans le repère

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso2);
    
    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob14(void) {
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
    mob->pos_map.x = 1;
    mob->pos_map.y = 1;
    mob->stats[speed] = 1; // Se déplace de 1 en 1 dans le repère

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso1);
    
    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}


void test_joueur_plus_proche_mob15(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = -1;
    perso1->pos_map.y = -1;
    perso2->pos_map.x = -3;
    perso2->pos_map.y = 1;
    perso3->pos_map.x = 4;
    perso3->pos_map.y = -2;
    perso4->pos_map.x = 6;
    perso4->pos_map.y = 5;

    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = 1;
    mob->pos_map.y = 1;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso1);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob16(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = -3;
    perso1->pos_map.y = -4;
    perso2->pos_map.x = -1;
    perso2->pos_map.y = -1;
    perso3->pos_map.x = 2;
    perso3->pos_map.y = 3;
    perso4->pos_map.x = 4;
    perso4->pos_map.y = 5;

    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = -2;
    mob->pos_map.y = -3;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso1);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob17(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = 0;
    perso1->pos_map.y = 0;
    perso2->pos_map.x = -6;
    perso2->pos_map.y = -6;
    perso3->pos_map.x = 1;
    perso3->pos_map.y = 1;
    perso4->pos_map.x = 2;
    perso4->pos_map.y = 2;

    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = -5;
    mob->pos_map.y = -5;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso2);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob18(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = 1;
    perso1->pos_map.y = 2;
    perso2->pos_map.x = -2;
    perso2->pos_map.y = -2;
    perso3->pos_map.x = 3;
    perso3->pos_map.y = 3;
    perso4->pos_map.x = -3;
    perso4->pos_map.y = -3;

    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = -1;
    mob->pos_map.y = -1;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso2);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob19(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = 0;
    perso1->pos_map.y = 0;
    perso2->pos_map.x = 5;
    perso2->pos_map.y = -5;
    perso3->pos_map.x = -5;
    perso3->pos_map.y = 5;
    perso4->pos_map.x = 10;
    perso4->pos_map.y = 10;

    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = 0;
    mob->pos_map.y = 0;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso1);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}
void test_joueur_plus_proche_mob21(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = 0;
    perso1->pos_map.y = 0;
    perso2->pos_map.x = 1;
    perso2->pos_map.y = 0;
    perso3->pos_map.x = 0;
    perso3->pos_map.y = 1;
    perso4->pos_map.x = 1;
    perso4->pos_map.y = 1;

    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = 0;
    mob->pos_map.y = 1;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso3);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob22(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = -1;
    perso1->pos_map.y = -1;
    perso2->pos_map.x = 2;
    perso2->pos_map.y = 2;
    perso3->pos_map.x = -3;
    perso3->pos_map.y = -3;
    perso4->pos_map.x = 3;
    perso4->pos_map.y = 3;

    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = 1;
    mob->pos_map.y = 1;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso2);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob23(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = -2;
    perso1->pos_map.y = -3;
    perso2->pos_map.x = 1;
    perso2->pos_map.y = 1;
    perso3->pos_map.x = 2;
    perso3->pos_map.y = -2;
    perso4->pos_map.x = -4;
    perso4->pos_map.y = 4;

    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = -1;
    mob->pos_map.y = -1;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso1);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob24(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = -1;
    perso1->pos_map.y = -1;
    perso2->pos_map.x = 1;
    perso2->pos_map.y = -1;
    perso3->pos_map.x = 0;
    perso3->pos_map.y = 2;
    perso4->pos_map.x = 3;
    perso4->pos_map.y = 0;

    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = 0;
    mob->pos_map.y = 0;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso1);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob25(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = -1;
    perso1->pos_map.y = -1;
    perso2->pos_map.x = 1;
    perso2->pos_map.y = 2;
    perso3->pos_map.x = 2;
    perso3->pos_map.y = 2;
    perso4->pos_map.x = -3;
    perso4->pos_map.y = -3;

    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = 1;
    mob->pos_map.y = 1;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso2);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob26(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = 1;
    perso1->pos_map.y = 0;
    perso2->pos_map.x = 0;
    perso2->pos_map.y = -1;
    perso3->pos_map.x = -2;
    perso3->pos_map.y = 2;
    perso4->pos_map.x = 3;
    perso4->pos_map.y = 3;

    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = 1;
    mob->pos_map.y = -2;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso2);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob27(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = 2;
    perso1->pos_map.y = 1;
    perso2->pos_map.x = -1;
    perso2->pos_map.y = -2;
    perso3->pos_map.x = 3;
    perso3->pos_map.y = 3;
    perso4->pos_map.x = 5;
    perso4->pos_map.y = 5;

    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = 1;
    mob->pos_map.y = 1;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso1);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob28(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = -2;
    perso1->pos_map.y = -1;
    perso2->pos_map.x = 3;
    perso2->pos_map.y = 4;
    perso3->pos_map.x = -1;
    perso3->pos_map.y = 2;
    perso4->pos_map.x = 4;
    perso4->pos_map.y = 5;

    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = -3;
    mob->pos_map.y = -3;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso1);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob29(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = 0;
    perso1->pos_map.y = -1;
    perso2->pos_map.x = -3;
    perso2->pos_map.y = 2;
    perso3->pos_map.x = 4;
    perso3->pos_map.y = 3;
    perso4->pos_map.x = -5;
    perso4->pos_map.y = -4;

    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = 1;
    mob->pos_map.y = 1;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso1);

    free(perso1);
    free(perso2);
    free(perso3);
    free(perso4);
    free(mob);
}

void test_joueur_plus_proche_mob30(void) {
    perso_t * perso1 = malloc(sizeof(perso_t));
    perso_t * perso2 = malloc(sizeof(perso_t));
    perso_t * perso3 = malloc(sizeof(perso_t));
    perso_t * perso4 = malloc(sizeof(perso_t));
    perso1->pos_map.x = 2;
    perso1->pos_map.y = -1;
    perso2->pos_map.x = 1;
    perso2->pos_map.y = 1;
    perso3->pos_map.x = -1;
    perso3->pos_map.y = -3;
    perso4->pos_map.x = 3;
    perso4->pos_map.y = 0;

    perso_t * listePersos[4] = {perso1, perso2, perso3, perso4};

    mob_t * mob = malloc(sizeof(mob_t));
    mob->pos_map.x = 0;
    mob->pos_map.y = 2;
    mob->stats[speed] = 1;

    perso_t * pPlusProche = joueur_plus_proche_mob(listePersos, mob, 4);

    CU_ASSERT_EQUAL(pPlusProche, perso2);

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
    CU_add_test(suite, "test distance entre un perso et monstre1", test_distance_mob1);
    CU_add_test(suite, "test distance entre un perso et monstre2", test_distance_mob2);
    CU_add_test(suite, "test distance entre un perso et monstre3", test_distance_mob3);
    CU_add_test(suite, "test distance entre un perso et monstre4", test_distance_mob4);
    CU_add_test(suite, "test distance entre un perso et monstre5", test_distance_mob5);
    CU_add_test(suite, "test distance entre un perso et monstre6", test_distance_mob6);
    CU_add_test(suite, "test distance entre un perso et monstre7", test_distance_mob7);
    CU_add_test(suite, "test distance entre un perso et monstre8", test_distance_mob8);
    CU_add_test(suite, "test distance entre un perso et monstre9", test_distance_mob9);
    CU_add_test(suite, "test distance entre un perso et monstre10", test_distance_mob10);
    CU_add_test(suite, "test distance entre un perso et monstre11", test_distance_mob11);
    CU_add_test(suite, "test distance entre un perso et monstre12", test_distance_mob12);
    CU_add_test(suite, "test distance entre un perso et monstre13", test_distance_mob13);
    CU_add_test(suite, "test distance entre un perso et monstre14", test_distance_mob14);
    CU_add_test(suite, "test distance entre un perso et monstre15", test_distance_mob15);
    CU_add_test(suite, "test distance entre un perso et monstre16", test_distance_mob16);
    CU_add_test(suite, "test distance entre un perso et monstre17", test_distance_mob17);
    CU_add_test(suite, "test distance entre un perso et monstre18", test_distance_mob18);
    CU_add_test(suite, "test distance entre un perso et monstre19", test_distance_mob19);
    CU_add_test(suite, "test distance entre un perso et monstre20", test_distance_mob20);
    CU_add_test(suite, "test distance entre un perso et monstre21", test_distance_mob21);
    CU_add_test(suite, "test distance entre un perso et monstre22", test_distance_mob22);
    CU_add_test(suite, "test distance entre un perso et monstre23", test_distance_mob23);
    CU_add_test(suite, "test distance entre un perso et monstre24", test_distance_mob24);
    CU_add_test(suite, "test distance entre un perso et monstre25", test_distance_mob25);
    CU_add_test(suite, "test distance entre un perso et monstre26", test_distance_mob26);
    CU_add_test(suite, "test distance entre un perso et monstre27", test_distance_mob27);
    CU_add_test(suite, "test distance entre un perso et monstre28", test_distance_mob28);
    CU_add_test(suite, "test distance entre un perso et monstre29", test_distance_mob29);
    CU_add_test(suite, "test distance entre un perso et monstre30", test_distance_mob30);
    CU_add_test(suite, "test distance entre un perso et monstre31", test_distance_mob31);
    CU_add_test(suite, "test distance entre un perso et monstre32", test_distance_mob32);
    CU_add_test(suite, "test distance entre un perso et monstre33", test_distance_mob33);
    CU_add_test(suite, "test distance entre un perso et monstre34", test_distance_mob34);
    CU_add_test(suite, "test distance entre un perso et monstre35", test_distance_mob35);
    CU_add_test(suite, "test distance entre un perso et monstre36", test_distance_mob36);
    CU_add_test(suite, "test distance entre un perso et monstre37", test_distance_mob37);
    CU_add_test(suite, "test distance entre un perso et monstre38", test_distance_mob38);
    CU_add_test(suite, "test distance entre un perso et monstre39", test_distance_mob39);
    CU_add_test(suite, "test distance entre un perso et monstre40", test_distance_mob40);
    CU_add_test(suite, "test distance entre un perso et monstre41", test_distance_mob41);
    CU_add_test(suite, "test distance entre un perso et monstre42", test_distance_mob42);
    CU_add_test(suite, "test distance entre un perso et monstre43", test_distance_mob43);
    CU_add_test(suite, "test distance entre un perso et monstre44", test_distance_mob44);
    CU_add_test(suite, "test distance entre un perso et monstre45", test_distance_mob45);
    CU_add_test(suite, "test distance entre un perso et monstre46", test_distance_mob46);
    CU_add_test(suite, "test distance entre un perso et monstre47", test_distance_mob47);
    CU_add_test(suite, "test distance entre un perso et monstre48", test_distance_mob48);
    CU_add_test(suite, "test distance entre un perso et monstre49", test_distance_mob49);
    CU_add_test(suite, "test distance entre un perso et monstre50", test_distance_mob50);
    CU_add_test(suite, "test distance entre un perso et monstre51", test_distance_mob51);
    CU_add_test(suite, "test distance entre un perso et monstre52", test_distance_mob52);
    CU_add_test(suite, "test distance entre un perso et monstre53", test_distance_mob53);
    CU_add_test(suite, "test distance entre un perso et monstre54", test_distance_mob54);
    CU_add_test(suite, "test distance entre un perso et monstre55", test_distance_mob55);


    


    CU_add_test(suite, "test joueur le plus proche du monstre1", test_joueur_plus_proche_mob1);
    CU_add_test(suite, "test joueur le plus proche du monstre2", test_joueur_plus_proche_mob2);
    CU_add_test(suite, "test joueur le plus proche du monstre3", test_joueur_plus_proche_mob3);
    CU_add_test(suite, "test joueur le plus proche du monstre4", test_joueur_plus_proche_mob4);
    CU_add_test(suite, "test joueur le plus proche du monstre5", test_joueur_plus_proche_mob5);
    CU_add_test(suite, "test joueur le plus proche du monstre7", test_joueur_plus_proche_mob8);
    CU_add_test(suite, "test joueur le plus proche du monstre8", test_joueur_plus_proche_mob10);
    CU_add_test(suite, "test joueur le plus proche du monstre9", test_joueur_plus_proche_mob11);
    CU_add_test(suite, "test joueur le plus proche du monstre10", test_joueur_plus_proche_mob12);
    CU_add_test(suite, "test joueur le plus proche du monstre11", test_joueur_plus_proche_mob13);
    CU_add_test(suite, "test joueur le plus proche du monstre12", test_joueur_plus_proche_mob14);
    CU_add_test(suite, "test joueur le plus proche du monstre13", test_joueur_plus_proche_mob15);
    CU_add_test(suite, "test joueur le plus proche du monstre14", test_joueur_plus_proche_mob16);
    CU_add_test(suite, "test joueur le plus proche du monstre15", test_joueur_plus_proche_mob17);
    CU_add_test(suite, "test joueur le plus proche du monstre16", test_joueur_plus_proche_mob18);
    CU_add_test(suite, "test joueur le plus proche du monstre17", test_joueur_plus_proche_mob19);
    CU_add_test(suite, "test joueur le plus proche du monstre18", test_joueur_plus_proche_mob21);
    CU_add_test(suite, "test joueur le plus proche du monstre19", test_joueur_plus_proche_mob22);
    CU_add_test(suite, "test joueur le plus proche du monstre20", test_joueur_plus_proche_mob23);
    CU_add_test(suite, "test joueur le plus proche du monstre21", test_joueur_plus_proche_mob24);
    CU_add_test(suite, "test joueur le plus proche du monstre22", test_joueur_plus_proche_mob25);
    CU_add_test(suite, "test joueur le plus proche du monstre23", test_joueur_plus_proche_mob26);
    CU_add_test(suite, "test joueur le plus proche du monstre24", test_joueur_plus_proche_mob27);
    CU_add_test(suite, "test joueur le plus proche du monstre25", test_joueur_plus_proche_mob28);
    CU_add_test(suite, "test joueur le plus proche du monstre26", test_joueur_plus_proche_mob29);
    CU_add_test(suite, "test joueur le plus proche du monstre27", test_joueur_plus_proche_mob30);
    

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
