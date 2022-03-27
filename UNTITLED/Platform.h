#pragma once

#include "Config.h"

enum EPlatform_State{
    EPS_None,
    EPS_Normal,
    EPS_Animation
};

class CsPlatform{
public:
    CsPlatform();

    RECT Platform_Rect, Prev_Platform_Rect;
    HPEN Ellipse_Platform_Pen, Rectangle_Platform_Pen;
    HBRUSH Ellipse_Platform_Brush, Rectangle_Platform_Brush;

    EPlatform_State Platform_State;

    int X_Position;
    int Width;
    int Inner_Platform_Width;

    void Init();
    void Redraw(HWND hwnd);
    void Draw(HDC hdc, RECT &paint_area);
    void Draw_Normal(HDC hdc, RECT &paint_area);
    void Draw_Animation(HDC hdc, RECT &paint_area);
    void Act(HWND hwnd);
    void Condition();
};