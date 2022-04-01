#pragma once

#include "Config.h"
#include "Level.h"

enum EBall_State {
    EBS_None,
    EBS_Start,
    EBS_Free
};

class CBall {
public:
    CBall();

    double Ball_Speed;
    double Ball_Direction;

    int X_Pos;
    int Y_Pos;

    RECT Ball_Rect, Prev_Ball_Rect;
    HPEN Ball_Pen;
    HBRUSH Ball_Brush;
    EBall_State Ball_State;

    void Init();
    void Draw(HDC hdc, RECT &paint_area);
    void Move(CLevel *level, int x_pos, int width);
    void Redraw();
    EBall_State Get_State();
    void Set_State(EBall_State state, int x_pos);
};