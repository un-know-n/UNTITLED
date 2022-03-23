
#include "Platform.h"


//          CSPLATFORM

CsPlatform::CsPlatform() : X_Position(0), Width(28), Inner_Platform_Width(21),
Ellipse_Platform_Brush(0), Ellipse_Platform_Pen(0), 
Platform_Rect{}
{//Constructor
}

void CsPlatform::Init(){
    CsConfig::Create_PenNBrush(255, 255, 255, Ellipse_Platform_Pen, Ellipse_Platform_Brush);
    CsConfig::Create_PenNBrush(81, 82, 81, Rectangle_Platform_Pen, Rectangle_Platform_Brush);
}

void CsPlatform::Redraw(HWND hwnd) {
    Prev_Platform_Rect = Platform_Rect;

    Platform_Rect.left = (CsConfig::Level_X_Offset + X_Position) * CsConfig::Extent;
    Platform_Rect.top = CsConfig::Platform_Y_Position * CsConfig::Extent;
    Platform_Rect.right = Platform_Rect.left + Width * CsConfig::Extent;
    Platform_Rect.bottom = Platform_Rect.top + CsConfig::Platform_Height * CsConfig::Extent;

    InvalidateRect(hwnd, &Prev_Platform_Rect, FALSE);
    InvalidateRect(hwnd, &Platform_Rect, FALSE);
}

void CsPlatform::Draw(HDC hdc, int x, int y, HPEN bg_pen, HBRUSH bg_brush, int inner_pl_width, RECT &paint_area) {//It draws platform
    RECT destination_rect;

    if(!(IntersectRect(&destination_rect, &paint_area, &Platform_Rect))) return;

    SelectObject(hdc, bg_pen);
    SelectObject(hdc, bg_brush);

    Rectangle(hdc, Prev_Platform_Rect.left, Prev_Platform_Rect.top, Prev_Platform_Rect.right, Prev_Platform_Rect.bottom);

    SelectObject(hdc, Ellipse_Platform_Pen);
    SelectObject(hdc, Ellipse_Platform_Brush);

    Ellipse(hdc, (x+1) * CsConfig::Extent, (y+1) * CsConfig::Extent,
        (x + 1 + CsConfig::Circle_Size) * CsConfig::Extent, (y + 1 + CsConfig::Circle_Size) * CsConfig::Extent);
    Ellipse(hdc, (x + 1 + inner_pl_width) * CsConfig::Extent, (y+1) * CsConfig::Extent,
        (x + 1 + CsConfig::Circle_Size + inner_pl_width) * CsConfig::Extent, (y + 1 + CsConfig::Circle_Size) * CsConfig::Extent);

    /*SelectObject(hdc, Arc_Pen);

    Arc(hdc, (x + 1) * CsConfig::Extent, (y + 1) * CsConfig::Extent,
    (x + Circle_Size - 1) * CsConfig::Extent, (y + Circle_Size - 1) * CsConfig::Extent,
    (x + 2) * CsConfig::Extent, (y + 1) * CsConfig::Extent,
    (x + 1) * CsConfig::Extent, (y + 3) * CsConfig::Extent);*/

    SelectObject(hdc, Rectangle_Platform_Pen);
    SelectObject(hdc, Rectangle_Platform_Brush);

    RoundRect(hdc, (x + 4) * CsConfig::Extent, (y + 1) * CsConfig::Extent,
        (x + inner_pl_width + 3) * CsConfig::Extent,
        (y + 6) * CsConfig::Extent, 3, 3);
}

void CsPlatform::Condition() {
    if (X_Position < CsConfig::Min_X-2)
        X_Position = CsConfig::Min_X-2;
    if (X_Position > CsConfig::Max_X+1)
        X_Position = CsConfig::Max_X+1;
}

/////////////////////////////////////////////////////////////////////
