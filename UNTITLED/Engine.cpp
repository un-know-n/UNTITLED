
#include "Engine.h"

/////////////////////////////////////////////////////////////////////

//          CSENGINE

CsEngine::CsEngine() : Platform_Step(6), Hwnd(0)
{//Constructor
}



void CsEngine::Init_Engine(HWND hwnd) {//It initializes game engine

    Hwnd = hwnd;
    //Arc_Pen = CreatePen(PS_SOLID, 0, RGB(81, 82, 81));

    CsConfig::Setup_Colors();

    CFade_Brick::Set_Color();

    Level.Init();
    Ball.Init();
    Platform.Init();
    Border.Init();

    Platform.Redraw(Hwnd);

    SetTimer(Hwnd, Timer_ID, 1000 / CsConfig::FPS, 0);
}

void CsEngine::Draw_Frame(HDC hdc, RECT &paint_area) {//It draws game screen(hdc - handle to device context)

    RECT destination_rect;

    Level.Draw(Hwnd, hdc, paint_area);
    
    Platform.Draw(hdc, CsConfig::Level_X_Offset + Platform.X_Position, CsConfig::Platform_Y_Position, Platform.Inner_Platform_Width, paint_area);

    /*for (int i = 0; i < 16; i++) {
    Draw_Brick_Animation(hdc, EBT_Blue, ELT_Circle, 20 + i * (Brick_Width + 1) * Extent, 100, i);
    Draw_Brick_Animation(hdc, EBT_Yellow, ELT_Circle, 20 + i * (Brick_Width + 1) * Extent, 140, i);
    Draw_Brick_Animation(hdc, EBT_Green, ELT_Circle, 20 + i * (Brick_Width + 1) * Extent, 180, i);
    Draw_Brick_Animation(hdc, EBT_Red, ELT_Circle, 20 + i * (Brick_Width + 1) * Extent, 220, i);
    }*/
    Ball.Draw(hdc, paint_area);

    Border.Draw(hdc, paint_area);
}

int CsEngine::On_Key_Down(EKey_Type key_type, int button) {
    switch (key_type) {
    case EKT_Left:
        Platform.X_Position -= Platform_Step;
        Platform.Condition();
        Platform.Redraw(Hwnd);
        break;
    case EKT_Right:
        Platform.X_Position += Platform_Step;
        Platform.Condition();
        Platform.Redraw(Hwnd);
        break;
    case EKT_Space:
        //Throw_Ball();
        break;
    }
    switch (button) {
    case Button_A:
        Platform.X_Position -= Platform_Step;
        Platform.Condition();
        Platform.Redraw(Hwnd);
        break;
    case Button_D:
        Platform.X_Position += Platform_Step;
        Platform.Condition();
        Platform.Redraw(Hwnd);
        break;
    }
    return 0;
}

int CsEngine::On_Timer() {
    Ball.Move(Hwnd, &Level, Platform.X_Position, Platform.Width);
    Level.Fade.Act(Hwnd);
    return 0;
}

/////////////////////////////////////////////////////////////////////