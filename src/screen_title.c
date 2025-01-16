/**********************************************************************************************
 *
 *   raylib - Advance Game template
 *
 *   Title Screen Functions Definitions (Init, Update, Draw, Unload)
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
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "function.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

// Title Screen Initialization logic
void InitTitleScreen(void)
{
    // TODO: Initialize TITLE screen variables here!
    framesCounter = 0;
    finishScreen = 0;
}

// Title Screen Update logic
void UpdateTitleScreen(void)
{
    // TODO: Update TITLE screen variables here!
    if (IsKeyPressed(KEY_F11))
    {
        ToggleFullscreen();
    }
}

// Title Screen Draw logic
void DrawTitleScreen(void)
{
    DrawText("Cross The Road",GetScreenWidth()/2-(14/2*40)+100,100,40,RED);
    if (GuiButton((Rectangle){GetScreenWidth()/2-50, GetScreenHeight()/2-80,120,40}, "Start"))
    {
        // Button was clicked
        finishScreen = 2; // GAMEPLAY
        Score = 0;
        PlaySound(fxCoin);
    }
    if (GuiButton((Rectangle){GetScreenWidth()/2-50, GetScreenHeight()/2-80+60,120,40}, "Exit"))
    {
        // Button was clicked
        CloseWindow();
        PlaySound(fxCoin);
    }
}

// Title Screen Unload logic
void UnloadTitleScreen(void)
{
    // TODO: Unload TITLE screen variables here!
}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finishScreen;
}