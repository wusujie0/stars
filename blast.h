#ifndef BLAST_H
#define BLAST_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/system.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/transformations.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <stdbool.h>
#include "asteroid.h"
#include "spaceship.h"


#define SHELL 2
#define SHELL_LENGTH 4//the length of shell
#define DISTANCE 7 //hit symbal of hit
typedef struct Blast{
    float sx;
    float sy;
    float heading;
    float speed;
    int gone;
    ALLEGRO_COLOR color;
    struct Blast *before_link;
    struct Blast *after_link;
} Blast;

void creat_blast(Spaceship *s);
void draw_blast(Blast *blast, Asteroid *a);
void draw_blast2(Blast *blast,Asteroid *a);
void b_hit_comet(Blast *blast,Asteroid *a);
void delete_blast(Blast *blast);
void blast_way(Blast *b);
void destroy_blast(void);
#endif // BLAST_H
