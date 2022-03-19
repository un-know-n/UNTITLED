#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include<Windows.h>

enum EKey_Type {
    EKT_None,
    EKT_Left,
    EKT_Right,
    EKT_Space
};

enum EBrick_Type {
    EBT_None,
    EBT_Green,
    EBT_Blue, 
    EBT_Red,
    EBT_Yellow
};

enum ELetter_Type {
    ELT_None,
    ELT_Circle
};

const int Button_A = 0x41;
const int Button_D = 0x44;
const int Timer_ID = WM_USER + 1;

class CsEngine {
public:
    CsEngine();

    static const int Level_X_Elems = 14;
    static const int Level_Y_Elems = 12;

    void Init_Engine(HWND hwnd);
    void Draw_Frame(HDC hdc, RECT &paint_area);
    int On_Key_Down(EKey_Type key_type, int button);
    int On_Timer();

private:
    void Create_PenNBrush(unsigned char r, unsigned char g, unsigned char b, HPEN& pen, HBRUSH& brush);
    void Redraw_Platform();
    void Draw_Brick(HDC hdc, int x, int y, EBrick_Type type);
    void Change_BG_Color(EBrick_Type type, HPEN& front_pen, HBRUSH& front_brush, HPEN& back_pen, HBRUSH& back_brush);
    void Draw_Brick_Animation(HDC hdc, EBrick_Type type, ELetter_Type letter_type, int x, int y, int step);
    void Draw_Level(HDC hdc);
    void Draw_Platform(HDC hdc, int x, int y);
    void Draw_Ball(HDC hdc, RECT& paint_area);
    void Draw_Border_Element(HDC hdc, int x, int y, BOOL is_vertical);
    void Draw_Border(HDC hdc, RECT& paint_area);
    void Platform_Condition();
    void Check_Ball_Colision(int& next_x_pos, int& next_y_pos);
    void Move_Ball();

    HWND Hwnd;
    HPEN Green_Pen, Blue_Pen, Red_Pen, Yellow_Pen, Ellipse_Platform_Pen, 
        Rectangle_Platform_Pen, Arc_Pen, BG_Pen, Ball_Pen, Border_Main_Pen, Border_White_Pen;
    HBRUSH Green_Brush, Blue_Brush, Red_Brush, Yellow_Brush, Ellipse_Platform_Brush, 
        Rectangle_Platform_Brush, BG_Brush, Ball_Brush, Border_Main_Brush, Border_White_Brush;
    RECT Platform_Rect, Prev_Platform_Rect;
    RECT Level_Area;
    RECT Ball_Rect, Prev_Ball_Rect;

    int Inner_Platform_Width;
    int Platform_X_Position;
    int Platform_Step;
    int Platform_Width;
    int Ball_X_Pos;
    int Ball_Y_Pos;

    double Ball_Speed;
    double Ball_Direction;

    static const int Global_Scale = 3;
    static const int Brick_Width = 15;
    static const int Brick_Height = 7;
    static const int Cell_Width = (Brick_Width + 1);
    static const int Cell_Height = (Brick_Height + 1);
    static const int Level_X_Offset = 8;
    static const int Level_Y_Offset = 6;
    static const int Circle_Size = 7;
    static const int Platform_Y_Position = 185;
    static const int Platform_Height = 7;
    static const int Ball_Size = 4;
    static const int Max_X_Pos = 188;//Level_X_Offset + Cell_Width * Level_X_Elems - Ball_Size;
    static const int Max_Y_Pos = (200 - Platform_Height + Ball_Size);
    static const int Min_Platform_X = 0;
    static const int Max_Platform_X = Max_X_Pos - 3 * Level_X_Offset;
    static const int Border_X_Offset = 6;
    static const int Border_Y_Offset = 4;
};