#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>


class GameObject
{
private:
        int ID;
        bool Alive;
        bool Collidable;

protected:
        float X;
        float Y;

        int Width;
        int Height;

        int BoundX;
        int BoundY;
public:
        GameObject();

        ALLEGRO_BITMAP *image;

        void virtual Destroy();

        float GetX();
        float GetY();

        void SetID(int);
        int GetID();

        void init(int, int, ALLEGRO_BITMAP *);

        void SetX(float );
        void SetY(float );

        void SetWidth(int );
        void SetHeight(int );

        int GetBoundX();
        int GetBoundY();

        void SetBoundX(int);
        void SetBoundY(int);

        int GetWidth();
        int GetHeight();

        void SetAlive(bool);
        bool GetAlive();

        void SetCollidable(bool);
        bool GetCollidable();

        void Collided(int);

        void virtual Update();

        void virtual Render();
        bool CheckCollisions(GameObject *);
};

GameObject::GameObject()
{
    X=0;
    Y=0;

    Width = 0;
    Height = 0;

    BoundX = 0;
    BoundY=0;

    ID = 0;
    Alive = true;
    Collidable = true;
}

void GameObject::init(int X, int Y, ALLEGRO_BITMAP * image)
{
            GameObject::X = X;
            GameObject::Y= Y;

            GameObject::Width = al_get_bitmap_width(image);
            GameObject::Height = al_get_bitmap_height(image);

            GameObject::BoundX = Width/2;
            GameObject::BoundY = Height/2;

            GameObject::image = image;
}

void GameObject::Destroy()
{
    if (image != NULL)
    {
        al_destroy_bitmap(image);
    }
}

void GameObject::SetX(float X){GameObject::X=X;}
void GameObject::SetY(float Y){GameObject::Y=Y;}

float GameObject::GetX(){ return X;}
float GameObject::GetY(){ return Y;}

void GameObject::SetWidth(int Width) {GameObject::Width = Width;}
void GameObject::SetHeight(int Height) {GameObject::Height = Height;}

int GameObject::GetWidth()    {return Width;}
int GameObject::GetHeight()   {return Height;}

void GameObject::SetID(int ID)  {GameObject::ID = ID;}
int GameObject::GetID()   {return ID;}

void GameObject::SetAlive(bool Alive)   {GameObject::Alive = Alive;}
bool GameObject::GetAlive() {return Alive;}

void GameObject::SetCollidable(bool Collidable)   {GameObject::Collidable = Collidable;}
bool GameObject::GetCollidable() {return Alive && Collidable;}

void GameObject::Collided(int objectID){}
void GameObject::Update()
{}

void GameObject::Render(){}

void GameObject::SetBoundX(int BoundX) {GameObject::BoundX = BoundX;}
void GameObject::SetBoundY(int BoundY) {GameObject::BoundY = BoundY;}

int GameObject::GetBoundX() {return BoundX;}
int GameObject::GetBoundY() {return BoundY;}

bool GameObject::CheckCollisions(GameObject* OtherObject)
{
        float oX = OtherObject->X;
        float oY = OtherObject->Y;

        int obX = OtherObject->BoundX;
        int obY = OtherObject->BoundY;

        if( X + BoundX > oX - obX && X - BoundX < oX + obX && Y + BoundY > oY - obY && Y - BoundY < oY + obY)
		return true;
	else
		return false;
}
#endif // GAMEOBJECT_H_INCLUDED
