
#include "Level.h"


char Level_01[CsConfig::Level_X_Elems][CsConfig::Level_Y_Elems] = {
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

//          CLEVEL

CLevel::CLevel() : Green_Brush(0), Blue_Brush(0), Red_Brush(0), Yellow_Brush(0),
Green_Pen(0), Blue_Pen(0), Red_Pen(0), Yellow_Pen(0), Level_Area{}
{//Constructor
}

void CLevel::Init(){
    CsConfig::Create_PenNBrush(43, 97, 49, Green_Pen, Green_Brush);
    CsConfig::Create_PenNBrush(43, 63, 97, Blue_Pen, Blue_Brush);
    CsConfig::Create_PenNBrush(97, 43, 43, Red_Pen, Red_Brush);
    CsConfig::Create_PenNBrush(112, 101, 46, Yellow_Pen, Yellow_Brush);

    Level_Area.left = CsConfig::Level_X_Offset * CsConfig::Extent;
    Level_Area.top = CsConfig::Level_Y_Offset * CsConfig::Extent;
    Level_Area.right = Level_Area.left + CsConfig::Cell_Width * CsConfig::Level_X_Elems * CsConfig::Extent;
    Level_Area.bottom = Level_Area.top + CsConfig::Cell_Height * CsConfig::Level_Y_Elems * CsConfig::Extent;
}

void CLevel::Draw_Brick(HDC hdc, int x, int y, EBrick_Type type) {//It draws game brick

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
    RoundRect(hdc, x * CsConfig::Extent, y * CsConfig::Extent,
        (x + CsConfig::Brick_Width) * CsConfig::Extent,
        (y + CsConfig::Brick_Height) * CsConfig::Extent, 3, 3);
}

void CLevel::Change_BG_Color(EBrick_Type type, HPEN &front_pen, HBRUSH &front_brush, HPEN &back_pen, HBRUSH &back_brush) {
    //We can change only existing bricks
    if (!(type == EBT_Blue || type == EBT_Green || type == EBT_Red || type == EBT_Yellow)) return;
    else {
        if (type == EBT_Blue) {
            front_pen = Blue_Pen;
            front_brush = Blue_Brush;

            back_pen = Yellow_Pen;
            back_brush = Yellow_Brush;
        }
        else if (type == EBT_Yellow) {
            front_pen = Yellow_Pen;
            front_brush = Yellow_Brush;

            back_pen = Blue_Pen;
            back_brush = Blue_Brush;
        }
        else if (type == EBT_Green) {
            front_pen = Green_Pen;
            front_brush = Green_Brush;

            back_pen = Red_Pen;
            back_brush = Red_Brush;
        }
        else if (type == EBT_Red) {
            front_pen = Red_Pen;
            front_brush = Red_Brush;

            back_pen = Green_Pen;
            back_brush = Green_Brush;
        }
    }
}

void CLevel::Draw_Brick_Animation(HDC hdc, EBrick_Type type, ELetter_Type letter_type, int x, int y, int step) {//It draws falling of the bonuses

    XFORM xForm, old_xForm;
    double offset;
    double rotation_angle;
    int half_height = CsConfig::Brick_Height * CsConfig::Extent / 2;

    HPEN front_pen, back_pen;
    HBRUSH front_brush, back_brush;

    step = step % 16;
    if (step < 8) {
        rotation_angle = 2.0 * M_PI / 16.0 * step;
    }
    else {
        rotation_angle = 2.0 * M_PI / 16.0 * (step - 8);
       //ahsdbjabsdjb
    }

    Change_BG_Color(type, front_pen, front_brush, back_pen, back_brush);

    if (step == 4 || step == 12) {

        //Draw front color
        SelectObject(hdc, front_pen);
        SelectObject(hdc, front_brush);

        Rectangle(hdc, x, y + half_height/2 + CsConfig::Extent, x + CsConfig::Brick_Width * CsConfig::Extent, y + half_height + CsConfig::Extent);

        //Draw back color
        SelectObject(hdc, back_pen);
        SelectObject(hdc, back_brush);

        Rectangle(hdc, x, y + half_height/2 + CsConfig::Extent, x + CsConfig::Brick_Width * CsConfig::Extent, y + half_height);

    }
    else {
        SetGraphicsMode(hdc, GM_ADVANCED);
        xForm.eM11 = 1.0f; 
        xForm.eM12 = 0.0f;
        xForm.eM21 = 0.0f;
        xForm.eM22 = (float)cos(rotation_angle);
        xForm.eDx  = (float)x; 
        xForm.eDy  = (float)y + (float)half_height; 
        GetWorldTransform(hdc, &old_xForm);
        SetWorldTransform(hdc, &xForm);

        SelectObject(hdc, back_pen);
        SelectObject(hdc, back_brush);

        offset = 3.0 * (1.0 - fabs(xForm.eM22)) * (double)CsConfig::Extent;

        Rectangle(hdc, 0, -half_height - (int)round(offset),  CsConfig::Brick_Width * CsConfig::Extent, half_height - (int)round(offset));

        SelectObject(hdc, front_pen);
        SelectObject(hdc, front_brush);

        Rectangle(hdc, 0, -half_height,  CsConfig::Brick_Width * CsConfig::Extent, half_height);

        if (step > 4 && step < 12) {
            if (letter_type == ELT_Circle) {
                SelectObject(hdc, back_pen);
                SelectObject(hdc, back_brush);
                Ellipse(hdc, 0 + 5 * CsConfig::Extent, -half_height + 2, 0 + 10 * CsConfig::Extent, half_height - 2);
            }
        }


        SetWorldTransform(hdc, &old_xForm);
    }
}

void CLevel::Draw(HDC hdc, RECT &paint_area) {//It draws level map

    RECT destination_rect;

    if(!(IntersectRect(&destination_rect, &paint_area, &Level_Area))) return;

    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 12; j++) {
            Draw_Brick(hdc, CsConfig::Level_X_Offset + j * CsConfig::Cell_Width,
                CsConfig::Level_Y_Offset + i * CsConfig::Cell_Height, (EBrick_Type)Level_01[i][j]);
        }
    }
}

void CLevel::Check_Ball_Colision(int &next_y_pos, double &ball_direction) {

    //If struck woth bricks

    int brick_y_pos = CsConfig::Level_X_Elems * CsConfig::Cell_Height;

    for (int i = CsConfig::Level_X_Elems - 1; i >= 0; i--) {
        for (int j = 0; j < CsConfig::Level_Y_Elems; j++) {
            if (Level_01[i][j] == 0) continue;
            else {
                if (next_y_pos < brick_y_pos) {
                    next_y_pos = brick_y_pos - (next_y_pos - brick_y_pos);
                    ball_direction = -ball_direction;
                }
            }
        }
        brick_y_pos -= CsConfig::Cell_Height;
    }
}

/////////////////////////////////////////////////////////////////////