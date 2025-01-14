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
//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------
Camera2D camera = {0};

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    player.r.width = 16 * 5;
    player.r.height = 13 * 5;
    player.dirc = 1;
    player.vel = 3;
    player.r.x = (GetScreenWidth() / 2) - player.r.width;
    player.r.y = (GetScreenHeight() / 2) - player.r.width;
    playerTexture = LoadTexture("res/player.png");
    Road = LoadTexture("res/road.png");
    camera.target = (Vector2){camera.target.x, player.r.y + player.r.height / 2};
    camera.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f}; // Centered on screen
    camera.rotation = 0.0f;
    camera.zoom = 1.5f;
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    if (IsKeyPressed(KEY_F11))
    {
        ToggleFullscreen();
    }

    // Update player movement
    Movement(&player);
    rotation = GetRotation(player);

    // Update background positions
    bgResend(&bg1.y, &bg2.y, Road.height, player);

    // Keep the camera fixed on x-axis and follow player on y-axis
    camera.target.x = GetScreenWidth() / 2.0f;          // Fixed x-axis position (screen center)
    camera.target.y = player.r.y + player.r.height / 2; // Follow player on y-axis
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    // Draw backgrounds

    BeginMode2D(camera);

    // Draw player
    DrawTextureEx(Road, bg1, 0, 1, WHITE);
    DrawTextureEx(Road, bg2, 0, 1, WHITE);
    DrawTextureEx(playerTexture, (Vector2){player.r.x, player.r.y}, rotation, 5, WHITE);

    EndMode2D();

    EndDrawing();
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
    UnloadTexture(playerTexture);
    UnloadTexture(Road);
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}