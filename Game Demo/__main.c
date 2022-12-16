#include "CanvasTable.h"

extern CTimgfont SHS22px;
extern char SHS22px_charlist[7592][4];
extern int SHS22px_glyphlist[7592][4];

int LANGUAGE = 0; //language var

CTscene scene1; //scene object : scene1
void scene1_sm(); //sprite map of the scene1
int scene1_0[1296]; //tile map of the scene1 - layer 0
int scene1_1[1296]; //tile map of the scene1 - layer 1
int scene1_2[1296]; //tile map of the scene1 - layer 2

CTwindow win_language; //window object : win_language
CTui but_ch; //ui object : but_ch
CTui but_en; //ui object : but_en
CTwindow win_hint; //window object : win_hint
CTui box_hint; //ui object : box_hint

CTsprite menuprog; //sprite object : menuprog
void menuprog_main(); //main function of the menuprog
void menuprog_loop(); //loop function of the menuprog

CTsprite SceneRunner; //sprite object : SceneRunner
void SceneRunner_main(); //main function of the menuprog
void SceneRunner_loop(); //loop function of the menuprog

CTsprite spr_player; //sprite object : spr_player
void spr_player_main(); //main function of the spr_player
void spr_player_loop(); //loop function of the spr_player

CTsprite spr_wall; //sprite object : spr_wall

CTsprite spr_ball; //sprite object : spr_ball
void spr_ball_main(); //main function of the spr_ball
void spr_ball_loop(); //loop function of the spr_ball

int player_index = 0; //player sprite the index

void ENTITYmain()
{
    char *ResList[] = 
    {
        "res/font/SHS22px_ASCII_GB2312.bmp",
        "res/img/img_player.bmp",
        "res/img/tile1.bmp",
        "res/img/ball.bmp",
        "res/img/wall.bmp",
        "res/img/touch_up.bmp",
        "res/img/touch_down.bmp",
        "res/img/touch_left.bmp",
        "res/img/touch_right.bmp",
        "res/img/touch_space.bmp",
        "res/audio/shoot.wav"
    }; //res list
    CT_init(960,540,ResList,sizeof(ResList)/sizeof(char*),CT_main,CT_loop,1,1,1,960,540,0,0,0,0,0,0,0,0,0,0,0);
}

void CT_main()
{
    //new imgfont
    CTimgfont_new(&SHS22px);
    SHS22px.FontImg = res("res/font/SHS22px_ASCII_GB2312.bmp");
    SHS22px.CharNumber = 7592;
    SHS22px.CharHeight = 22;
    SHS22px.GlyphList = SHS22px_glyphlist;
    SHS22px.CharList = SHS22px_charlist;

    //new win_language
    CTwindow_new(&win_language);
    win_language.width = 400;
    win_language.height = 200;
    win_language.x = 280;
    win_language.y = 170;

    //new but_ch
    CTbutton_new(&but_ch);
    but_ch.width = 400;
    but_ch.height = 90;
    but_ch.x = 0;
    but_ch.y = 0;
    but_ch.imgfont = &SHS22px;
    but_ch.text = "中文";

    //new but_en
    CTbutton_new(&but_en);
    but_en.width = 400;
    but_en.height = 90;
    but_en.x = 0;
    but_en.y = 110;
    but_en.imgfont = &SHS22px;
    but_en.text = "English";

    //new menuprog
    CTsprite_new(&menuprog);
    menuprog.main = menuprog_main;
    menuprog.loop = menuprog_loop;

    //new win_hint
    CTwindow_new(&win_hint);
    win_hint.layer = 5;
    win_hint.width = 400;
    win_hint.height = 40;
    win_hint.x = 558;
    win_hint.y = 2;

    //new box_hint
    CTtextbox_new(&box_hint);
    box_hint.x = 10;
    box_hint.y = 6;
    box_hint.readonly = 1;
    box_hint.width = 380;
    box_hint.color_text = 0x0000ffff;
    box_hint.imgfont = &SHS22px;

    //new scene1
    CTscene_new(&scene1);
    scene1.width = 1440;
    scene1.height = 810;
    scene1.tile_image[0] = res("res/img/tile1.bmp");
    scene1.tile_offset = 1;
    scene1.tile_map[0] = scene1_0;
    scene1.tile_map[1] = scene1_1;
    scene1.tile_map[2] = scene1_2;
    scene1.sprite_map = scene1_sm;

    //new spr_player
    CTsprite_new(&spr_player);
    spr_player.image = res("res/img/img_player.bmp");
    spr_player.subimg_o = 1;
    spr_player.subnum = 12;
    spr_player.layer = 2;
    spr_player.main = spr_player_main;
    spr_player.loop = spr_player_loop;

    //new spr_wall
    CTsprite_new(&spr_wall);
    spr_wall.image = res("res/img/wall.bmp");
    spr_wall.collision_edge = 1;
    spr_wall.layer = 2;

    //new spr_ball
    CTsprite_new(&spr_ball);
    spr_ball.layer = 2;
    spr_ball.image = res("res/img/ball.bmp");
    spr_ball.subimg_o = 1;
    spr_ball.main = spr_ball_main;
    spr_ball.loop = spr_ball_loop;

    //new SceneRunner
    CTsprite_new(&SceneRunner);
    SceneRunner.main = SceneRunner_main;
    SceneRunner.loop = SceneRunner_loop;


    sprite_create(0,0,&menuprog); //start the language menu
}

