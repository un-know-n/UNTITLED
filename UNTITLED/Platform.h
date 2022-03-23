#pragma once

#include "Config.h"

class CsPlatform{
public:
    CsPlatform();

    RECT Platform_Rect, Prev_Platform_Rect;
    HPEN Ellipse_Platform_Pen, Rectangle_Platform_Pen;
    HBRUSH Ellipse_Platform_Brush, Rectangle_Platform_Brush;

    int X_Position;
    int Width;
    int Inner_Platform_Width;

    void Init();
    void Redraw(HWND hwnd);
    void Draw(HDC hdc, int x, int y, HPEN bg_pen, HBRUSH bg_brush, int inner_pl_width, RECT &paint_area);
    void Condition();
};