#include "blasterioids.h"
#include "spaceship.h"
#include "asteroid.h"
#include "blast.h"


enum KEYBOARD{
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE
};

bool key[5] = {false, false, false, false, false};//all keyboard false before enter or after enter.

int score =0;
char text[6] ="0";//关于分数的全局变量定义，则写分数那个函数不需在参数列表里有这两个变量传入。
Asteroid *bomb_b =NULL;
Blast *bb =NULL;

int init(void)
{

    if(!al_init()){
        fprintf(stderr,"failed to initialize allegro!\n");
        return -1;
    }

    if(!al_install_keyboard()){
        fprintf(stderr,"failed to initilize keyboard!\n");
        return -1;
    }

    if(!al_install_mouse()) {
       fprintf(stderr, "failed to initialize the mouse!\n");
       return -1;
    }

    timer = al_create_timer(1.0/FPS);
    if(!timer){
        fprintf(stderr,"failed to creat timer.\n");
        return -1;
    }

    display = al_create_display(SCREEN_W,SCREEN_H);
    if(!display){
        fprintf(stderr,"failed to creat display.\n");
        al_destroy_timer(timer);
        return -1;
    }




    event_queue = al_create_event_queue();
    if(!event_queue){
        fprintf(stderr,"failed to creat event_queue.\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
    al_init_font_addon();
    al_init_ttf_addon();

    font1 = al_load_font("../Blastingthecomet/fonts/actionis.ttf",70,0);
    font2 = al_load_font("../Blastingthecomet/fonts/actionis.ttf",200,0);
    font3 = al_load_font("../Blastingthecomet/fonts/actionis.ttf",120,0);
    font4 = al_load_font("../Blastingthecomet/fonts/actionis.ttf",80,0);


    if(!font1){
        fprintf(stderr,"could not load font.\n");
        return -1;
    }

    al_init_image_addon();
    image1 = al_load_bitmap("../Blastingthecomet/image/xingkong.png");

    if(!image1) {
        fprintf(stderr,"could not load image1.\n");
        return -1;
    }

    if(!al_install_audio()){
        fprintf(stderr, "failed to initialize audio!\n");
        return 0;
    }

    if(!al_init_acodec_addon()){
        fprintf(stderr, "failed to initialize audio codecs!\n");
        return 0;
    }

    if (!al_reserve_samples(2)){
        fprintf(stderr, "failed to reserve samples!\n");
        return 0;
    }

    sample1 = al_load_sample( "../Blastingthecomet/sounds/游戏过程.wav" );
    sample2 = al_load_sample( "../Blastingthecomet/sounds/炮弹声.wav" );

    if (!sample1){
        printf( "Audio clip sample not loaded!\n" );
        return 0;
    }

    /* Loop the sample until the display closes. */
     al_play_sample(sample1, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

    //make keyboard,timer,display enter in the event.

    al_register_event_source(event_queue,al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue,al_get_timer_event_source(timer));

    al_register_event_source(event_queue,al_get_display_event_source(display));

    al_clear_to_color(al_map_rgb(0,0,0));

    char *text1 = " comet pop ";
    start(text1);

    char *text2 = " Hello";
    al_draw_text(font3,al_map_rgb(225,0,50),130,50,ALLEGRO_ALIGN_CENTER,text2);

    char *text5 = "$ & !!! ----";
    al_draw_text(font4,al_map_rgb(0,100,225),650,100,ALLEGRO_ALIGN_CENTER,text5);

    char *text3 = " Welcome to game !!!";
    al_draw_text(font4,al_map_rgb(0,225,50),250,500,ALLEGRO_ALIGN_LEFT,text3);

    al_flip_display();

    al_rest(4);

    return 0;

}




void destroy(void)
{
    if (timer)
        al_destroy_timer(timer);

    if (display)
        al_destroy_display(display);

    if (event_queue)
        al_destroy_event_queue(event_queue);

    if (image1)
        al_destroy_bitmap(image1);

    if (image2)
        al_destroy_bitmap(image2);
}



void game_ing(void)
{
    al_start_timer(timer);

    Spaceship *s = malloc(sizeof(Spaceship));
    Asteroid *a = malloc(sizeof(Asteroid));
    Food *f = malloc(sizeof(Food));
    bool redraw = true;

    init_spaceship(s);
    creat_asteroid_link(a);
    Init_Asteroid(a);
    creat_and_init_food(f);


    while(s->gone!=0)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            if (key[KEY_UP]) {
                s->speed += 0.1;
            }
            if (key[KEY_DOWN] && s->speed >0) {
                s->speed -= 0.1;
            }
            if(key[KEY_LEFT]) {
                s->heading -= 0.05;
            }
            if(key[KEY_RIGHT]) {
                s->heading += 0.05;
            }
            if(key[KEY_SPACE]){
                creat_blast(s);
            }

            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                key[KEY_UP] = true;
                break;

            case ALLEGRO_KEY_DOWN:
                key[KEY_DOWN] = true;
                break;

            case ALLEGRO_KEY_LEFT:
                key[KEY_LEFT] = true;
                break;

            case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = true;
                break;

            case ALLEGRO_KEY_SPACE:
                key[KEY_SPACE] = true;
                break;
            }
        }else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
                 ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

            s->sx = ev.mouse.x-13;
            s->sy = ev.mouse.y+5;
         }
        else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                key[KEY_UP] = false;
                s->speed =0;
                break;

            case ALLEGRO_KEY_DOWN:
                key[KEY_DOWN] = false;
                break;

            case ALLEGRO_KEY_LEFT:
                key[KEY_LEFT] = false;
                break;

            case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = false;
                break;

            case ALLEGRO_KEY_SPACE:
                key[KEY_SPACE] = false;
                break;

            case ALLEGRO_KEY_ESCAPE:
                s->gone = 0;
                break;
            }

        }

        if(redraw && al_is_event_queue_empty(event_queue )) {

            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));

            ALLEGRO_TRANSFORM transform;
            al_identity_transform(&transform);
            al_rotate_transform(&transform,0);
            al_translate_transform(&transform,0,0);
            al_use_transform(&transform);
            al_draw_bitmap(image1,0,0,0);

            s_hit_comet(s,&a);
            draw_ship(s);
            rest_life(s->gone);
            print_score(s->gone);

            Asteroid *b;
            b = a;

            while(b) {
                check_gone_and_numbers(&a);
                draw_asteroid(b);
                change_position(b);
                b = b->after_link;

            }

            if(f){
            draw_food(f);
            change_food_position(f);
           }
            if(bb) {
                Blast *b5 =bb;
                while(b5) {
                    draw_blast2(b5,a);//包含记录被击中的彗星(bomb)。hit_commet()
                    if(bomb_b && bomb_b->_die == 0) {           //////////////////
                        al_play_sample(sample2, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                        creat_new_asteroid(&a);
                        bomb_b = NULL;
                        score += 100;
                        delete_blast(b5);
                    }
                    b5 = b5->after_link;
                }
            }


            al_flip_display();

        }

    }
    destroy_blast();
    destroy_asteroid(a);
    destroy_ship(s);
    printf("  You failed! \n");

}

int itoa(int num, char *dest)
{
    if(dest == NULL)
        return -1;

    char temp[24];
    temp[23] = '\0';
    char *p = &temp[22];
    while(num/10 != 0){
        *(p--) = num%10 + 48;
        num = num /10;
    }
    *p = num%10 + 48;
    strcpy(dest, p);
    return 0;
}

void print_score(int gone)
{
    itoa(score,text);
    int add = 0;
    for(int i=3-gone;i!=0;i--) {
        add +=25;
    }

    int score_center_to_left =-27+add;
    if(score /10 >=4) score_center_to_left =2+add;

    al_draw_text(font1,al_map_rgb(225,225,50),score_center_to_left
                 ,20,ALLEGRO_ALIGN_CENTER,text);
}

void start(char *text)
{
    al_draw_text(font2,al_map_rgb(225,225,50),500,250,ALLEGRO_ALIGN_CENTER,text);
}


