#pragma once

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

};