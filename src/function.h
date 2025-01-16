#include "raylib.h"

#ifndef FUNCTION_H 
#define FUNCTION_H 
 
extern int Score;
typedef struct{
    Rectangle r;
    float vel;
    int dirc;
}Player;

typedef struct{
    Rectangle r;
    Texture2D t;
    float vel;
    bool outOfScreen;
    float rotation;
} Car;
 

//functions
void Movement(Player *player);
bool CheckCollision(Player player, Car car, bool gameOver);
float GetRotation(Player *player);
void bgResend(float *bg1y, float *bg2y, float bgHeight, Player player);
void spawnCar(Car *car, Vector2 bg, int carSide, int carLane);
void MoveCar(Car *car, Player player, int side, int *FS);
#endif 

