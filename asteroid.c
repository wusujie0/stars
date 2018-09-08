#include "asteroid.h"
#include "blasterioids.h"

extern Asteroid *bomb_b;
extern Asteroid *bomb_s;

void creat_and_init_food(Food *a)
{

   a->type = rand() % 2;
   if(a->type == 1){                 //此食物会竖着下来
   a->sx = rand() % SCREEN_W;
   a->sy = 0;
   a->speed = 1;
   a->twist = rand() % 360;
   a->color = al_map_rgb(rand()%250,rand()%250,rand()%250);
   a->scale = 4 / rand() % 2 + 1;
   }
   else if(a->type == 0){                            //此食物会横着飞
       a->sx = 0;
       a->sy = rand() % SCREEN_H;
       a->speed = 1.5;
       a->twist = rand() % 360;
       a->color = al_map_rgb(rand()%250,rand()%250,rand()%250);
       a->scale = 4 / rand() % 2 + 1;
   }

}

void change_food_position(Food *a)
{
   if(a->type == 1){
       a->sx = a->sx;
       a->sy = a->sy + a->speed;
   }
   else{
       a->sx = a->sx + a->speed;
       a->sy = a->sy;
   }

}

void creat_asteroid_link(Asteroid *a)  //创建储存彗星信息的链表
{
    a->before_link = NULL;
    a->after_link = NULL;
    Asteroid *b;
    b = a;
    for(int i = 0;i < Asteroid_Number;i++)
    {
        Asteroid *p;
        p = malloc(sizeof(Asteroid));
        b->after_link = p;
        p->before_link = b;
        p->after_link = NULL;
        p = NULL;
        b = b->after_link;

    }


}

void creat_asteroid_link_15(Asteroid *a)
{
    Asteroid *b;
    b = a;
    for(int i = 0;i < Asteroid_Number;i++)
    {
        Asteroid *p;
        p = malloc(sizeof(Asteroid));
        b->after_link = p;
        p->before_link = b;
        p->after_link = NULL;
        p = NULL;
        b = b->after_link;

    }

}

void Init_Asteroid(Asteroid *a)          //初始化彗星的位置等信息
{
    for(int i = 0;i < Asteroid_Number;i++)     //
    {
        a->sx = rand() % SCREEN_W;
        a->sy = rand() % (SCREEN_H - 100);
        a->rot_velocity = (rand() % 10) / 5;
        a->twist = rand() % 360;
        a->scale = (rand() % 10) / 4;
        a->speed = 1;
        a->heading = rand() % 2;
        a->unbreak = rand() % 2;
        a->color = al_map_rgb(rand()%250,rand()%250,rand()%250);
        a = a->after_link;
        a->_die =1;               //////////////////

    }
}

void Init_New_Asteroid(Asteroid *a)
{
    for(int i = 0;i < Asteroid_Number;i++)     //
    {
        a->heading = rand() % 2;
        if(a->heading == 0)
        {
        a->sx = rand() % SCREEN_W;
        a->sy = 0;
        }
        else{
        a->sx = 0;
        a->sy = rand() % SCREEN_H;
        }
        a->rot_velocity = (rand() % 10) / 5;
        a->twist = rand() % 360;
        a->scale = (rand() % 10) / 4;
        a->speed = rand() % 2 + 0.5;

        a->unbreak = rand() % 2;
        a->color = al_map_rgb(rand()%250,rand()%250,rand()%250);
        a = a->after_link;
        a->_die =1;               //////////////////

    }
}

void draw_food(Food *a)   //画出食物
{
   ALLEGRO_TRANSFORM transform;
   al_identity_transform(&transform);
   al_rotate_transform(&transform,a->twist);
   al_translate_transform(&transform,a->sx,a->sy);
   al_use_transform(&transform);

   al_draw_line(0*a->scale,0*a->scale,20*a->scale,20*a->scale,a->color,3.0f);
   al_draw_line(20*a->scale,20*a->scale,40*a->scale,0*a->scale,a->color,3.0f);
   al_draw_line(0*a->scale,0*a->scale,40*a->scale,0*a->scale,a->color,3.0f);
   al_draw_line(0*a->scale,10*a->scale,40*a->scale,10*a->scale,a->color,3.0f);
   al_draw_line(0*a->scale,10*a->scale,20*a->scale,-10*a->scale,a->color,3.0f);
   al_draw_line(40*a->scale,10*a->scale,20*a->scale,-10*a->scale,a->color,3.0f);

}

void draw_asteroid(Asteroid *a)     //画出彗星
{
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform,a->twist);
    al_translate_transform(&transform,a->sx,a->sy);
    //al_scale_transform(&transform,a->scale,a->scale);
    al_use_transform(&transform);

    al_draw_line(-20*a->scale,20*a->scale,-25*a->scale,5*a->scale,a->color,2.0f);
    al_draw_line(-25*a->scale,5*a->scale,-25*a->scale,-10*a->scale,a->color,2.0f);
    al_draw_line(-25*a->scale,-10*a->scale,-5*a->scale,-10*a->scale,a->color,2.0f);
    al_draw_line(-5*a->scale,-10*a->scale,-10*a->scale,-20*a->scale,a->color,2.0f);
    al_draw_line(-10*a->scale,-20*a->scale,5*a->scale,-20*a->scale,a->color,2.0f);
    al_draw_line(5*a->scale,-20*a->scale,20*a->scale,-10*a->scale,a->color,2.0f);
    al_draw_line(20*a->scale,-10*a->scale,20*a->scale,-5*a->scale,a->color,2.0f);
    al_draw_line(20*a->scale,-5*a->scale,0*a->scale,0*a->scale,a->color,2.0f);
    al_draw_line(0*a->scale,0*a->scale,20*a->scale,10*a->scale,a->color,2.0f);
    al_draw_line(20*a->scale,10*a->scale,10*a->scale,20*a->scale,a->color,2.0f);
    al_draw_line(10*a->scale,20*a->scale,0*a->scale,15*a->scale,a->color,2.0f);
    al_draw_line(0*a->scale,15*a->scale,-20*a->scale,20*a->scale,a->color,2.0f);

}

