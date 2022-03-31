#pragma once

#include "Config.h"
#include "Level.h"

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

    void Init();
    void Draw(HDC hdc, RECT &paint_area);
    void Move(HWND hwnd, CLevel *level, int x_pos, int width);
};