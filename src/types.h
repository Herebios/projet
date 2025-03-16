#ifndef _TYPES_H_
#define _TYPES_H_
typedef unsigned char octet;

typedef enum {administrateur, tank, guerrier, mage, archer, informaticien, ninja, druide, NB_CLASSES} classe_t;
typedef enum {vie, force, magie, speed, NB_STATS} stat_t;
typedef enum {zone, projectile, instant} comp_type;
typedef enum {atk1, atk2, skill, mouv, NB_COMP} icomp_t;

typedef struct comp_s comp_t;
typedef struct objet_s objet_t;
typedef struct perso_s perso_t;
typedef struct {
    int x;
    int y;
}pos_t;

#endif
