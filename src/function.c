#include "function.h"
#include "raylib.h"
#include "screens.h"

void Movement(Player *player){
    if(IsKeyDown(KEY_W)){
        player->r.y -= player->vel;
        player->dirc = 1;
    }
    else if(IsKeyDown(KEY_A)&&player->r.x>300){
        player->r.x-=player->vel;
        player->dirc = 3;
    }
    else if(IsKeyDown(KEY_D)&&player->r.x < 1050){
        player->r.x += player->vel;
        player->dirc = 4;
    }
}

bool CheckCollision(Player player, Car car, bool gameOver){
    if(CheckCollisionRecs(player.r, car.r)){
        gameOver=true;
        return true;
    }
}

float GetRotation(Player *player){
    int temp;
    if(player->dirc == 1){
        return 180.0f;
    }
    if(player->dirc == 3){
        return 90.0f;
    }
    if(player->dirc == 4){
        return 270.0f;
    }
}

void bgResend(float *bg1y, float *bg2y, float bgHeight, Player player) {
    // Check if bg1 is behind the player
    if (*bg1y > player.r.y + player.r.height+270) {
        *bg1y = *bg2y - bgHeight; // Move bg1 above bg2
    }
    // Check if bg2 is behind the player
    if (*bg2y > player.r.y + player.r.height+270) {
        *bg2y = *bg1y - bgHeight; // Move bg2 above bg1
    }
}

// void SelectTexture()

void spawnCar(Car *car, Vector2 bg, int carSide, int carLane) {
    Vector2 carPosition;

    // Determine the vertical position based on the lane
    float laneHeight = 110.0f; // Adjust based on the lane height in your road texture
    float baseLaneY = bg.y + 200.0f; // Starting y-position for the first lane

    // Calculate lane-specific y-position
    float laneY = baseLaneY + carLane * laneHeight;

    // Determine horizontal position based on car side
    if (carSide == 0) { // Left side
        carPosition = (Vector2){bg.x + 100, laneY};
        car->rotation = 90.0f;
    }
    else if (carSide == 1) { // Right side
        carPosition = (Vector2){bg.x + 800, laneY};
        car->rotation = -90.0f;
    } 
    car->r.x = carPosition.x;
    car->r.y = carPosition.y;

    // Draw the car at the calculated position with specified rotation
}

void MoveCar(Car *car, Player player, int side, int *FS){
    if(car->r.y>player.r.y+600){
        car->outOfScreen = true;
        UnloadTexture(car->t);
        Score += 1;
        car->r.y = -9999999;
    }
    if(side == 1){
        car->r.height = car->t.width*3;
        car->r.width = car->t.height*3;
        if(car->r.x >-60){
            car->r.x -= car->vel;
        }
        else{
            car->outOfScreen = true;
            UnloadTexture(car->t);
        }
    }else if(side == 0){
        car->r.height = car->t.width*3;
        car->r.width = car->t.height*3;
        if(car->r.x < 1050){
            car->r.x += car->vel;
        }
        else {
            car->outOfScreen = true;
            UnloadTexture(car->t);
        }
    }
}