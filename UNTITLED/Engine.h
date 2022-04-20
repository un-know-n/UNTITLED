#pragma once

#include "Config.h"
#include "Border.h"
#include "Platform.h"
#include "Level.h"
#include "Ball_Pile.h"


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

class Head_Engine {
public:
    Head_Engine();

    void Init_Engine(HWND hwnd);
    void Draw_Frame(HDC hdc, RECT &paint_area);
    void Act();
    void On_Falling_Bonus(Bonus *falling_bonus);
    void Play_Level();
    void Next_Driver_Step();

    int On_Key(EKey_Type key_type, int button, HWND hwnd, bool is_key_down);
    int On_Timer();

    int Life_Counter;

    EGame_State Game_State;
private:
    
    Level Level;
    Platform Platform;
    Border Border;
    Ball_Pile Ball_Pile;
    
    Driver* Object_Driver[Config::Max_Driver_Count];
};