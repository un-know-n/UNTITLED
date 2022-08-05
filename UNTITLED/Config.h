#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include <Windows.h>

class Color{
public:
    Color(unsigned char r, unsigned char g, unsigned char b);
    int Get_RGB() const;
    unsigned char R, G, B;
};


class Config{
public:
    static const Color BG_Color, Blue_Block, Green_Block, Yellow_Block, Red_Block;

    static HBRUSH Green_Brush, Blue_Brush, Red_Brush, Yellow_Brush;
    static HPEN Green_Pen, Blue_Pen, Red_Pen, Yellow_Pen;

    static HPEN BG_Pen;
    static HBRUSH BG_Brush;
    static HWND Hwnd;

//Main variables
    static const int Extent = 3;
    static const int FPS = 20;
    static int Tick;
    static const int Max_Fading_Count = 50;
    static const int Max_Falling_Count = 50;

//Level
    static const int Block_Width = 15;
    static const int Block_Height = 7;
    static const int Level_X_Elems = 14;
    static const int Level_Y_Elems = 12;
    static const int Level_X_Offset = 8;
    static const int Level_Y_Offset = 6;
    static const int Min_X = 0;
    static const int Max_X = 188 - 3 * Level_X_Offset;//Max_X_Pos -...
    static const int Cell_Width = (Block_Width + 1);
    static const int Cell_Height = (Block_Height + 1);

//Ball
    static const int Ball_Size = 4;
    static const double Step_Size;

//Platform
    static const int Platform_Y_Position = 185;
    static const int Circle_Size = 5;
    static const int Platform_Height = 7;

    static const int Max_X_Pos = Level_X_Offset + Cell_Width * Level_Y_Elems - Ball_Size * Extent;
    static const int Max_Y_Pos = 200;//199

    static void Setup_Colors();
    static void Create_PenNBrush(const Color &color, HPEN &pen, HBRUSH &brush);
    static void Create_PenNBrush(unsigned char r, unsigned char g, unsigned char b, HPEN& pen, HBRUSH& brush);
};