#ifndef BLASTERIOIDS_H
#define BLASTERIOIDS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/system.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/transformations.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <time.h>
#include <stdbool.h>



#define FPS 60
#define SCREEN_W 1024
#define SCREEN_H 640

ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_TIMER* timer;
ALLEGRO_DISPLAY* display;
ALLEGRO_FONT *font1;
ALLEGRO_FONT *font2;
ALLEGRO_FONT *font3;
ALLEGRO_FONT *font4;
ALLEGRO_BITMAP *image1;
ALLEGRO_BITMAP *image2;
ALLEGRO_SAMPLE *sample1;
ALLEGRO_SAMPLE *sample2;

int init(void);
void destroy(void);
void game_ing(void);
int itoa(int num, char *dest);
void print_score(int gone);
void start(char *text);
#endif // BLASTERIOIDS_H
