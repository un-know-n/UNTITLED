#pragma once

#include <Windows.h>

class CsBorder{
public:
    CsBorder();
    

    HPEN Arc_Pen, Border_Main_Pen, Border_White_Pen;
    HBRUSH Border_Main_Brush, Border_White_Brush;

    void Init();
    void Draw(HDC hdc, RECT &paint_area);

private:
    void Draw_Element(HDC hdc, int x, int y, BOOL is_vertical);
};
