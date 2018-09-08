#ifndef ASTEROID_H
#define ASTEROID_H

#define Asteroid_Number 30
#include <allegro5/allegro_color.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/system.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/transformations.h>


typedef struct Asteroid{
    float sx;                       // 位置
    float sy;
    float heading;                  // 朝向
    float twist;                    // 当前的角度
    float speed;                    //彗星的速度
    float rot_velocity;             //转速
    float scale;                    //大小
    int gone;                       // 摧毁次数
    int unbreak;   //判断是否为不可摧毁的特殊彗星
    int _die;
    ALLEGRO_COLOR color;            //彗星的颜色
    struct Asteroid *before_link;   //指向彗星的前一个节点
    struct Asteroid *after_link;    //指向彗星的后一个节点
}Asteroid;

typedef struct Food{
    float sx;
    float sy;
    float speed;
    float twist;
    int type;                  //为1时食物竖着飞 为0时食物横着飞
    float scale;
    ALLEGRO_COLOR color;
}Food;

void creat_asteroid_link(Asteroid *a);  //创建保存彗星信息的链表
void Init_Asteroid(Asteroid *a);             //初始化彗星的信息
void draw_asteroid(Asteroid *a);        //画出彗星
void change_position(Asteroid *a);      //改变彗星的位置和旋转
void delete_asteroid(Asteroid *a, Asteroid **aa);     //摧毁被击中的彗星
void destroy_asteroid(Asteroid *b);
void creat_new_asteroid(Asteroid **aa);    //创建两个新的小慧星并且初始化他们的信息,temp为保存之前被击中的彗星信息
void check_gone_and_numbers(Asteroid **aa);    //检查彗星的摧毁次数和剩余的数量
void creat_asteroid_link_15(Asteroid *a);  //当彗星数量少于10时 新建15个彗星
void Init_New_Asteroid(Asteroid *a);    //用来初始化彗星少于10个时新生成的彗星
void creat_and_init_food(Food *a);      //创建和初始化食物
void change_food_position(Food *a);     //改变食物的位置
void draw_food(Food *a);   //画出食物
void destroy_food(Food *a);   //摧毁食物
#endif // ASTEROID_H
