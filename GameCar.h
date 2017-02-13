#ifndef GAMECAR_H_INCLUDED
#define GAMECAR_H_INCLUDED

#include "GameObject.h"
#include "EnemyCar.h"
#include "Coin.h"

class GameCar:public GameObject
{
private:
        int lives;
        int Score;

        int Dir;
public:
        friend int main();
        GameCar();
        GameCar(int , int , ALLEGRO_BITMAP *);

        int GetScore();

        void SetDir(int );

        int GetDir() ;
        int GetLives();

        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();
        void KeyReleased();
        void Render();
        void Collided(int);
        };

    GameCar::GameCar()
    {
        BoundX = 0;
        BoundY = 0;

        Dir= 0;

        lives = 0;
        Score=0;
    }

     GameCar::GameCar( int X, int Y, ALLEGRO_BITMAP * image)
        {
            GameCar::X = X;
            GameCar::Y = Y;

            GameCar::Width = al_get_bitmap_width(image);
            GameCar::Height = al_get_bitmap_height(image);

            GameCar::BoundX = Width/2;
            GameCar::BoundY = Height/2;

            GameCar::image = image;

            SetID(CAR);

            lives = 3;
            Score = 0;
        }

void GameCar::SetDir(int Dir)   {GameCar::Dir = Dir;}
int GameCar::GetDir()   {return Dir;}


void GameCar::MoveLeft()
{
    if(X>=Width/2)
        X = X-MoveSpeedX;
}

void GameCar::MoveRight()
{
    if(X<=WIDTH-Width/2)
        X=X+MoveSpeedX;
}

void GameCar::KeyReleased()
{
    X=X;
    Y=Y;
}

int GameCar::GetScore()
{
    return Score;
}
void GameCar::MoveUp()
{
    if(Y>=Height/2)
        Y = Y-MoveSpeedX;
}

void GameCar::MoveDown()
{
    if(Y<HEIGHT-Height/2)
        Y=Y+MoveSpeedX;
}

void GameCar::Render()
{
    GameObject::Render();
    al_draw_bitmap(image, X-Width/2, Y-Height/2,NULL);
}

void GameCar::Collided(int objectID)
{
	if(objectID == ENEMY)
		{
            lives-=1;

		}
}

int GameCar::GetLives()
{
    return lives;
}
#endif // GAMECAR_H_INCLUDED
