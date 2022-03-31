
#include "Engine.h"

/////////////////////////////////////////////////////////////////////

//          CSENGINE

CsEngine::CsEngine() 
{//Constructor
}



void CsEngine::Init_Engine(HWND hwnd) {//It initializes game engine

    CsConfig::Hwnd = hwnd;
    //Arc_Pen = CreatePen(PS_SOLID, 0, RGB(81, 82, 81));

    CsConfig::Setup_Colors();

    CFade_Brick::Set_Color();

    Level.Init();
    Ball.Init();
    Platform.Init();
    Border.Init();

    Platform.Set_State(EPS_StartGame);
    Platform.Redraw();

    SetTimer(CsConfig::Hwnd, Timer_ID, 1000 / CsConfig::FPS, 0);
}

void CsEngine::Draw_Frame(HDC hdc, RECT &paint_area) {//It draws game screen(hdc - handle to device context)

    RECT destination_rect;

    Level.Draw(CsConfig::Hwnd, hdc, paint_area);
    /*for (int i = 0; i < 16; i++) {
    Draw_Brick_Animation(hdc, EBT_Blue, ELT_Circle, 20 + i * (Brick_Width + 1) * Extent, 100, i);
    Draw_Brick_Animation(hdc, EBT_Yellow, ELT_Circle, 20 + i * (Brick_Width + 1) * Extent, 140, i);
    Draw_Brick_Animation(hdc, EBT_Green, ELT_Circle, 20 + i * (Brick_Width + 1) * Extent, 180, i);
    Draw_Brick_Animation(hdc, EBT_Red, ELT_Circle, 20 + i * (Brick_Width + 1) * Extent, 220, i);
    }*/
    Ball.Draw(hdc, paint_area);
    Border.Draw(hdc, paint_area);
    Platform.Draw(hdc, paint_area);
}

int CsEngine::On_Key_Down(EKey_Type key_type, int button) {
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
        //Throw_Ball();
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

int CsEngine::On_Timer() {

    ++CsConfig::Tick;

    Ball.Move(CsConfig::Hwnd, &Level, Platform.X_Position, Platform.Width);

    //Level.Fade.Act(Hwnd);

    //if(CsConfig::Tick % 2 == 0) 
        Platform.Act();

    return 0;
}

/////////////////////////////////////////////////////////////////////