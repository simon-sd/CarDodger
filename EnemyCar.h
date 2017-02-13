#ifndef ENEMYCAR_H_INCLUDED
#define ENEMYCAR_H_INCLUDED

class EnemyCar:public GameObject
{
private:
        int BoundX;
        int BoundY;

        friend class GameCar;
public:
        EnemyCar();
        EnemyCar(int ,int , ALLEGRO_BITMAP *);

        void Destroy();
        void Render();
        void Collided(int);
};


    EnemyCar::EnemyCar()
    {}

        EnemyCar::EnemyCar( int X, int Y, ALLEGRO_BITMAP * image)
        {
            EnemyCar::X = X;
            EnemyCar::Y= Y;

            EnemyCar::Width = al_get_bitmap_width(image);
            EnemyCar::Height = al_get_bitmap_height(image);

            EnemyCar::BoundX = Width/2;
            EnemyCar::BoundY = Height/2;

            EnemyCar::image = image;
            SetID(ENEMY);
        }



void EnemyCar::Render()
{
    GameObject::Render();
    al_draw_bitmap(image, X - Width/2, Y-Height/2, NULL );
    Y = Y + rand()%10+2;
}

void EnemyCar::Collided(int objectID)
{
	if(objectID != ENEMY)
	SetAlive(false);
}

void EnemyCar::Destroy()
{
    if (image != NULL)
    {
        al_destroy_bitmap(image);
    }
}
#endif // ENEMYCAR_H_INCLUDED
