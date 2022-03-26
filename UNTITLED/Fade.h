#pragma once
#include "Config.h"

enum EBrick_Type {
    EBT_None,
    EBT_Green,
    EBT_Blue, 
    EBT_Red,
    EBT_Yellow
};

class CFade_Brick {
public:
    CFade_Brick(EBrick_Type brick_type);

    RECT Fade_Rect;

    EBrick_Type Brick_Type;

    int Fade_Step;
    static const int Max_Fade_Step = 20;

    static HPEN Fade_Green_Pen[Max_Fade_Step];
    static HBRUSH Fade_Green_Brush[Max_Fade_Step];
    static HPEN Fade_Blue_Pen[Max_Fade_Step];
    static HBRUSH Fade_Blue_Brush[Max_Fade_Step];
    static HPEN Fade_Red_Pen[Max_Fade_Step];
    static HBRUSH Fade_Red_Brush[Max_Fade_Step];
    static HPEN Fade_Yellow_Pen[Max_Fade_Step];
    static HBRUSH Fade_Yellow_Brush[Max_Fade_Step];

    void Draw(HDC hdc);
    void Act(HWND hwnd);
    static void Set_Color();
    static unsigned char Get_Fade_Channel(unsigned char color, unsigned char bg_color, int step);
    static void Get_Fade_Color(const CColor &color, const CColor &bg_color,int step, HPEN &pen, HBRUSH &brush);
};

