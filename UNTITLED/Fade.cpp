#include "Fade.h"

//          CFADE_BRICK

HPEN Fade_Block::Fade_Green_Pen[Max_Fade_Step];
HBRUSH Fade_Block::Fade_Green_Brush[Max_Fade_Step];
HPEN Fade_Block::Fade_Blue_Pen[Max_Fade_Step];
HBRUSH Fade_Block::Fade_Blue_Brush[Max_Fade_Step];
HPEN Fade_Block::Fade_Red_Pen[Max_Fade_Step];
HBRUSH Fade_Block::Fade_Red_Brush[Max_Fade_Step];
HPEN Fade_Block::Fade_Yellow_Pen[Max_Fade_Step];
HBRUSH Fade_Block::Fade_Yellow_Brush[Max_Fade_Step];

Fade_Block::Fade_Block(EBlock_Type block_type, int x_pos, int y_pos)
    :   Fade_Step(0), Block_Type(block_type)
{//Constructor
    //Creation of the rectangle in which block is fading
    Fade_Rect.left = (Config::Level_X_Offset + x_pos * Config::Cell_Width) * Config::Extent;
    Fade_Rect.top = (Config::Level_Y_Offset + y_pos * Config::Cell_Height) * Config::Extent;
    Fade_Rect.right = Fade_Rect.left + Config::Block_Width * Config::Extent;
    Fade_Rect.bottom = Fade_Rect.top + Config::Block_Height * Config::Extent;
}

void Fade_Block::Draw(HDC hdc){
    //Pick up the brush and pen which are currently needed to put on the block
    HPEN pen = 0;
    HBRUSH brush = 0;

    switch (Block_Type)
    {
    case BT_Green:
        pen = Fade_Green_Pen[Fade_Step];
        brush = Fade_Green_Brush[Fade_Step];
        break;
    case BT_Blue:
        pen = Fade_Blue_Pen[Fade_Step];
        brush = Fade_Blue_Brush[Fade_Step];
        break;
    case BT_Red:
        pen = Fade_Red_Pen[Fade_Step];
        brush = Fade_Red_Brush[Fade_Step];
        break;
    case BT_Yellow:
        pen = Fade_Yellow_Pen[Fade_Step];
        brush = Fade_Yellow_Brush[Fade_Step];
        break;
    default:
        break;
    }

    SelectObject(hdc, pen);
    SelectObject(hdc, brush);

    Rectangle(hdc, Fade_Rect.left, Fade_Rect.top, Fade_Rect.right, Fade_Rect.bottom);
}

void Fade_Block::Act(){
    //Check our fading process -> redrawing the block
    if(Fade_Step < Max_Fade_Step - 1){
        ++Fade_Step;
        InvalidateRect(Config::Hwnd, &Fade_Rect, FALSE);
    }
}

bool Fade_Block::Is_Finished() {
    if (Fade_Step >= Max_Fade_Step - 1) return true;
    else return false;
}

void Fade_Block::Set_Color(){
    //unsigned char r, g, b;

    for(int i = 0; i < Max_Fade_Step; i++){
        Get_Fade_Color(Config::Blue_Block, Config::BG_Color, i, Fade_Blue_Pen[i], Fade_Blue_Brush[i]);
        Get_Fade_Color(Config::Red_Block, Config::BG_Color, i, Fade_Red_Pen[i], Fade_Red_Brush[i]);
        Get_Fade_Color(Config::Green_Block, Config::BG_Color, i, Fade_Green_Pen[i], Fade_Green_Brush[i]);
        Get_Fade_Color(Config::Yellow_Block, Config::BG_Color, i, Fade_Yellow_Pen[i], Fade_Yellow_Brush[i]);
    }

}

unsigned char Fade_Block::Get_Fade_Channel(unsigned char color, unsigned char bg_color, int step){
    const int max_step = Max_Fade_Step - 1;
    return color - step * (color - bg_color) / max_step;
}

void Fade_Block::Get_Fade_Color(const Color &color, const Color &bg_color,int step, HPEN &pen, HBRUSH &brush){
    unsigned char r, g, b;
    r = Get_Fade_Channel(color.R, bg_color.R, step);
    g = Get_Fade_Channel(color.G, bg_color.G, step);
    b = Get_Fade_Channel(color.B, bg_color.B, step);
    Config::Create_PenNBrush(r, g, b, pen, brush);
}

//////////////////////////////////////////////////////////////////