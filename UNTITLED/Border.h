#pragma once

#include <Windows.h>
#include "Ball.h"

class Border: public Main_Hit_Checker, public Object_Designer{
public:
    Border();
    
    virtual bool Check_Colision(double next_x_pos, double next_y_pos, Ball* ball);

    virtual void Draw(HDC hdc, RECT& paint_area);
    virtual void Animate();
    virtual bool Is_Finished();

    void Init();
    //void Draw(HDC hdc, RECT& paint_area);
    void Redraw_Floor();

    HPEN Border_Main_Pen, Border_White_Pen;
    HBRUSH Border_Main_Brush, Border_White_Brush;

    RECT Floor_Rect;

private:
    void Draw_Element(HDC hdc, int x, int y, BOOL is_vertical);
    void Draw_Floor(HDC hdc, int x, int y);
};
