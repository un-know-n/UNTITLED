
#include "Engine.h"

/////////////////////////////////////////////////////////////////////

//          CSENGINE

HeadEngine::HeadEngine() : Game_State(GS_Play)
{//Constructor
}

void HeadEngine::Init_Engine(HWND hwnd) {
    //It initializes game engine

    Config::Hwnd = hwnd;

    Config::Setup_Colors();

    Fade_Block::Set_Color();

    Level.Init();
    Border.Init();
    Platform.Init();
    Ball.Init();
    
    Ball::Add_Hit_Checker(&Border);
    Ball::Add_Hit_Checker(&Level);
    Ball::Add_Hit_Checker(&Platform);

    Ball.Set_State(BS_Start, Platform.X_Position + Platform.Width / 2);
    Platform.Set_State(EPS_StartGame);
    Platform.Redraw();
    
    SetTimer(Config::Hwnd, Timer_ID, 1000 / Config::FPS, 0);
}

void HeadEngine::Draw_Frame(HDC hdc, RECT &paint_area) {
    //It draws game screen (hdc - handle to device context)

    RECT destination_rect;

    Level.Draw(hdc, paint_area);
    /*for (int i = 0; i < 16; i++) {
    Draw_Brick_Animation(hdc, BT_Blue, BNT_Circle, 20 + i * (Block_Width + 1) * Extent, 100, i);
    Draw_Brick_Animation(hdc, BT_Yellow, BNT_Circle, 20 + i * (Block_Width + 1) * Extent, 140, i);
    Draw_Brick_Animation(hdc, BT_Green, BNT_Circle, 20 + i * (Block_Width + 1) * Extent, 180, i);
    Draw_Brick_Animation(hdc, BT_Red, BNT_Circle, 20 + i * (Block_Width + 1) * Extent, 220, i);
    }*/
    
    Ball.Draw(hdc, paint_area);
    Border.Draw(hdc, paint_area);
    Platform.Draw(hdc, paint_area);
}

int HeadEngine::On_Key_Down(EKey_Type key_type, int button, HWND hwnd) {
    //Check what type of key is currently pressed
    switch (key_type) {
    case KT_Left:
        Platform.X_Position -= Platform.Platform_Step;
        Platform.Condition();
        Platform.Redraw();
        break;
    case KT_Right:
        Platform.X_Position += Platform.Platform_Step;
        Platform.Condition();
        Platform.Redraw();
        break;
    case KT_Space:
        if (Platform.Get_State() == EPS_Ready) {
            Ball.Set_State(BS_Free, Platform.X_Position + Platform.Width / 2 + Platform.Width / 4);
            Platform.Set_State(EPS_Normal);
        }
        break;
    case KT_Escape:
        DestroyWindow(hwnd);
        break;
    }
    switch (button) {
    case Button_A:
        Platform.X_Position -= Platform.Platform_Step;
        Platform.Condition();
        Platform.Redraw();
        break;
    case Button_D:
        Platform.X_Position += Platform.Platform_Step;
        Platform.Condition();
        Platform.Redraw();
        break;
    }
    return 0;
}

int HeadEngine::On_Timer() {
    //Timer that is used to do the actions in time we ask to
    ++Config::Tick;

    switch (Game_State) {
    case GS_Test:
        Ball.Set_Test();
        Platform.Set_State(EPS_None);
        Game_State = GS_Play;
        break;

    case GS_Play:
        Ball.Move();
        if (Ball.Get_State() == BS_None) {
            Game_State = GS_GameOver;
            Platform.Set_State(EPS_EndGame);
        } 
        if(Ball.Is_Test_Finished()){
            Game_State = GS_Test;
        }
        break;

    case GS_GameOver:
        if (Platform.Get_State() == EPS_None) {
            Game_State = GS_Restart;
            Platform.Set_State(EPS_StartGame);
        }
        break;

    case GS_Restart:
        if (Platform.Get_State() == EPS_Ready) {
            Ball.Set_State(BS_Start, Platform.X_Position + Platform.Width - Platform.Width / 4);
            Ball.Ball_Speed = 0.0;
            Game_State = GS_Play;
        }
        
        break;

    }
    Platform.Act();
    Level.Act();

    return 0;
}

/////////////////////////////////////////////////////////////////////