#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <Windows.h>

class Color{
public:
    Color(unsigned char r, unsigned char g, unsigned char b);
    int Get_RGB() const;
    unsigned char R, G, B;
};

class Object_Designer {
public:
    virtual void Draw(HDC hdc, RECT& paint_area) = 0;
    virtual void Animate() = 0;
    virtual bool Is_Finished() = 0;
};

class Common{
public:

    static void Setup_Colors();
    static void Create_PenNBrush(const Color& color, HPEN& pen, HBRUSH& brush);
    static void Create_PenNBrush(unsigned char r, unsigned char g, unsigned char b, HPEN& pen, HBRUSH& brush);

    //Main variables
    static const Color BG_Color, Blue_Block, Green_Block, Yellow_Block, Red_Block;

    static HBRUSH Green_Brush, Blue_Brush, Red_Brush, Yellow_Brush;
    static HPEN Green_Pen, Blue_Pen, Red_Pen, Yellow_Pen;

    static HPEN BG_Pen;
    static HBRUSH BG_Brush;
    static HWND Hwnd;

    //static const int Extent = 3;
    static const int FPS = 20;
    static int Tick;
    static int Floor_Tick;
    static const int Max_Fading_Count = 50;
    static const int Max_Falling_Count = 50;
    static const int Max_Ball_Count = 5;//9
    static const int Max_Driver_Count = 10;
    static const int Max_Life_Counter = 5;
    static const int Max_Module_Count = 5;
    static bool Have_Floor;

    //Level
    static const int Block_Width = 45;
    static const int Block_Height = 21;
    static const int Level_X_Elems = 14;
    static const int Level_Y_Elems = 12;
    static const int Level_X_Offset = 24;
    static const int Level_Y_Offset = 18;
    static const int Min_X = 0;
    static const int Max_X = 564 - 3 * Level_X_Offset;//Max_X_Pos -...
    static const int Cell_Width = (Block_Width + 3);
    static const int Cell_Height = (Block_Height + 3);

    //Ball
    static const int Ball_Size = 12;
    static const double Step_Size;

    //Platform
    static const int Platform_Y_Position = 555;
    static const int Circle_Size = 15;
    static const int Platform_Height = 21;

    static const int Max_X_Pos = Level_X_Offset + Cell_Width * Level_Y_Elems - Ball_Size;
    static const int Max_Y_Pos = 600;//199

    
};