void change_position(Asteroid *a)     //移动并且旋转彗星
{
    //    if(a->unbreak = 1)              //不可摧毁的彗星
    //    {
    //        a->sx = a->sx + (-1)^
    //    }
    if(a->heading == 1)
    {
        a->sx = a->sx + a->speed;
        a->sy = a->sy + 0.01;
        a->twist = a->twist + 0.1;
        // if(a->unbreak == 1) a->scale = a->scale + ((-1) * rand() % 2);
        if(a->sx > SCREEN_W) a->sx = 0;
        if(a->sy > SCREEN_H)a->sy = 0;
        if(a->sx < 0) a->sx = SCREEN_W;
        if(a->sy < 0) a->sy = SCREEN_H;
    }
    else if (a->heading == 0)
    {
        a->sx = a->sx + rand() % 2;
        a->sy = a->sy + a->speed + 1 + rand()%2;
        a->twist = a->twist + 0.1;
        // if(a->unbreak == 1) a->scale = a->scale + ((-1) * rand() % 2);
        if(a->sx > SCREEN_W) a->sx = 0;
        if(a->sy > SCREEN_H)a->sy = 0;
        if(a->sx < 0) a->sx = SCREEN_W;
        if(a->sy < 0) a->sy = SCREEN_H;

    }


}

void delete_asteroid(Asteroid *a,Asteroid **aa)      //摧毁彗星
{
    Asteroid *a1 = *aa;
    Asteroid *a2;
    while(a1) {
        if(a1==a) {
            a2=a1->before_link;
            if(a2) {
                a2->after_link = a->after_link;
                Asteroid *a3;
                a3 = a->after_link;
                if(a3) a3->before_link = a2;
                free(a);
                return;

            }else{                             //b2 kong
                a2 = a->after_link;
                if(a2) a2->before_link =NULL;
                *aa = a2;                    // bb 被删 ,给bb赋值
                free(a);
                return;
            }

        }else{
            a1 = a1->after_link;
        }
    }
}

void destroy_food(Food *a)
{
    free(a);
}

void creat_new_asteroid(Asteroid **aa)    //创建两个新的小慧星并且初始化他们的信息,temp为保存之前销毁的彗星信息
{
    Asteroid *b;
    Asteroid *c;
    Asteroid *a_before;  //bomb_b的前节点
    Asteroid *a_after;   //bomb_b的后节点

    a_before = bomb_b->before_link;
    a_after = bomb_b->after_link;
    b = malloc(sizeof(Asteroid));       //新建两个结点
    c = malloc(sizeof(Asteroid));

    b->after_link = c;
    c->before_link = b;
    //c->after_link = bomb_b->after_link;
    //a_after->before_link = c;

    Asteroid *d = bomb_b;     // bomb_b 是第一个节点
    //bomb_b = NULL;



    b->scale = d->scale / 2;         //初始化彗星的信息
    b->sx = d->sx ;
    b->sy = d->sy ;
    b->rot_velocity = 0.1;
    b->heading = d->heading;
    b->twist = d->twist + 1;
    b->speed = -0.5;                 //偏左
    b->gone = 1 +d->gone;
    b->color = d->color;
    b->_die =1;               ////////////////////

    c->scale = d->scale / 2;
    c->sx = d->sx ;
    c->sy = d->sy ;
    c->speed = 0.5;                 //偏右
    c->gone = d->gone+1;
    c->twist = d->twist - 1;
    c->rot_velocity = 0.1;
    c->heading = d->heading;
    c->color = d->color;
    c->_die =1;            ///////////////////

    if(a_before != NULL && a_after != NULL) {
        b->before_link = a_before;
        a_before->after_link = b; //ooooo
        c->after_link = a_after;
        a_after->before_link = c;
        free(bomb_b);
        //*aa = b;
    }
    else if(a_after == NULL){
        b->before_link = a_before;
        a_before->after_link = b;
        c->after_link = NULL;
        free(bomb_b);
        //*aa = b;
    }
    else if(a_before == NULL){
        a_after->before_link = c;
        c->after_link = a_after;
        b->before_link = NULL;
        free(bomb_b); //释放bomb_b 对应的节点
        *aa = b;
    }
    bomb_b = NULL;

}

void destroy_asteroid(Asteroid *b)
{
    Asteroid *b1;
    while(b) {
        b1 =b;
        b = b->after_link;
        free(b1);
    }
}

void check_gone_and_numbers(Asteroid **aa)
{
    Asteroid *b = *aa;
    int i = 0;
    while(b){
        if(b->gone > 2){
            delete_asteroid(b,aa);
        }
        else if(b->after_link == NULL && i < 10){
            creat_asteroid_link_15(b);
            Init_New_Asteroid(b);
        }
        i++;
        b = b->after_link;
    }

}


