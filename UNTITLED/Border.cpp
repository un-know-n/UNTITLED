#include "Border.h"


//          CSBORDER

CsBorder::CsBorder() : Arc_Pen(0), Border_Main_Pen(0), Border_White_Pen(0),
Border_Main_Brush(0), Border_White_Brush(0)
{//Constructor
}

void CsBorder::Init(){
    CsConfig::Create_PenNBrush(133, 13, 37, Border_Main_Pen, Border_Main_Brush);
    CsConfig::Create_PenNBrush(255, 255, 255, Border_White_Pen, Border_White_Brush);
}

void CsBorder::Draw_Element(HDC hdc, int x, int y, BOOL is_vertical) {
    //Draw main line
    SelectObject(hdc, Border_Main_Pen);
    SelectObject(hdc, Border_Main_Brush);

    if (is_vertical) 
        Rectangle(hdc, (x + 1) * CsConfig::Extent, y * CsConfig::Extent, (x + 4) * CsConfig::Extent, (y + 4) * CsConfig::Extent);
    else 
        Rectangle(hdc, x * CsConfig::Extent, (y + 1) * CsConfig::Extent, (x + 4) * CsConfig::Extent, (y + 4) * CsConfig::Extent);

    //White line
    SelectObject(hdc, Border_White_Pen);
    SelectObject(hdc, Border_White_Brush);

    if(is_vertical)
        Rectangle(hdc, x * CsConfig::Extent, y * CsConfig::Extent, (x + 1) * CsConfig::Extent - 1, (y + 4) * CsConfig::Extent);
    else
        Rectangle(hdc, x * CsConfig::Extent, y * CsConfig::Extent, (x + 6) * CsConfig::Extent, (y + 1) * CsConfig::Extent - 1);

    //White inner-dot
    /*SelectObject(hdc, Border_White_Pen);
    SelectObject(hdc, Border_White_Brush);

    if(is_vertical)
        Rectangle(hdc, (x + 2) * CsConfig::Extent, (y + 1) * CsConfig::Extent, (x + 3) * CsConfig::Extent, (y + 6) * CsConfig::Extent);
    else
        Rectangle(hdc, (x + 1) * CsConfig::Extent, (y + 2) * CsConfig::Extent, (x + 6) * CsConfig::Extent, (y + 3) * CsConfig::Extent);*/

}

void CsBorder::Draw(HDC hdc, RECT &paint_area) {

    //Drawing left/right border
    for(int i = 0; i < 50; i++)
        Draw_Element(hdc, 2, 3 + i * 4, TRUE);

    for(int i = 0; i < 50; i++)
        Draw_Element(hdc, 201, 3 + i * 4, TRUE);

    //Drawing top border
    for(int i = 0; i < 50; i++)
        Draw_Element(hdc, 3 + i * 4, 2, FALSE);
}

bool CsBorder::Check_Colision(double next_x_pos, double next_y_pos, CBall *ball) {
    bool collided = false;

    //if we`ve collided with wall
    if (next_x_pos < CsConfig::Level_X_Offset) {
        //next_x_pos = CsConfig::Level_X_Offset - (CsConfig::Level_X_Offset - next_x_pos);
        collided = true;
        ball->Is_Vertical_Reflect(true);
    }

    if (next_y_pos - ball->Radius < 0) {
        //next_y_pos = CsConfig::Level_Y_Offset - (CsConfig::Level_Y_Offset - next_y_pos);
        collided = true;
        ball->Is_Vertical_Reflect(false);
    }

    if (next_x_pos - ball->Radius - 2 > CsConfig::Max_X_Pos + CsConfig::Level_X_Offset) {
        //next_x_pos = CsConfig::Level_X_Offset - (CsConfig::Level_X_Offset - next_x_pos);
        ////next_x_pos = CsConfig::Max_X_Pos - (next_x_pos - CsConfig::Max_X_Pos);
        collided = true;
        ball->Is_Vertical_Reflect(true);
    }

    if (next_y_pos > CsConfig::Max_Y_Pos + CsConfig::Level_Y_Offset) {
        /* next_y_pos = CsConfig::Level_X_Offset - (CsConfig::Level_X_Offset - next_y_pos);
         Ball_Direction = -Ball_Direction;*/
        ball->Ball_State = EBS_None;
    }

    return collided;
}

/////////////////////////////////////////////////////////////////////