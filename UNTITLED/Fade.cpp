#include "Fade.h"

//          CFADE_BRICK

HPEN CFade_Brick::Fade_Green_Pen[Max_Fade_Step];
HBRUSH CFade_Brick::Fade_Green_Brush[Max_Fade_Step];
HPEN CFade_Brick::Fade_Blue_Pen[Max_Fade_Step];
HBRUSH CFade_Brick::Fade_Blue_Brush[Max_Fade_Step];
HPEN CFade_Brick::Fade_Red_Pen[Max_Fade_Step];
HBRUSH CFade_Brick::Fade_Red_Brush[Max_Fade_Step];
HPEN CFade_Brick::Fade_Yellow_Pen[Max_Fade_Step];
HBRUSH CFade_Brick::Fade_Yellow_Brush[Max_Fade_Step];

CFade_Brick::CFade_Brick(EBrick_Type brick_type)
    :   Fade_Step(0), Brick_Type(brick_type)
{//Constructor
}

void CFade_Brick::Draw(HDC hdc){

    HPEN pen = 0;
    HBRUSH brush = 0;

    switch (Brick_Type)
    {
    case EBT_Green:
        pen = Fade_Green_Pen[Fade_Step];
        brush = Fade_Green_Brush[Fade_Step];
        break;
    case EBT_Blue:
        pen = Fade_Blue_Pen[Fade_Step];
        brush = Fade_Blue_Brush[Fade_Step];
        break;
    case EBT_Red:
        pen = Fade_Red_Pen[Fade_Step];
        brush = Fade_Red_Brush[Fade_Step];
        break;
    case EBT_Yellow:
        pen = Fade_Yellow_Pen[Fade_Step];
        brush = Fade_Yellow_Brush[Fade_Step];
        break;
    default:
        break;
    }

    Fade_Rect.left = (CsConfig::Level_X_Offset + CsConfig::Cell_Width) * CsConfig::Extent;
    Fade_Rect.top = (CsConfig::Level_Y_Offset + CsConfig::Cell_Height) * CsConfig::Extent;
    Fade_Rect.right = Fade_Rect.left + CsConfig::Brick_Width * CsConfig::Extent;
    Fade_Rect.bottom = Fade_Rect.top + CsConfig::Brick_Height * CsConfig::Extent;

    SelectObject(hdc, pen);
    SelectObject(hdc, brush);

    RoundRect(hdc, Fade_Rect.left, Fade_Rect.top, Fade_Rect.right, Fade_Rect.bottom, 3, 3);
}

void CFade_Brick::Act(HWND hwnd){
    if(Fade_Step < Max_Fade_Step - 1){
        ++Fade_Step;
        InvalidateRect(hwnd, &Fade_Rect, FALSE);
    }
}

void CFade_Brick::Set_Color(){

    unsigned char r, g, b;

    for(int i = 0; i < Max_Fade_Step; i++){
        r = CsConfig::Blue_Brick.R - i * (CsConfig::Blue_Brick.R - CsConfig::BG_Color.R) / (Max_Fade_Step - 1);
        g = CsConfig::Blue_Brick.G - i * (CsConfig::Blue_Brick.G - CsConfig::BG_Color.G) / (Max_Fade_Step - 1);
        b = CsConfig::Blue_Brick.B - i * (CsConfig::Blue_Brick.B - CsConfig::BG_Color.B) / (Max_Fade_Step - 1);

        CsConfig::Create_PenNBrush(r, g, b, Fade_Blue_Pen[i], Fade_Blue_Brush[i]);
    }

    
    
}

//////////////////////////////////////////////////////////////////