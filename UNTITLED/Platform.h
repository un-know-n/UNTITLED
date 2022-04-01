#pragma once

#include "Config.h"

enum EPlatform_State{
    EPS_None,
    EPS_Normal,
    EPS_EndGame,
    EPS_StartGame,
    EPS_Extension,
    EPS_Ready
};

class CsPlatform{
public:
    CsPlatform();

    RECT Platform_Rect, Prev_Platform_Rect;
    HPEN Ellipse_Platform_Pen, Rectangle_Platform_Pen;
    HBRUSH Ellipse_Platform_Brush, Rectangle_Platform_Brush;

    EPlatform_State Platform_State;

    static const int Default_Width = 28;
    static const int Max_Rotation = 36;

    int Platform_Step;
    int X_Position;
    int Y_Position;
    int Step_Up;
    int Inner_Platform_Width;
    int Width;
//  int EndGame_Position;
    int EndGame_Elem_Position[Default_Width * CsConfig::Extent];

    void Init();
    void Redraw();
    void Draw(HDC hdc, RECT &paint_area);
    void Draw_Normal(HDC hdc, RECT &paint_area);
    void Draw_EndGame(HDC hdc, RECT &paint_area);
    void Draw_StartGame(HDC hdc, RECT& paint_area);
    void Draw_Extension(HDC hdc, RECT& paint_area);
    EPlatform_State Get_State();
    void Set_State(EPlatform_State platform_state);
    void Clear_BG(HDC hdc);
    void Act();
    void Condition();
};