#ifndef COIN_H_INCLUDED
#define COIN_H_INCLUDED

class Coin: public GameObject
{
private:
    int BoundX;
    int BoundY;

    friend class GameCar;
public:
    Coin();
    Coin(int , int , ALLEGRO_BITMAP *);

    void SetBoundX(int);
    void SetBoundY(int);

    int GetBoundX();
    int GetBoundY();
    void Render();

};

    Coin::Coin()
    {
        BoundX = 0;
        BoundY = 0;
    }

    Coin::Coin(int X, int Y, ALLEGRO_BITMAP *image)
    {
        Coin::X = X;
        Coin::Y = Y;

        Coin::Width = al_get_bitmap_width(image);
        Coin::Height = al_get_bitmap_height(image);

        Coin::BoundX = Width/2;
        Coin::BoundY = Height/2;

        Coin::image = image;

        SetID(COIN);
    }
    int Coin::GetBoundX()
    {
        return BoundX;
    }

    int Coin::GetBoundY()
    {
        return BoundY;
    }

    void Coin::SetBoundX(int BoundX)
    {
        Coin::BoundX = BoundX;
    }

    void Coin::SetBoundY(int BoundY)
    {
        Coin::BoundY = BoundY;
    }
void Coin::Render()
{
    GameObject::Render();
    al_draw_bitmap(image, X - Width/2, Y-Height/2, NULL );
    //Y = Y + rand()%100+2;
}


#endif // COIN_H_INCLUDED
