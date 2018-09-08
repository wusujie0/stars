#include "blast.h"
#include "spaceship.h"
#include "asteroid.h"
#include "blasterioids.h"  //font chu shi hua

extern Asteroid *bomb_b;
extern Blast *bb;
extern char text[6];
extern int score;
void creat_blast(Spaceship *s)
{
    if(!bb) {
        bb = malloc(sizeof(Blast));
        bb->sx = s->sx +45*sin(s ->heading);
        bb->sy = s->sy -45*cos(s ->heading);
        bb->color = al_map_rgb(225,220,0);
        bb->heading = s->heading;
        bb->speed = 3 +3 * s->speed;
        bb->gone = 1;
        bb->before_link =NULL;
        bb->after_link =NULL;
    }else {


        Blast *b2;
        b2=bb;
        while(b2->after_link) {
            b2 = b2->after_link;
        }
        Blast *b1 = malloc(sizeof(Blast));;
        b1->sx = s->sx +30*sin(s ->heading);
        b1->sy = s->sy -30*cos(s ->heading);
        b1->color = al_map_rgb(225,220,0);
        b1->heading = s->heading;
        b1->speed = 3 * s->speed;
        b1->gone = 1;
        b1->before_link =b2;
        b1->after_link =NULL;

        b2->after_link =b1;
    }
}

void draw_blast(Blast *blast,Asteroid *a)
{
    if(blast->sx >= SCREEN_W || blast->sy >= SCREEN_H || blast->sx <=0 || blast->sy <=0) {
        delete_blast(blast);
        return;
    }
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform,blast->heading);
    al_translate_transform(&transform,blast->sx,blast->sy);
    al_use_transform(&transform);

    al_draw_line(-6,0,-6,SHELL_LENGTH+3,blast->color,2.0f);
    al_draw_line(6,0,6,SHELL_LENGTH+3,blast->color,2.0f);

    b_hit_comet(blast,a);
    blast_way(blast);

}
void draw_blast2(Blast *blast,Asteroid *a)
{
    if(blast->sx >= SCREEN_W || blast->sy >= SCREEN_H || blast->sx <=0 || blast->sy <=0) {
        delete_blast(blast);
        return;
    }
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform,blast->heading);
    al_translate_transform(&transform,blast->sx,blast->sy);
    al_use_transform(&transform);

    al_draw_line(-5,0,-5,SHELL_LENGTH+3,blast->color,2.0f);
    al_draw_line(5,0,5,SHELL_LENGTH+3,blast->color,2.0f);
    al_draw_line(-11,5,-11,SHELL_LENGTH+6,al_map_rgb(106,90,205),4.0f);

    al_draw_line(11,5,11,SHELL_LENGTH+6,al_map_rgb(106,90,205),4.0f);

    b_hit_comet(blast,a);
    blast_way(blast);

}
void b_hit_comet(Blast *blast,Asteroid *a)
{
    double sx, sy;
    double dis;//distance between blast and comet

    while(a) {
        sx = fabs(a->sx - blast->sx);
        sy = fabs(a->sy - blast->sy);
        if(sx<DISTANCE || sy<DISTANCE) {
            dis = sqrt(sx*sx + sy*sy);
            if(dis < DISTANCE){
                bomb_b =a;
                (bomb_b ->_die)--;
                return;
            }else{
                a = a->after_link;
            }
        }else{
            a = a->after_link;
        }
    }

}

void delete_blast(Blast *blast)  //bei shan zi dan
{
    Blast *b1=bb;
    Blast *b2;
    while(b1) {
        if(b1==blast) {
            b2=b1->before_link;
            if(b2) {
                b2->after_link = blast->after_link;
                Blast *b3;
                b3 = blast->after_link;
                if(b3) b3->before_link = b2;
                free(blast);
                return;

            }else{                             //b2 kong
                b2 = blast->after_link;
                if(b2) b2->before_link =NULL;
                bb = b2;                    // bb bei shan ,gei bb fu zhi
                free(blast);
                return;
            }

        }else{
            b1 = b1->after_link;
        }
    }
}


void blast_way(Blast *b)
{
    if(b->heading < 0){
        b->heading = fabs(b->heading);
        b->sx -= (b->speed + SHELL_LENGTH) * sin(b->heading);
        b->sy -= (b->speed + SHELL_LENGTH) * cos(b->heading);
        b->heading = -(b->heading);
    }else if(b->heading > 0){
        b->sx += (b->speed + SHELL_LENGTH) * sin(b->heading);
        b->sy -= (b->speed + SHELL_LENGTH) * cos(b->heading);
    }else{
        b->sy -= b->speed + SHELL_LENGTH;
    }
}

void destroy_blast(void)
{
    Blast *b1;
    while(bb) {
        b1 =bb;
        bb = bb->after_link;
        free(b1);
    }
}



