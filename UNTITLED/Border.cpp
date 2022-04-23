#include "Border.h"


//          BORDER

Border::Border() : Border_Main_Pen(0), Border_White_Pen(0),
Border_Main_Brush(0), Border_White_Brush(0)
{//Constructor
    Floor_Rect.left = (Common::Level_X_Offset - 1) * Common::Extent;
    Floor_Rect.top = (Common::Max_Y_Pos - Common::Level_Y_Offset) * Common::Extent;
    Floor_Rect.right = 200 * Common::Extent;
    Floor_Rect.bottom = Common::Max_Y_Pos * Common::Extent;
}

void Border::Init(){
    Common::Create_PenNBrush(133, 13, 37, Border_Main_Pen, Border_Main_Brush);
    Common::Create_PenNBrush(255, 255, 255, Border_White_Pen, Border_White_Brush);
}

void Border::Draw_Element(HDC hdc, int x, int y, BOOL is_vertical) {
    //Draw main line
    SelectObject(hdc, Border_Main_Pen);
    SelectObject(hdc, Border_Main_Brush);

    if (is_vertical) 
        Rectangle(hdc, (x + 1) * Common::Extent, y * Common::Extent, (x + 4) * Common::Extent - 1, (y + 4) * Common::Extent - 1);
    else 
        Rectangle(hdc, x * Common::Extent, (y + 1) * Common::Extent, (x + 4) * Common::Extent - 1, (y + 4) * Common::Extent - 1);

    //White line
    SelectObject(hdc, Border_White_Pen);
    SelectObject(hdc, Border_White_Brush);

    if (is_vertical) {
        Rectangle(hdc, x * Common::Extent, y * Common::Extent, (x + 1) * Common::Extent - 2, (y + 4) * Common::Extent - 1);
    }
    else {
        Rectangle(hdc, x * Common::Extent, y * Common::Extent, (x + 6) * Common::Extent - 1, (y + 1) * Common::Extent - 2);
    }
    
}

void Border::Draw_Floor(HDC hdc, int x, int y) {

    //White line
    SelectObject(hdc, Border_White_Pen);
    SelectObject(hdc, Border_White_Brush);

    RoundRect(hdc, x * Common::Extent, y * Common::Extent, (x + 3) * Common::Extent - 1, (y + 1) * Common::Extent - 2, 2, 2);
}

bool Border::Check_Colision(double next_x_pos, double next_y_pos, Ball *ball) {
    bool collided = false;

    //if we`ve collided with LEFT border
    if (next_x_pos < Common::Level_X_Offset) {
        collided = true;
        ball->Is_Vertical_Reflect(true);
    }

    //if we`ve collided with RIGHT border
    if (next_x_pos - ball->Radius - 2 > Common::Max_X_Pos + Common::Level_X_Offset - 1) {
        collided = true;
        ball->Is_Vertical_Reflect(true);
    }

    //if we`ve collided with UPPER border
    if (next_y_pos - ball->Radius < 0) {
        collided = true;
        ball->Is_Vertical_Reflect(false);
    }

    //if ball has flown through deathline || he`s collided with floor
    if (next_y_pos > Common::Max_Y_Pos - 3 * Common::Ball_Size + 2) {
        if (Common::Have_Floor) {
            collided = true;
            ball->Is_Vertical_Reflect(false);
        } else if (next_y_pos > Common::Max_Y_Pos + Common::Ball_Size)
            ball->Ball_State = BS_None;
    }

    return collided;
}

void Border::Draw(HDC hdc, RECT& paint_area) {

    RECT destination_rect;

    //Drawing left border
    for (int i = 0; i < 50; i++)
        Draw_Element(hdc, 2, 3 + i * 4, TRUE);

    //Drawing right border
    for (int i = 0; i < 50; i++)
        Draw_Element(hdc, 201, 3 + i * 4, TRUE);

    //Drawing top border
    for (int i = 0; i < 50; i++)
        Draw_Element(hdc, 3 + i * 4, 2, FALSE);

    if (Common::Have_Floor) {
        if (IntersectRect(&destination_rect, &paint_area, &Floor_Rect)) {
            //Drawing floor
            for (int i = 0; i < 49; i++)
                Draw_Floor(hdc, 6 + i * 4, 197);
        }
    }
}

void Border::Animate() {
    //There`s nothing
}

bool Border::Is_Finished() {
    //There`s nothing
    return false;
}

void Border::Redraw_Floor() {
    InvalidateRect(Common::Hwnd, &Floor_Rect, FALSE);
}

/////////////////////////////////////////////////////////////////////