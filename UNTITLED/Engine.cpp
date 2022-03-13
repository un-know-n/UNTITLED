
#include "Engine.h"

//Main variables

enum EBrick_Type {
    EBT_None,
    EBT_Green,
    EBT_Blue, 
    EBT_Red,
    EBT_Yellow
};

HPEN Green_Pen, Blue_Pen, Red_Pen, Yellow_Pen, Ellipse_Platform_Pen, Rectangle_Platform_Pen, Arc_Pen;
HBRUSH Green_Brush, Blue_Brush, Red_Brush, Yellow_Brush, Ellipse_Platform_Brush, Rectangle_Platform_Brush;

const int Global_Scale = 3;
const int Brick_Width = 15;
const int Brick_Height = 7;
const int Cell_Width = (Brick_Width + 1);
const int Cell_Height = (Brick_Height + 1);
const int Level_X_Offset = 8;
const int Level_Y_Offset = 6;
const int Circle_Size = 7;

int Inner_Platform_Width = 21;

char Level_01[14][12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void Create_PenNBrush(unsigned char r, unsigned char g, unsigned char b, HPEN &pen, HBRUSH &brush) {
    pen = CreatePen(PS_SOLID, 0, RGB(r, g, b));
    brush = CreateSolidBrush(RGB(r, g, b));
}

void Init_Art_Items() {//It initializes pens/brushes

    Arc_Pen = CreatePen(PS_SOLID, 0, RGB(81, 82, 81));
    Create_PenNBrush(43, 97, 49, Green_Pen, Green_Brush);
    Create_PenNBrush(43, 63, 97, Blue_Pen, Blue_Brush);
    Create_PenNBrush(97, 43, 43, Red_Pen, Red_Brush);
    Create_PenNBrush(112, 101, 46, Yellow_Pen, Yellow_Brush);
    Create_PenNBrush(255, 255, 255, Ellipse_Platform_Pen, Ellipse_Platform_Brush);
    Create_PenNBrush(81, 82, 81, Rectangle_Platform_Pen, Rectangle_Platform_Brush);
}

void Draw_Brick(HDC hdc, int x, int y, EBrick_Type type) {//It draws game brick

    HPEN pen;
    HBRUSH brush;

    switch (type) {
    case EBT_Green:
        pen = Green_Pen;
        brush = Green_Brush;
        break;
    case EBT_Blue:
        pen = Blue_Pen;
        brush = Blue_Brush;
        break;
    case EBT_Red:
        pen = Red_Pen;
        brush = Red_Brush;
        break;
    case EBT_Yellow:
        pen = Yellow_Pen;
        brush = Yellow_Brush;
        break;
    case EBT_None: return;
    default: return;
    }
    SelectObject(hdc, pen);
    SelectObject(hdc, brush);
    RoundRect(hdc, x * Global_Scale, y * Global_Scale,
        (x + Brick_Width) * Global_Scale,
        (y + Brick_Height) * Global_Scale, 3, 3);
}

void Draw_Level(HDC hdc) {//It draws level map
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 12; j++) {
            Draw_Brick(hdc, Level_X_Offset + j * Cell_Width,
                Level_Y_Offset + i * Cell_Height, (EBrick_Type)Level_01[i][j]);
        }
    }
}

void Draw_Platform(HDC hdc, int x, int y) {//It draws platform

    SelectObject(hdc, Ellipse_Platform_Pen);
    SelectObject(hdc, Ellipse_Platform_Brush);

    Ellipse(hdc, x * Global_Scale, y * Global_Scale,
        (x + Circle_Size) * Global_Scale, (y + Circle_Size) * Global_Scale);
    Ellipse(hdc, (x + Inner_Platform_Width) * Global_Scale, y * Global_Scale,
        (x + Circle_Size + Inner_Platform_Width) * Global_Scale, (y + Circle_Size) * Global_Scale);

    /*SelectObject(hdc, Arc_Pen);

    Arc(hdc, (x + 1) * Global_Scale, (y + 1) * Global_Scale,
        (x + Circle_Size - 1) * Global_Scale, (y + Circle_Size - 1) * Global_Scale,
        (x + 2) * Global_Scale, (y + 1) * Global_Scale,
        (x + 1) * Global_Scale, (y + 3) * Global_Scale);*/

    SelectObject(hdc, Rectangle_Platform_Pen);
    SelectObject(hdc, Rectangle_Platform_Brush);

    RoundRect(hdc, (x + 4) * Global_Scale, (y + 1) * Global_Scale,
        (x + Inner_Platform_Width + 3) * Global_Scale,
        (y + 6) * Global_Scale, 3, 3);
}

void Draw_Frame(HDC hdc) {//It draws game screen(hdc - handle to device context)

    Draw_Level(hdc);

    Draw_Platform(hdc, 50, 100);
}