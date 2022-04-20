#pragma once
#include "Config.h"

enum EBlock_Type {
    BT_None,
    BT_Green,
    BT_Blue, 
    BT_Red,
    BT_Yellow
};

class Object_Designer {
public:
    virtual void Draw(HDC hdc, RECT &paint_area) = 0;
    virtual void Act() = 0;
    virtual bool Is_Finished() = 0;
};

class Fade_Block : public Object_Designer{
public:
    Fade_Block(EBlock_Type block_type, int x_pos, int y_pos);

    virtual void Draw(HDC hdc, RECT& paint_area);
    virtual void Act();
    virtual bool Is_Finished();

    static void Set_Color();
    static unsigned char Get_Fade_Channel(unsigned char color, unsigned char bg_color, int step);
    static void Get_Fade_Color(const Color& color, const Color& bg_color, int step, HPEN& pen, HBRUSH& brush);

    RECT Fade_Rect;

    EBlock_Type Block_Type;

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
};

