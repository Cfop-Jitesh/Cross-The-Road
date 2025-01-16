/**********************************************************************************************
 *
 *   raylib - Advance Game template
 *
 *   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
 *
 *   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
 *
 *   This software is provided "as-is", without any express or implied warranty. In no event
 *   will the authors be held liable for any damages arising from the use of this software.
 *
 *   Permission is granted to anyone to use this software for any purpose, including commercial
 *   applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 *     1. The origin of this software must not be misrepresented; you must not claim that you
 *     wrote the original software. If you use this software in a product, an acknowledgment
 *     in the product documentation would be appreciated but is not required.
 *
 *     2. Altered source versions must be plainly marked as such, and must not be misrepresented
 *     as being the original software.
 *
 *     3. This notice may not be removed or altered from any source distribution.
 *
 **********************************************************************************************/

#include "raylib.h"
#include "screens.h"
#include "function.h"
#include "stdio.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

Player player;
Texture2D playerTexture;
Texture2D Road;
float rotation;
Vector2 bg1 = {0, 0};
Vector2 bg2 = {0, -540};
int Score =-2;
//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------
Camera2D camera = {0};
Car car[4];
int c = 0;
int side[4];
// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    player.r.width = 16 * 5;
    player.r.height = 13 * 5;
    player.dirc = 1;
    player.vel = 5;
    player.r.x = (GetScreenWidth() / 2) -player.r.width;
    player.r.y = (GetScreenHeight() / 2) - (2*player.r.width);
    playerTexture = LoadTexture("res/player.png");
    Road = LoadTexture("res/road.png");
    camera.target = (Vector2){camera.target.x, player.r.y + player.r.height / 2};
    camera.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f}; // Centered on screen
    camera.rotation = 0.0f;
    camera.zoom = 1;
    car[0].outOfScreen = true;
    car[0].r.width = 21*3;
    car[0].r.height = 32*3;
    car[0].r.x = 0;
    car[0].r.y = 0;
    car[0].t = LoadTexture("res/Car.png");
    car[0].rotation = 0.0f;
    car[1].outOfScreen = true;
    car[1].r.width = 21*3;
    car[1].r.height = 32*3;
    car[1].r.x = 0;
    car[1].r.y = 0;
    car[1].t = LoadTexture("res/RedCar.png");
    car[1].rotation = 0.0f;
    car[2].outOfScreen = true;
    car[2].r.width = 21*3;
    car[2].r.height = 32*3;
    car[2].r.x = 0;
    car[2].r.y = 0;
    car[2].t = LoadTexture("res/GreenCar.png");
    car[2].rotation = 0.0f;
    car[3].outOfScreen = true;
    car[3].r.width = 21*3;
    car[3].r.height = 32*3;
    car[3].r.x = 0;
    car[3].r.y = 0;
    car[3].t = LoadTexture("res/RedCar.png");
    car[3].rotation = 0.0f;
    Score = 0;
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // Update player movement
    Movement(&player);
    rotation = GetRotation(&player);

    // Update background positions
    bgResend(&bg1.y, &bg2.y, Road.height, player);

    // Keep the camera fixed on x-axis and follow player on y-axis
    camera.target.x = GetScreenWidth() / 2.0f;          // Fixed x-axis position (screen center)
    camera.target.y = player.r.y + player.r.height / 2; // Follow player on y-axis
}
int lane;
// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    // Draw backgrounds

    BeginMode2D(camera);

    // Draw player
    DrawTextureEx(Road,(Vector2){bg1.x+Road.width-40,bg1.y+2}, 0, 1, WHITE);
    DrawTextureEx(Road, (Vector2){bg2.x+Road.width-40,bg2.y+2}, 0, 1, WHITE);
    DrawTextureEx(Road, bg1, 0, 1, WHITE);
    DrawTextureEx(Road, bg2, 0, 1, WHITE);
    if(player.dirc == 1){
        DrawTextureEx(playerTexture, (Vector2){player.r.x+(playerTexture.width*5), player.r.y+(playerTexture.height*5)}, rotation, 5, WHITE);
    }
    if(player.dirc == 3){
        DrawTextureEx(playerTexture, (Vector2){player.r.x+(playerTexture.width*5), player.r.y}, rotation, 5, WHITE);
    }
    if(player.dirc == 4){
        DrawTextureEx(playerTexture, (Vector2){player.r.x, player.r.y+(playerTexture.height*5)}, rotation, 5, WHITE);
    }

    for(int i = 0;i < 4; i++){
        if (!car[i].outOfScreen) {
            car[i].vel=12;
            // Draw the car at its current position
            if(side[i]==0){
                DrawTextureEx(car[i].t, (Vector2){car[i].r.x+(car[i].t.width*3.7f), car[i].r.y}, car[i].rotation, 3.0f, WHITE);
            }else {
                DrawTextureEx(car[i].t, (Vector2){car[i].r.x, car[i].r.y+(car[i].t.height*2.0f)}, car[i].rotation, 3.0f, WHITE);
            }
            MoveCar(&car[i],player,side[i], &finishScreen);
            if(CheckCollisionRecs(player.r,car[i].r)){
                finishScreen = 1; // GAMEPLAY
                PlaySound(fxCoin);
            }
        }
        if(car[i].outOfScreen){
            side[i]= GetRandomValue(0,1);
            if(i%2==0){
                lane = 1;
            }
            else {
                lane = 0;
            }
            int setTexture = GetRandomValue(1,3);
            if(setTexture==1){
                car[i].t = LoadTexture("res/Car.png");
            }else if(setTexture==2){
                car[i].t = LoadTexture("res/RedCar.png");
            }else{
                car[i].t = LoadTexture("res/GreenCar.png");
            }
            if(i<2){
                spawnCar(&car[i], bg1, side[i],lane);
            }
            else{
                spawnCar(&car[i], bg2, side[i],lane);
            }
            car[i].outOfScreen = false;
        }
    }

    EndMode2D();

    EndDrawing();
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
    UnloadTexture(playerTexture);
    UnloadTexture(Road);
    for(int i=0;i<4;i++){
        UnloadTexture(car[i].t);
    }
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    if(finishScreen==1){
        framesCounter = 0;
        player.r.width = 16 * 5;
        player.r.height = 13 * 5;
        player.dirc = 1;
        player.vel = 5;
        player.r.x = (GetScreenWidth() / 2) -player.r.width;
        player.r.y = (GetScreenHeight() / 2) - (2*player.r.width);
        playerTexture = LoadTexture("res/player.png");
        Road = LoadTexture("res/road.png");
        camera.target = (Vector2){camera.target.x, player.r.y + player.r.height / 2};
        camera.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f}; // Centered on screen
        camera.rotation = 0.0f;
        camera.zoom = 1;
        car[0].outOfScreen = true;
        car[0].r.width = 21*3;
        car[0].r.height = 32*3;
        car[0].r.x = 0;
        car[0].r.y = 0;
        car[0].t = LoadTexture("res/Car.png");
        car[0].rotation = 0.0f;
        car[1].outOfScreen = true;
        car[1].r.width = 21*3;
        car[1].r.height = 32*3;
        car[1].r.x = 0;
        car[1].r.y = 0;
        car[1].t = LoadTexture("res/RedCar.png");
        car[1].rotation = 0.0f;
        car[2].outOfScreen = true;
        car[2].r.width = 21*3;
        car[2].r.height = 32*3;
        car[2].r.x = 0;
        car[2].r.y = 0;
        car[2].t = LoadTexture("res/GreenCar.png");
        car[2].rotation = 0.0f;
        car[3].outOfScreen = true;
        car[3].r.width = 21*3;
        car[3].r.height = 32*3;
        car[3].r.x = 0;
        car[3].r.y = 0;
        car[3].t = LoadTexture("res/RedCar.png");
        car[3].rotation = 0.0f;
        bg1.x = 0;
        bg1.y =0;
        bg2.x =0;
        bg2.y = -540;
    }
    return finishScreen;
}