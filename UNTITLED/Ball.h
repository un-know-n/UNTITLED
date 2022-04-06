#pragma once

#include "Config.h"

enum EBall_State {
    EBS_Test,
    EBS_None,
    EBS_Start,
    EBS_Free
};

class CBall;

class Hit_Checker {
public:
    virtual bool Check_Colision(double next_x_pos, double next_y_pos, CBall* ball) = 0;
};

class CBall {
public:
    CBall();

    double Ball_Speed;
    static const double Radius;
    static const double Start_Y_Pos;
    double Central_X;
    double Central_Y;
    double Rest_Size;
    static int Hit_Counter;
    double Rest_Test_Size;
    int Move_Pos;
    bool Test_Active;

    static Hit_Checker *Hit_Check[3];
    RECT Ball_Rect, Prev_Ball_Rect;
    HPEN Ball_Pen;
    HBRUSH Ball_Brush;
    EBall_State Ball_State;

    void Init();
    void Draw(HDC hdc, RECT &paint_area);
    void Move();
    void Redraw();
    EBall_State Get_State();
    void Set_State(EBall_State state, int x_pos);
    double Get_Direction();
    void Set_Direction(double new_direction);
    void Reflect(bool is_vertical);
    static void Add_Hit_Checker(Hit_Checker* hit_check);
    void Set_Test();
    bool Is_Test_Finished();

private:
    double Ball_Direction;
};