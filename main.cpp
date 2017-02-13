#include <iostream>
#include <ctime>
#include <cstdlib>
#include <allegro5/allegro.h> //Main Allegro header
#include <allegro5/allegro_native_dialog.h> //Header for dialogue boxes
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <list>

#include "Global.h"
#include "GameObject.h"
#include "GameCar.h"
#include "EnemyCar.h"


GameCar *Car;
EnemyCar *eCar;
GameObject *Begin, *End;
Coin *coin;

std::list<GameObject *> objects;
std::list<GameObject *>::iterator iter;
std::list<GameObject *>::iterator iter2;

int RandNum(void);
int q=0;
void ChangeState(int &state, int newState);

int main()
{
bool DrawImage = true;
bool done=false;
bool render=false;

float gameTime = 0;
int frames = 0;
int gameFPS = 0;
int state = -1;
//Project Variable

ALLEGRO_BITMAP *CarImage, *eCarImage, *BeginImage, *EndImage, *CoinImage;

//allegro variable
ALLEGRO_DISPLAY *MainDisplay = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_FONT *font;
ALLEGRO_TIMER *timer;


//program initialize
if(!al_init())
al_show_native_message_box(NULL, NULL, NULL, "Could not initialize Allegro 5", NULL, NULL);

MainDisplay = al_create_display(WIDTH, HEIGHT);
al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);

if(!MainDisplay)
al_show_native_message_box(NULL, NULL, NULL, "Could not create Allegro 5 display", NULL, NULL);

al_set_window_position(MainDisplay,0,0);
al_set_window_title(MainDisplay,"CarDodger");

//addon initialize
al_init_image_addon();
al_install_keyboard();
al_init_primitives_addon();
al_init_font_addon();
al_init_ttf_addon();


BeginImage=al_load_bitmap("batman1.jpg");
EndImage=al_load_bitmap("batmap2.jpg");

eCarImage=al_load_bitmap("Car2.png");
CarImage=al_load_bitmap("Car1.png");
CoinImage=al_load_bitmap("Coin.jpg");

/*Begin = new GameObject();
Begin->init(500,350,BeginImage);

End = new GameObject();
End->init(500,350,EndImage);*/

Car = new GameCar(150,600,CarImage);
objects.push_back(Car);

eCar = new EnemyCar( RandNum(), 0, eCarImage);
objects.push_back(eCar);

coin= new Coin(RandNum(), 50, CoinImage);
objects.push_back(coin);

font = al_load_font("arial.ttf",18,0);

//ChangeState( state, START);
srand(time(NULL));

//for events
event_queue = al_create_event_queue();
timer=al_create_timer(1.0/60);

al_register_event_source(event_queue,al_get_timer_event_source(timer));
al_register_event_source(event_queue, al_get_keyboard_event_source());

al_start_timer(timer);
gameTime = al_current_time();

//game loop
while(!done)
{
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch(ev.keyboard.keycode)
        {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_UP:
                Car->SetDir(UP);
                break;
            case ALLEGRO_KEY_DOWN:
                Car->SetDir(DOWN);
                break;
            case ALLEGRO_KEY_LEFT:
                Car->SetDir(LEFT);
                break;
			case ALLEGRO_KEY_RIGHT:
				Car->SetDir(RIGHT);
				break;
			/*case ALLEGRO_KEY_SPACE:
				dir = SPACE;
                break;*/
        }
    }

    if (ev.type == ALLEGRO_EVENT_KEY_UP)
    {
        switch(ev.keyboard.keycode)
        {
            case ALLEGRO_KEY_LEFT:
                Car->SetDir(RELEASED);
                break;
			case ALLEGRO_KEY_RIGHT:
				Car->SetDir(RELEASED);
				break;
            case ALLEGRO_KEY_UP:
                Car->SetDir(RELEASED);
                break;
			case ALLEGRO_KEY_DOWN:
				Car->SetDir(RELEASED);
				break;
			/*case ALLEGRO_KEY_SPACE:
				dir = SPACE;
                break;*/
        }
    }

    if(ev.type == ALLEGRO_EVENT_TIMER)
    {
        render = true;

            frames++;
			if(al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}

        switch(Car->GetDir())
        {
            case RIGHT:
				Car->MoveRight();
				break;

            case LEFT:
				Car->MoveLeft();
				break;

			case UP:
                Car->MoveUp();
                break;

            case DOWN:
                Car->MoveDown();
                break;

			case RELEASED:
				Car->KeyReleased();
                break;
            /*case SPACE:

            */

        }

            if(rand() % 50 ==0)
            {
                eCar = new EnemyCar( RandNum(), -20, eCarImage);
               objects.push_back(eCar);

            }
            if(rand() % 20 ==0)
            {
                coin = new Coin( RandNum(), RandNum(), CoinImage);
               objects.push_back(coin);

            }
            for(iter = objects.begin(); iter != objects.end(); ++iter)
				{
					if( ! (*iter)->GetCollidable() ) continue; // continue to remaining part of loop if, if statement is false.

					for(iter2 = iter; iter2 != objects.end(); ++iter2)
					{
						if( !(*iter2)->GetCollidable() ) continue;
						if( (*iter)->GetID() == (*iter2)->GetID()) continue;

						if( (*iter)->CheckCollisions( (*iter2)))
						{
							(*iter)->Collided( (*iter2)->GetID());
							(*iter2)->Collided( (*iter)->GetID());
							/*if((*iter2)->GetID()==COIN)
                                Car->Score++;
                            if((*iter2)->GetID()==ENEMY)
                                Car->lives--;*/

                                al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, 20, NULL, "collision" );

                        }
					}
				   if(Car->GetLives() <= 0)
					{
                    al_draw_text(font, al_map_rgb(255,255,255), 500, 20, NULL, "GameOver" );
					//ChangeState(state, LOST);
					}
				}



    }

    //UPDATING
    //=============================================================================================

    //==============================================================================================
    //BEGIN PROJECT RENDER
    if(render)
        {


                    al_draw_textf(font, al_map_rgb(255,255,255), WIDTH/2, 40,NULL , "Score is %i and Lives Remaining are %i",Car->GetScore(), Car->GetLives());
                    for(iter = objects.begin(); iter != objects.end(); ++iter)
					(*iter)->Render();



            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }


}
//deallocate memory
for(iter = objects.begin(); iter != objects.end();iter++ )
	{
		(*iter)->Destroy();
		delete (*iter);
	}
al_destroy_display(MainDisplay);
al_destroy_font(font);
al_destroy_event_queue(event_queue);
al_destroy_timer(timer);
return 0;
}

int RandNum()
{
    srand((unsigned)time(0));
    abc:
    int i = (rand()%1000);
    int randX = (rand()%i)+1;
    if(q>(randX-100)&&(q<randX+100))
    {
        goto abc;
    }
    else
    {
        if(randX>100 && randX<950)
        {
            q=randX;
            return randX;
        }
       else
           goto abc;
    }
}

/*void ChangeState(int &state, int newState)
{
	if(state ==START)
	{}
	else if(state == PLAYING)
	{
		for(iter = objects.begin(); iter != objects.end(); ++iter)
		{
			if( (*iter)->GetID() != CAR )
				(*iter)->SetAlive(false);
		}

	}
	else if(state == LOST)
	{}

	state = newState;

	if(state ==START)
	{}
	else if(state == PLAYING)
	{
		Car = new GameCar();
	}
	else if(state == LOST)
	{}
}*/
