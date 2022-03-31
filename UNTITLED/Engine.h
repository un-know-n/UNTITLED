#pragma once

#include "Config.h"
#include "Border.h"
#include "Ball.h"
#include "Platform.h"


enum EKey_Type {
    EKT_None,
    EKT_Left,
    EKT_Right,
    EKT_Space
};

const int Button_A = 0x41;
const int Button_D = 0x44;
const int Timer_ID = WM_USER + 1;

//class CsEngine;
//class CsPlatform;

class CsEngine {
public:
    CsEngine();

    void Init_Engine(HWND hwnd);
    void Draw_Frame(HDC hdc, RECT &paint_area);
    int On_Key_Down(EKey_Type key_type, int button);
    int On_Timer();

private:
    CBall Ball;
    CLevel Level;
    CsPlatform Platform;
    CsBorder Border;
};