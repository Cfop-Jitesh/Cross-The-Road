#include "raylib.h"

#ifndef FUNCTION_H 
#define FUNCTION_H 
 
typedef struct{
    Rectangle r;
    float vel;
    int dirc;
}Player;

typedef struct{
    Rectangle r;
    float vel;
    bool outOfScreen;
} Car;
 

 //functions
 void Movement(Player *player);
 bool CheckCollision(Player player, Car car, bool gameOver);
 float GetRotation(Player player);
 void bgResend(float *bg1y, float *bg2y, float bgHeight, Player player);
#endif 

