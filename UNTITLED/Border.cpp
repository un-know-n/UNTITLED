#include "Border.h"


//          CSBORDER

bool Border::Have_Floor = true;

Border::Border() : Arc_Pen(0), Border_Main_Pen(0), Border_White_Pen(0),
Border_Main_Brush(0), Border_White_Brush(0)
{//Constructor
}

void Border::Init(){
    Config::Create_PenNBrush(133, 13, 37, Border_Main_Pen, Border_Main_Brush);
    Config::Create_PenNBrush(255, 255, 255, Border_White_Pen, Border_White_Brush);
}

void Border::Draw_Element(HDC hdc, int x, int y, BOOL is_vertical) {
    //Draw main line
    SelectObject(hdc, Border_Main_Pen);
    SelectObject(hdc, Border_Main_Brush);

    if (is_vertical) 
        Rectangle(hdc, (x + 1) * Config::Extent, y * Config::Extent, (x + 4) * Config::Extent, (y + 4) * Config::Extent);
    else 
        Rectangle(hdc, x * Config::Extent, (y + 1) * Config::Extent, (x + 4) * Config::Extent, (y + 4) * Config::Extent);

    //White line
    SelectObject(hdc, Border_White_Pen);
    SelectObject(hdc, Border_White_Brush);

    if(is_vertical)
        Rectangle(hdc, x * Config::Extent, y * Config::Extent, (x + 1) * Config::Extent - 1, (y + 4) * Config::Extent);
    else
        Rectangle(hdc, x * Config::Extent, y * Config::Extent, (x + 6) * Config::Extent, (y + 1) * Config::Extent - 1);

}

void Border::Draw(HDC hdc, RECT &paint_area) {

    //Drawing left border
    for(int i = 0; i < 50; i++)
        Draw_Element(hdc, 2, 3 + i * 4, TRUE);

    //Drawing right border
    for(int i = 0; i < 50; i++)
        Draw_Element(hdc, 201, 3 + i * 4, TRUE);

    //Drawing top border
    for(int i = 0; i < 50; i++)
        Draw_Element(hdc, 3 + i * 4, 2, FALSE);
}

bool Border::Check_Colision(double next_x_pos, double next_y_pos, Ball *ball) {
    bool collided = false;

    //if we`ve collided with LEFT border
    if (next_x_pos < Config::Level_X_Offset) {
        //next_x_pos = Config::Level_X_Offset - (Config::Level_X_Offset - next_x_pos);
        collided = true;
        ball->Is_Vertical_Reflect(true);
    }

    //if we`ve collided with RIGHT border
    if (next_x_pos - ball->Radius - 2 > Config::Max_X_Pos + Config::Level_X_Offset) {
        //next_x_pos = Config::Level_X_Offset - (Config::Level_X_Offset - next_x_pos);
        ////next_x_pos = Config::Max_X_Pos - (next_x_pos - Config::Max_X_Pos);
        collided = true;
        ball->Is_Vertical_Reflect(true);
    }

    //if we`ve collided with UPPER border
    if (next_y_pos - ball->Radius < 0) {
        //next_y_pos = Config::Level_Y_Offset - (Config::Level_Y_Offset - next_y_pos);
        collided = true;
        ball->Is_Vertical_Reflect(false);
    }

    //if ball has flown through deathline || he`s collided with floor
    if (next_y_pos > Config::Max_Y_Pos - Config::Ball_Size) {
        if (Have_Floor) {
            collided = true;
            ball->Is_Vertical_Reflect(false);
        } else ball->Ball_State = BS_None;
        /* next_y_pos = Config::Level_X_Offset - (Config::Level_X_Offset - next_y_pos);
         Ball_Direction = -Ball_Direction;*/
    }

    return collided;
}

/////////////////////////////////////////////////////////////////////