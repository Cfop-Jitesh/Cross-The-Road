#include "function.h"
#include "raylib.h"

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

float GetRotation(Player player){
    if(player.dirc == 1){
        return 180.0f;
    }
    if(player.dirc == 2){
        return 0.0f;
    }
    if(player.dirc == 3){
        return 90.0f;
    }
    if(player.dirc == 4){
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

