#pragma once

#include "Config.h"
#include "Level.h"

enum EBall_State{
    EBS_None,
    EBS_Start,
    EBS_Normal
};

class CBall {
public:
    CBall();

    double Ball_Speed;
    double Ball_Direction;

    double X_Pos;
    double Y_Pos;

    RECT Ball_Rect, Prev_Ball_Rect;
    HPEN Ball_Pen;
    HBRUSH Ball_Brush;
    EBall_State Ball_State;

    void Init(int x_pos);
    void Draw(HDC hdc, RECT &paint_area);
    void Move(HWND hwnd, CLevel *level, int x_pos, int width);
};