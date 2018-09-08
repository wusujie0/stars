#ifndef SPACESHIP_H
#define SPACESHIP_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/system.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/transformations.h>
#include <allegro5/allegro_color.h>
#include <stdbool.h>
#include "asteroid.h"

#define DIS 5
typedef struct {
    float sx;
    float sy;
    float heading;
    float speed;
    int gone;
    ALLEGRO_COLOR color;
}Spaceship;

void init_spaceship(Spaceship *s);
void draw_ship(Spaceship *s);
void s_hit_comet(Spaceship *s, Asteroid **aa);
void destroy_ship(Spaceship *s);
void ship_life(float x, float y);
void rest_life(int gone);
#endif // SPACESHIP_H
