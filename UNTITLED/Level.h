#pragma once

#include "Config.h"
#include "Fade.h"

enum ELetter_Type {
    ELT_None,
    ELT_Circle
};

class CLevel{
public:
    CLevel();

    HBRUSH Green_Brush, Blue_Brush, Red_Brush, Yellow_Brush;
    HPEN Green_Pen, Blue_Pen, Red_Pen, Yellow_Pen;
    RECT Level_Area;

    CFade_Brick Fade;

    void Init();
    void Check_Ball_Colision(double &next_y_pos, double &ball_direction);
    void Draw(HWND hwnd, HDC hdc, RECT &paint_area);
    void Change_BG_Color(EBrick_Type type, HPEN &front_pen, HBRUSH &front_brush, HPEN &back_pen, HBRUSH &back_brush);

private:
    void Draw_Brick(HDC hdc, int x, int y, EBrick_Type type);
    void Draw_Brick_Animation(HDC hdc, EBrick_Type type, ELetter_Type letter_type, int x, int y, int step);
    //static char Level_01[CsConfig::Level_X_Elems][CsConfig::Level_Y_Elems];

};