#pragma once

#include "Config.h"
#include "Border.h"
#include "Platform.h"
#include "Level.h"


enum EKey_Type {
    KT_None,
    KT_Left,
    KT_Right,
    KT_Space,
    KT_Escape
};

enum EGame_State {
    GS_Test,
    GS_Play,
    GS_GameOver,
    GS_Restart
};

const int Button_A = 0x41;
const int Button_D = 0x44;
const int Timer_ID = WM_USER + 1;

class HeadEngine {
public:
    HeadEngine();

    void Init_Engine(HWND hwnd);
    void Draw_Frame(HDC hdc, RECT &paint_area);
    int On_Key(EKey_Type key_type, int button, HWND hwnd, bool is_key_down);
    int On_Timer();
    void Act();
    void On_Falling_Bonus(Bonus *falling_bonus);
    void Play_Level();

    int active_balls, fallen_balls;

    EGame_State Game_State;
private:
    //Ball Ball;
    Level Level;
    Platform Platform;
    Border Border;

    Ball Balls[Config::Max_Ball_Count];
};