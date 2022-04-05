#pragma once

#include <Windows.h>
#include "Ball.h"

class CsBorder: public Hit_Checker{
public:
    CsBorder();
    

    HPEN Arc_Pen, Border_Main_Pen, Border_White_Pen;
    HBRUSH Border_Main_Brush, Border_White_Brush;

    virtual bool Check_Colision(double next_x_pos, double next_y_pos, CBall* ball);
    void Init();
    void Draw(HDC hdc, RECT &paint_area);
   
private:
    void Draw_Element(HDC hdc, int x, int y, BOOL is_vertical);
};
