#include "Border.h"


//          BORDER

Border::Border() : Border_Main_Pen(0), Border_White_Pen(0),
Border_Main_Brush(0), Border_White_Brush(0)
{//Constructor
    Floor_Rect.left = (Config::Level_X_Offset - 1) * Config::Extent;
    Floor_Rect.top = (Config::Max_Y_Pos - Config::Level_Y_Offset) * Config::Extent;
    Floor_Rect.right = 200 * Config::Extent;
    Floor_Rect.bottom = Config::Max_Y_Pos * Config::Extent;
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
        Rectangle(hdc, (x + 1) * Config::Extent, y * Config::Extent, (x + 4) * Config::Extent - 1, (y + 4) * Config::Extent - 1);
    else 
        Rectangle(hdc, x * Config::Extent, (y + 1) * Config::Extent, (x + 4) * Config::Extent - 1, (y + 4) * Config::Extent - 1);

    //White line
    SelectObject(hdc, Border_White_Pen);
    SelectObject(hdc, Border_White_Brush);

    if (is_vertical) {
        Rectangle(hdc, x * Config::Extent, y * Config::Extent, (x + 1) * Config::Extent - 2, (y + 4) * Config::Extent - 1);
    }
    else {
        Rectangle(hdc, x * Config::Extent, y * Config::Extent, (x + 6) * Config::Extent - 1, (y + 1) * Config::Extent - 2);
    }
    
}

void Border::Draw_Floor(HDC hdc, int x, int y) {

    //White line
    SelectObject(hdc, Border_White_Pen);
    SelectObject(hdc, Border_White_Brush);

    RoundRect(hdc, x * Config::Extent, y * Config::Extent, (x + 3) * Config::Extent - 1, (y + 1) * Config::Extent - 2, 2, 2);
}

void Border::Draw(HDC hdc, RECT &paint_area) {

    RECT destination_rect;

    //Drawing left border
    for(int i = 0; i < 50; i++)
        Draw_Element(hdc, 2, 3 + i * 4, TRUE);

    //Drawing right border
    for(int i = 0; i < 50; i++)
        Draw_Element(hdc, 201, 3 + i * 4, TRUE);

    //Drawing top border
    for(int i = 0; i < 50; i++)
        Draw_Element(hdc, 3 + i * 4, 2, FALSE);

    if (Config::Have_Floor) {
        if (IntersectRect(&destination_rect, &paint_area, &Floor_Rect)) {
            //Drawing floor
            for (int i = 0; i < 49; i++)
                Draw_Floor(hdc, 6 + i * 4, 197);
        }
    }
}

bool Border::Check_Colision(double next_x_pos, double next_y_pos, Ball *ball) {
    bool collided = false;

    //if we`ve collided with LEFT border
    if (next_x_pos < Config::Level_X_Offset) {
        collided = true;
        ball->Is_Vertical_Reflect(true);
    }

    //if we`ve collided with RIGHT border
    if (next_x_pos - ball->Radius - 2 > Config::Max_X_Pos + Config::Level_X_Offset - 1) {
        collided = true;
        ball->Is_Vertical_Reflect(true);
    }

    //if we`ve collided with UPPER border
    if (next_y_pos - ball->Radius < 0) {
        collided = true;
        ball->Is_Vertical_Reflect(false);
    }

    //if ball has flown through deathline || he`s collided with floor
    if (next_y_pos > Config::Max_Y_Pos - 3 * Config::Ball_Size + 2) {
        if (Config::Have_Floor) {
            collided = true;
            ball->Is_Vertical_Reflect(false);
        } else if (next_y_pos > Config::Max_Y_Pos + Config::Ball_Size)
            ball->Ball_State = BS_None;
    }

    return collided;
}

void Border::Redraw_Floor() {
    InvalidateRect(Config::Hwnd, &Floor_Rect, FALSE);
}

/////////////////////////////////////////////////////////////////////