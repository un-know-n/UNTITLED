
#include "Engine.h"

/////////////////////////////////////////////////////////////////////

//          CSENGINE

HeadEngine::HeadEngine() : Game_State(EGS_Play)
{//Constructor6
}

void HeadEngine::Init_Engine(HWND hwnd) {//It initializes game engine

    Config::Hwnd = hwnd;
    //Arc_Pen = CreatePen(PS_SOLID, 0, RGB(81, 82, 81));

    Config::Setup_Colors();

    Fade_Brick::Set_Color();

    Level.Init();
    Border.Init();
    Platform.Init();
    Ball.Init();
    
    Ball::Add_Hit_Checker(&Border);
    Ball::Add_Hit_Checker(&Level);
    Ball::Add_Hit_Checker(&Platform);

    /*Ball::Hit_Check[0] = &Border;
    Ball::Hit_Check[1] = &Level;
    Ball::Hit_Check[2] = &Platform;*/

    Ball.Set_State(EBS_Start, Platform.X_Position + Platform.Width / 2);
    Platform.Set_State(EPS_StartGame);
    Platform.Redraw();

    SetTimer(Config::Hwnd, Timer_ID, 1000 / Config::FPS, 0);
}

void HeadEngine::Draw_Frame(HDC hdc, RECT &paint_area) {//It draws game screen(hdc - handle to device context)

    RECT destination_rect;

    Level.Draw(hdc, paint_area);
    /*for (int i = 0; i < 16; i++) {
    Draw_Brick_Animation(hdc, EBT_Blue, ELT_Circle, 20 + i * (Brick_Width + 1) * Extent, 100, i);
    Draw_Brick_Animation(hdc, EBT_Yellow, ELT_Circle, 20 + i * (Brick_Width + 1) * Extent, 140, i);
    Draw_Brick_Animation(hdc, EBT_Green, ELT_Circle, 20 + i * (Brick_Width + 1) * Extent, 180, i);
    Draw_Brick_Animation(hdc, EBT_Red, ELT_Circle, 20 + i * (Brick_Width + 1) * Extent, 220, i);
    }*/
    Ball.Draw(hdc, paint_area);
    Border.Draw(hdc, paint_area);
    Platform.Draw(hdc, paint_area);
    //Sleep(125);
}

int HeadEngine::On_Key_Down(EKey_Type key_type, int button, HWND hwnd) {
    switch (key_type) {
    case EKT_Left:
        Platform.X_Position -= Platform.Platform_Step;
        Platform.Condition();
        Platform.Redraw();
        break;
    case EKT_Right:
        Platform.X_Position += Platform.Platform_Step;
        Platform.Condition();
        Platform.Redraw();
        break;
    case EKT_Space:
        if (Platform.Get_State() == EPS_Ready) {
            Ball.Set_State(EBS_Free, Platform.X_Position + Platform.Width / 2 + Platform.Width / 4);
            Platform.Set_State(EPS_Normal);
        }
        break;
    case EKT_Escape:
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

    ++Config::Tick;

    switch (Game_State) {
    case EGS_Test:
        Ball.Set_Test();
        Platform.Set_State(EPS_None);
        Game_State = EGS_Play;
        break;

    case EGS_Play:
        Ball.Move();
        if (Ball.Get_State() == EBS_None) {
            Game_State = EGS_GameOver;
            Platform.Set_State(EPS_EndGame);
        } 
        if(Ball.Is_Test_Finished()){
            Game_State = EGS_Test;
        }
        break;

    case EGS_GameOver:
        if (Platform.Get_State() == EPS_None) {
            Game_State = EGS_Restart;
            Platform.Set_State(EPS_StartGame);
        }
        break;

    case EGS_Restart:
        if (Platform.Get_State() == EPS_Ready) {
            Ball.Set_State(EBS_Start, Platform.X_Position + Platform.Width - Platform.Width / 4);
            Ball.Ball_Speed = 0.0;
            Game_State = EGS_Play;
            //Platform.Set_State(EPS_Ready);
        }
        
        break;

    }
    Platform.Act();
    Level.Act();

    //if(Config::Tick % 2 == 0) 
    //Platform.Act();
    return 0;
}

/////////////////////////////////////////////////////////////////////