#pragma once

#include "Config.h"

enum EPlatform_State{
    EPS_None,
    EPS_Normal,
    EPS_Animation,
    EPS_Start
};

class CsPlatform{
public:
    CsPlatform();

    RECT Platform_Rect, Prev_Platform_Rect;
    HPEN Ellipse_Platform_Pen, Rectangle_Platform_Pen;
    HBRUSH Ellipse_Platform_Brush, Rectangle_Platform_Brush;

    EPlatform_State Platform_State;

    int Y_Position;
    int X_Position;
    int Width;
    int Inner_Platform_Width;
    int Anim_Position;

    double Rolling_Step;

    static const int Normal_Width = 28;

    void Init();
    void Redraw(HWND hwnd);
    void Draw(HDC hdc, RECT &paint_area);
    void Draw_Normal(HDC hdc, RECT &paint_area);
    void Draw_Animation(HDC hdc, RECT &paint_area);
    void Draw_Start(HDC hdc, RECT &paint_area);
    EPlatform_State Get_State();
    void Set_State(EPlatform_State platform_state);
    void Act(HWND hwnd);
    void Condition();
    void Clear_BG(HDC hdc);
};