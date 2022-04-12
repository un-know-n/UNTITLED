#pragma once

//#include "Config.h"
#include "Ball.h"

enum EPlatform_State{
    PS_None,
    PS_Normal,
    PS_EndGame,
    PS_StartGame,
    PS_Extension,
    PS_Ready
};

class Platform: public Main_Hit_Checker{
public:
    ~Platform();
    Platform();

    Color Ellipse_Platform_Pen_Color, Rectangle_Platform_Pen_Color;

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
    int Height;
    int EndGame_Elem_Position[Default_Width * Config::Extent];

    const int Platform_Normal_Width, Platform_Normal_Height;
    int* Platform_Scan;

    virtual bool Check_Colision(double next_x_pos, double next_y_pos, Ball* ball);
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
    bool Get_Platform_Column_Color(int x, int y, HPEN& color_pen, int& column_length);
};