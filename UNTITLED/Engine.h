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


class CLevel;
class CPlatform;
class CsEngine;

class CBall {
public:
    double Ball_Speed;
    double Ball_Direction;

    int Ball_X_Pos;
    int Ball_Y_Pos;

    static const int Ball_Size = 4;

    RECT Ball_Rect, Prev_Ball_Rect;
    HPEN Ball_Pen;
    HBRUSH Ball_Brush;

    CBall();

    void Init_Ball();
    void Draw_Ball(HDC hdc, RECT &paint_area, CsEngine *engine);
    void Move_Ball(CsEngine *engine, CLevel *level, CPlatform *platform);
    
};

class CLevel{
public:
    static const int Brick_Width = 15;
    static const int Brick_Height = 7;
    static const int Level_X_Elems = 14;
    static const int Level_Y_Elems = 12;
    static const int Level_X_Offset = 8;
    static const int Level_Y_Offset = 6;
    static const int Cell_Width = (Brick_Width + 1);
    static const int Cell_Height = (Brick_Height + 1);

    HBRUSH Green_Brush, Blue_Brush, Red_Brush, Yellow_Brush;
    HPEN Green_Pen, Blue_Pen, Red_Pen, Yellow_Pen;
    RECT Level_Area;

    void Init_Level();
    void Check_Ball_Colision(int &next_y_pos, double &ball_direction);
    void Draw_Brick(HDC hdc, int x, int y, EBrick_Type type);
    void Draw_Brick_Animation(HDC hdc, EBrick_Type type, ELetter_Type letter_type, int x, int y, int step, CsEngine *engine);
    void Draw_Level(HDC hdc, RECT &paint_area);
};

class CPlatform{
public:
    CPlatform();
    void Init_Platform();
    void Redraw_Platform(CsEngine *engine);
    void Draw_Platform(HDC hdc, int x, int y, CsEngine *engine, RECT &paint_area);
    void Platform_Condition();

    RECT Platform_Rect, Prev_Platform_Rect;
    HPEN Ellipse_Platform_Pen, Rectangle_Platform_Pen;
    HBRUSH Ellipse_Platform_Brush, Rectangle_Platform_Brush;

    int Platform_X_Position;
    int Platform_Width;

    static const int Platform_Y_Position = 185;
    static const int Circle_Size = 5;
    static const int Platform_Height = 7;
    static const int Min_Platform_X = 0;
    static const int Max_Platform_X = 188 - 3 * CLevel::Level_X_Offset;//Max_X_Pos -...
};

class CsEngine {
public:
    CsEngine();

    static const int Global_Scale = 3;
    static const int Max_X_Pos = CLevel::Level_X_Offset + CLevel::Cell_Width * CLevel::Level_Y_Elems - CBall::Ball_Size * Global_Scale;
    static const int Max_Y_Pos = (195 - CBall::Ball_Size);
    static const int Border_X_Offset = 6;
    static const int Border_Y_Offset = 4;

    HWND Hwnd;
    HPEN BG_Pen;
    HBRUSH BG_Brush;

    int Platform_Step;
    int Inner_Platform_Width;

    void Init_Engine(HWND hwnd);
    void Draw_Frame(HDC hdc, RECT &paint_area);
    int On_Key_Down(EKey_Type key_type, int button);
    int On_Timer();
    void Change_BG_Color(EBrick_Type type, HPEN &front_pen, HBRUSH &front_brush, HPEN &back_pen, HBRUSH &back_brush);
    static void Create_PenNBrush(unsigned char r, unsigned char g, unsigned char b, HPEN &pen, HBRUSH &brush);   
private:
    
    void Draw_Border_Element(HDC hdc, int x, int y, BOOL is_vertical);
    void Draw_Border(HDC hdc, RECT &paint_area);
    
    HPEN Arc_Pen, Border_Main_Pen, Border_White_Pen;
    HBRUSH Border_Main_Brush, Border_White_Brush;

    CBall Ball;
    CLevel Level;
    CPlatform Platform;
    
};