#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

const int WIDTH = 1000;
const int HEIGHT = 700;

enum STATE{START, PLAYING, LOST};
enum KEYS{RELEASED,SPACE,UP,DOWN,LEFT, RIGHT};
enum ID{ENEMY ,CAR, COIN };

int MoveSpeedX = 10;
int MoveSpeedY = 5;




#endif // GLOBAL_H_INCLUDED