void CT_loop()
{

}

//------------------------------------------------------------------------
// MenuProg Program
//------------------------------------------------------------------------
void menuprog_main()
{
    //create the UI of the main menu
    CTwindow_create(&win_language);
    CTui_create(&win_language,&but_ch);
    CTui_create(&win_language,&but_en);
}
void menuprog_loop()
{
    //select language,and then enter scene1
    if(button_click(&but_ch))
    {
        LANGUAGE = 1;
        scene_enter(&scene1);
    }
    if(button_click(&but_en))
    {
        LANGUAGE = 2;
        scene_enter(&scene1);
    }
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
// SceneRunner Program
//------------------------------------------------------------------------
void SceneRunner_main()
{
    int scene_w = scene_width();
    int scene_h = scene_height();
    int grid_w = grid_width();
    int grid_h = grid_height();
    int i;
    int i2;

    spritenum_set(0,0); //switch message

    //Create the hint window
    CTwindow_create(&win_hint);
    CTui_create(&win_hint,&box_hint);

    //Timer of hint
    timer_set("hint",2);
    timer_run("hint");

    //create TouchKey
    touchkey_create(0,50,390,50,50,key_up);
    touchkey_image(0,res("res/img/touch_up.bmp"));
    touchkey_create(1,50,490,50,50,key_down);
    touchkey_image(1,res("res/img/touch_down.bmp"));
    touchkey_create(2,0,440,50,50,key_left);
    touchkey_image(2,res("res/img/touch_left.bmp"));
    touchkey_create(3,100,440,50,50,key_right);
    touchkey_image(3,res("res/img/touch_right.bmp"));
    touchkey_create(4,860,440,50,50,key_space);
    touchkey_image(4,res("res/img/touch_space.bmp"));

    //Create the wall object
    for(i=0;i<scene_h;i+=grid_h)
    {
        for(i2=0;i2<scene_w;i2+=grid_w)
        {
            if(tile_check(2,i2,i))
            {
                sprite_create(i2,i,&spr_wall);
            }
        }
    }
}
void SceneRunner_loop()
{
    //if timer is end,show or switch the hint message
    if(timer_end("hint"))
    {
        if(spritenum(0) == 0)
        {
            if(LANGUAGE == 1)
            {
                textbox_set_string(&box_hint,"提示：按<上 下 左 右>键移动。");
            }
            if(LANGUAGE == 2)
            {
                textbox_set_string(&box_hint,"HINT : Press <UP DOWN LEFT RIGHT> key to move.");
            }
            spritenum_set(0,1);
            timer_run("hint");
            return;
        }
        if(spritenum(0) == 1)
        {
            if(LANGUAGE == 1)
            {
                textbox_set_string(&box_hint,"提示：按<空格>键发射球。");
            }
            if(LANGUAGE == 2)
            {
                textbox_set_string(&box_hint,"HINT : Press <SPACE> key to shoot ball."); 
            }
            spritenum_set(0,0);
            timer_run("hint");
            return;
        }
    }
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
// spr_player Programm
//------------------------------------------------------------------------
void spr_player_main()
{
    spritenum_set(0,0); //move status
    spritenum_set(1,1); //direction
    spritenum_set(2,-1); //next position the x
    spritenum_set(3,-1); //next position the y
    spritenum_set(4,0); //subimage index
    spritenum_set(5,0); //animation status
    player_index = sprite_index();
    timer_set("player_ani",0.05); //create the animation timer
}
void spr_player_loop()
{
    int next_x = 0;
    int next_y = 0;

    //Set player move
    if(keyboard_press(key_up))
    {
        if(spritenum(0) == 0)
        {
            spritenum_set(1,1);
            spritenum_set(0,1);
            next_y = sprite_y() - 30;
            spritenum_set(3,next_y);
            spritenum_set(5,1);
            sprite_set_subimg(0);
            timer_run("player_ani");
        }
    }
    if(keyboard_press(key_down))
    {
        if(spritenum(0) == 0)
        {
            spritenum_set(1,2);
            spritenum_set(0,1);
            next_y = sprite_y() + 30;
            spritenum_set(3,next_y);
            spritenum_set(5,1);
            sprite_set_subimg(3);
            timer_run("player_ani");
        }
    }
    if(keyboard_press(key_left))
    {
        if(spritenum(0) == 0)
        {
            spritenum_set(1,3);
            spritenum_set(0,1);
            next_x = sprite_x() - 30;
            spritenum_set(2,next_x);
            spritenum_set(5,1);
            sprite_set_subimg(6);
            timer_run("player_ani");
        }
    }
    if(keyboard_press(key_right))
    {
        if(spritenum(0) == 0)
        {
            spritenum_set(1,4);
            spritenum_set(0,1);
            next_x = sprite_x() + 30;
            spritenum_set(2,next_x);
            spritenum_set(5,1);
            sprite_set_subimg(9);
            timer_run("player_ani");
        }
    }
    if(keyboard_up(key_up))
    {
        if(spritenum(1) == 1)
        {
            spritenum_set(5,0);
        }
    }
    if(keyboard_up(key_down))
    {
        if(spritenum(1) == 2)
        {
            spritenum_set(5,0);
        }
    }
    if(keyboard_up(key_left))
    {
        if(spritenum(1) == 3)
        {
            spritenum_set(5,0);
        }
    }
    if(keyboard_up(key_right))
    {
       if(spritenum(1) == 4)
       {
            spritenum_set(5,0);
       }
    }

    //shoot ball
    if(keyboard_down(key_space))
    {
        if(spritenum(1) == 1)
        {
            sprite_create(sprite_x()+10,sprite_y()-10,&spr_ball);
        }
        if(spritenum(1) == 2)
        {
            sprite_create(sprite_x()+10,sprite_y()+60,&spr_ball);
        }
        if(spritenum(1) == 3)
        {
            sprite_create(sprite_x()-10,sprite_y()+25,&spr_ball);
        }
        if(spritenum(1) == 4)
        {
            sprite_create(sprite_x()+30,sprite_y()+25,&spr_ball);
        }
        audio_play(res("res/audio/shoot.wav"),0);
    }

    //move the process of the player
    if(spritenum(0) == 1)
    {
        if(spritenum(1) == 1)
        {
            if(sprite_y() > spritenum(3))
            {
                sprite_set_y(sprite_y()-5);
            }
            if(sprite_y() == spritenum(3))
            {
                spritenum_set(0,0);
                if(spritenum(5) == 0)
                {                        
                    timer_stop("player_ani");
                    sprite_set_subimg(0);
                }
            }
            if(timer_end("player_ani"))
            {
                if(spritenum(4) >= 0 && spritenum(4) <= 2)
                {
                    spritenum_set(4,spritenum(4)+1);
                }
                if(spritenum(4) < 0 || spritenum(4) > 2)
                {
                    spritenum_set(4,0);
                }
                sprite_set_subimg(spritenum(4));
                timer_run("player_ani");
            }
        }
        if(spritenum(1) == 2)
        {
            if(sprite_y() < spritenum(3))
            {
                sprite_set_y(sprite_y()+5);
            }
            if(sprite_y() == spritenum(3))
            {
                spritenum_set(0,0);
                if(spritenum(5) == 0)
                {
                    timer_stop("player_ani");
                    sprite_set_subimg(3);
                }
            }
            if(timer_end("player_ani"))
            {
                if(spritenum(4) >= 3 && spritenum(4) <= 5)
                {
                    spritenum_set(4,spritenum(4)+1);
                }
                if(spritenum(4) < 3 || spritenum(4) > 5)
                {
                    spritenum_set(4,3);
                }
                sprite_set_subimg(spritenum(4));
                timer_run("player_ani");
            }
        }
        if(spritenum(1) == 3)
        {
            if(sprite_x() > spritenum(2))
            {
                sprite_set_x(sprite_x()-5);
            }
            if(sprite_x() == spritenum(2))
            {
                spritenum_set(0,0);
                if(spritenum(5) == 0)
                {
                    timer_stop("player_ani");
                    sprite_set_subimg(6);
                }
            }
            if(timer_end("player_ani"))
            {
                if(spritenum(4) >= 6 && spritenum(4) <= 8)
                {
                    spritenum_set(4,spritenum(4)+1);
                }
                if(spritenum(4) < 6 || spritenum(4) > 8)
                {
                    spritenum_set(4,6);
                }
                sprite_set_subimg(spritenum(4));
                timer_run("player_ani");
            }
        }
        if(spritenum(1) == 4)
        {
            if(sprite_x() < spritenum(2))
            {
                sprite_set_x(sprite_x()+5);
            }
            if(sprite_x() == spritenum(2))
            {
                spritenum_set(0,0);
                if(spritenum(5) == 0)
                {
                    timer_stop("player_ani");
                    sprite_set_subimg(9);
                }
            }
            if(timer_end("player_ani"))
            {
                if(spritenum(4) >= 9 && spritenum(4) <= 11)
                {
                    spritenum_set(4,spritenum(4)+1);
                }
                if(spritenum(4) < 9 || spritenum(4) > 11)
                {
                    spritenum_set(4,9);
                }
                sprite_set_subimg(spritenum(4));
                timer_run("player_ani");
            }
        }
    }
    if(sprite_collision(&spr_wall))
    {
        spritenum_set(0,0);
    }
    view_set_x(sprite_x()-480);
    view_set_y(sprite_y()-270);
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
// spr_ball Program
//------------------------------------------------------------------------
void spr_ball_main()
{
    int player_dir = ispritenum(player_index,1); //player direction
    spritenum_set(0,player_dir); //ball direction
}
void spr_ball_loop()
{
    //ball move
    if(spritenum(0) == 1)
    {
        sprite_set_y(sprite_y()-10);
    }
    if(spritenum(0) == 2)
    {
        sprite_set_y(sprite_y()+10);
    }
    if(spritenum(0) == 3)
    {
        sprite_set_x(sprite_x()-10);
    }
    if(spritenum(0) == 4)
    {
        sprite_set_x(sprite_x()+10);
    }
    if(spritenum(0) == 5)
    {
        sprite_set_x(sprite_x()-10);
        sprite_set_y(sprite_y()+10);
    }
    if(spritenum(0) == 6)
    {
        sprite_set_x(sprite_x()+10);
        sprite_set_y(sprite_y()+10);
    }
    if(spritenum(0) == 7)
    {
        sprite_set_x(sprite_x()+10);
        sprite_set_y(sprite_y()-10);
    }
    if(spritenum(0) == 8)
    {
        sprite_set_x(sprite_x()-10);
        sprite_set_y(sprite_y()-10);
    }

    //if ball collision to wall
    if(sprite_collision(&spr_wall))
    {
        int right_collision = 0;
        if(sprite_check(sprite_x()+4,sprite_y()-10,&spr_wall))
        {
            right_collision = 1;
            if(spritenum(0) == 1)
            {
                spritenum_set(0,5);
            }
            if(spritenum(0) == 7)
            {
                spritenum_set(0,6);
            }
            if(spritenum(0) == 8)
            {
                spritenum_set(0,5);
            }
        }
        if(sprite_check(sprite_x()+4,sprite_y()+18,&spr_wall))
        {
            right_collision = 1;
            if(spritenum(0) == 2)
            {
                spritenum_set(0,7);
            }
            if(spritenum(0) == 6)
            {
                spritenum_set(0,7);
            }
            if(spritenum(0) == 5)
            {
                spritenum_set(0,8);
            }
        }
        if(sprite_check(sprite_x()-10,sprite_y()+4,&spr_wall))
        {
            right_collision = 1;
            if(spritenum(0) == 3)
            {
                spritenum_set(0,7);
            }
            if(spritenum(0) == 5)
            {
                spritenum_set(0,6);
            }
            if(spritenum(0) == 8)
            {
                spritenum_set(0,7);
            }
        }
        if(sprite_check(sprite_x()+18,sprite_y()+4,&spr_wall))
        {
            right_collision = 1;
            if(spritenum(0) == 4)
            {
                spritenum_set(0,5);
            }
            if(spritenum(0) == 6)
            {
                spritenum_set(0,5);
            }
            if(spritenum(0) == 7)
            {
                spritenum_set(0,8);
            }
        }
        if(right_collision == 0)
        {
            sprite_destroy();
        }
    }
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
// scene1 map
//------------------------------------------------------------------------
int scene1_0[1296] = 
{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 0,
      0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 0,
      0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 0,
      0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 0,
      0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 0,
      0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 0,
      0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 0,
      0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 0,
      0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 0,
      0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 0,
      0, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 0,
      0, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 0,
      0, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
}; //tile map of the scene1 - layer 0

int scene1_1[1296] = 
{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,34,35,35,35,35,35,35,35,35,36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,34,35,35,35,35,35,35,36, 0, 0, 0, 0, 0, 0, 0, 0, 0,44, 0, 0,25, 0, 0, 0, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,44, 0,15,15, 0, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0,44, 0,15, 0, 0, 0,22, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,44, 0,12, 0, 0, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0,44, 0, 0, 0,12, 0, 0, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,44,22, 0, 0,12, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0,44, 0,22, 0, 0, 0, 0, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,44, 0,15, 0,22, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0,44, 0, 0, 0, 0, 0,15,22, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,44, 0,22, 0, 0, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0,44, 0, 0, 0,22, 0, 0, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,44, 0, 0, 0, 0, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0,44, 0, 0, 0, 0, 0, 0, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,54,55,55,55,55,55,55,56, 0, 0, 0, 0, 0, 0, 0, 0, 0,54,55,55,55,55,55,55,55,55,56, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,34,35,35,35,35,35,35,35,35,35,36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,44,25, 0, 0, 0, 0, 0, 0, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,44, 0, 0, 0,22, 0, 0, 0, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,44, 0, 0,15, 0, 0, 0,12, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0,35,35,35,35,35,35,35,36, 0, 0, 0, 0, 0, 0, 0,44, 0, 0, 0, 0, 0,25, 0, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,46, 0, 0, 0, 0, 0, 0, 0,44, 0, 0, 0, 0, 0,22, 0, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0,15, 0,22, 0, 0, 0,46, 0, 0, 0, 0, 0, 0, 0,44, 0, 0, 0, 0, 0, 0, 0, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0,12, 0, 0, 0, 0,46, 0, 0, 0, 0, 0, 0, 0,54,55,55,55,55,55,55,55,55,55,56, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0,25,25, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0,22, 0, 0,15,22, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
}; //tile map of the scene1 - layer 1

int scene1_2[1296] = 
{
     31,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,33,
     41,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,43,
     41,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,37,38,38,38,38,38,39,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,47, 0, 0, 0, 0, 0,49,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,47, 0, 0, 0, 0, 0,49,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,47, 0, 0, 0, 0, 0,49,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,47, 0, 0, 0, 0, 0,49,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,47, 0, 0, 0, 0, 0,49,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,57,58,58,58,58,58,59,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43,
     41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43,
     51,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,53
}; //tile map of the scene1 - layer 2

//sprite map of the scene1
void scene1_sm()
{
    m(0,0,&SceneRunner);
    m(690,420,&spr_player);
}
//------------------------------------------------------------------------