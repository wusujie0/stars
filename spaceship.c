#include "spaceship.h"
#include "blasterioids.h"
#include "asteroid.h"

void init_spaceship(Spaceship *s)
{
    s->sx = SCREEN_W/2.0;
    s->sy = SCREEN_H/2.0;
    s->heading = 0;
    s->speed = 0;
    s->gone = 3;
    s->color = al_map_rgb(0,0,0);
}

void draw_ship(Spaceship *s)
{

    if((s->sx += s->speed *sin(s ->heading))<0) {
        s->sx = 0;
    }else if((s->sx += s->speed *sin(s ->heading))>SCREEN_W) {
        s->sx = SCREEN_W;
    }else {
        s->sx += s->speed *sin(s ->heading);
    }

    if((s->sy += s->speed *cos(s ->heading))<0) {
        s->sy = 0;
    }else if((s->sy -= s->speed *cos(s ->heading))>SCREEN_H) {
        s->sy = SCREEN_H;
    }else {
        s->sy -= s->speed *cos(s ->heading);
    }

    if((s->sy -= s->speed *cos(s ->heading))>=0) s->sy -= s->speed *cos(s ->heading);

    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform, s->heading);//应用旋转变换。参数：(transform,θ-旋转弧)
    al_translate_transform(&transform, s->sx, s->sy);//换一对坐标。参数：(transform,坐标x,坐标y)
    al_use_transform(&transform);
    al_draw_line(-8, 12, 0, -11, s->color,3.5f);
    al_draw_line(0, -11, 8, 12, s->color, 3.5f);
    al_draw_line(-12,17,-7, 10,al_map_rgb(225,225,50) , 1.5f);
    al_draw_line(12,17,7, 10,al_map_rgb(225,225,50) , 1.5f);
    al_draw_line(-5, 7, -1, 4, s->color, 3.0f);
    al_draw_line(5, 7, 1, 4, s->color, 3.0f);


}

void s_hit_comet(Spaceship *s,Asteroid **aa) {
    double sx, sy;
    double dis;//distance between blast and comet
    Asteroid *a =*aa;

    while(a) {
        sx = fabs(a->sx - s->sx);
        sy = fabs(a->sy - s->sy);
        if(sx<DIS || sy<DIS) {
            dis = sqrt(sx*sx + sy*sy);
            if(dis < DIS){
                (s->gone)--;
                s->sx = SCREEN_W/2.0;
                s->sy = SCREEN_H/2.0;
                s->heading = 0;
                s->speed = 0;
                s->color = al_map_rgb(0,0,0);
                delete_asteroid(a,aa);
                return;
            }else{
                a = a->after_link;
            }
        }else{
            a = a->after_link;
        }
    }
}


void destroy_ship(Spaceship *s)
{
    free(s);
}

//draw the life of ship.
void ship_life(float x, float y)
{
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform, 0);//应用旋转变换。参数：(transform,θ-旋转弧)
    al_translate_transform(&transform, x, y);//换一对坐标。参数：(transform,坐标x,坐标y)
    al_use_transform(&transform);

    al_draw_line(-8, 9, 0, -11, al_map_rgb(0,100,100),3.0f);
    al_draw_line(0, -11, 8, 9,  al_map_rgb(200,255,10), 3.0f);
    al_draw_line(-6, 4, -1, 4,  al_map_rgb(200,255,10), 3.0f);
    al_draw_line(6, 4, 1, 4,  al_map_rgb(0,100,100), 3.0f);
}

void rest_life(int gone)
{
    int i;
    int site = 25;
    for(i=gone;i>0;i--){
        ship_life(site,20);
        site += 30;
    }
}
