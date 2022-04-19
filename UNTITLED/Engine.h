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

class Ball_Pile: public Driver {
public:

    virtual void Initialization();
    virtual void Finalization();
    virtual void Next_Step(double max_speed);
    virtual double Get_Speed();

    Ball Balls[Config::Max_Ball_Count];
    void Draw(HDC hdc, RECT& paint_area);
    void Release_Balls(double platform_pos);
    bool If_Balls_Lost();
        
};

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
    void Next_Driver_Step();

    int active_balls, fallen_balls;

    EGame_State Game_State;
private:
    //Ball Ball;
    Level Level;
    Platform Platform;
    Border Border;
    Ball_Pile Ball_Pile;
    
    Driver* Object_Driver[Config::Max_Driver_Count];
};