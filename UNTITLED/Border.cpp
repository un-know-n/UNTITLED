#include "Border.h"


//          BORDER

Border::Border() : Border_Main_Pen(0), Border_White_Pen(0),
Border_Main_Brush(0), Border_White_Brush(0)
{//Constructor
    Floor_Rect.left = Common::Level_X_Offset - 3;
    Floor_Rect.top = Common::Max_Y_Pos - Common::Level_Y_Offset;
    Floor_Rect.right = 600;
    Floor_Rect.bottom = Common::Max_Y_Pos;
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
        Rectangle(hdc, x + 3, y, x + 10, y + 8);
    else 
        Rectangle(hdc, x, y + 3, x + 6, y + 10);

    //White line
    SelectObject(hdc, Border_White_Pen);
    SelectObject(hdc, Border_White_Brush);

    if (is_vertical) {
        Rectangle(hdc, x, y, x + 1, y + 4);
    }
    else {
        Rectangle(hdc, x, y, x + 6, y + 1);
    }
    
}

void Border::Draw_Floor(HDC hdc, int x, int y) {

    //White line
    SelectObject(hdc, Border_White_Pen);
    SelectObject(hdc, Border_White_Brush);

    RoundRect(hdc, x + 5, y, x + 13, y + 3, 2, 2);
}

bool Border::Check_Colision(double next_x_pos, double next_y_pos, Ball *ball) {
    bool collided = false;

    //if we`ve collided with LEFT border
    if (next_x_pos < Common::Level_X_Offset) {
        collided = true;
        ball->Is_Vertical_Reflect(true);
    }

    //if we`ve collided with RIGHT border
    if (next_x_pos - ball->Radius - 6 > Common::Max_X_Pos) {
        collided = true;
        ball->Is_Vertical_Reflect(true);
    }

    //if we`ve collided with UPPER border
    if (next_y_pos - 4 < 0) {
        collided = true;
        ball->Is_Vertical_Reflect(false);
    }

    //if ball has flown through deathline || he`s collided with floor
    if (next_y_pos > Common::Max_Y_Pos - 3 * Common::Ball_Size + 5) {
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
    for (int i = 0; i < 150; i++)
        Draw_Element(hdc, 6, 9 + i * 4, TRUE);

    //Drawing right border
    for (int i = 0; i < 150; i++)
        Draw_Element(hdc, 603, 9 + i * 4, TRUE);

    //Drawing top border
    for (int i = 0; i < 150; i++)
        Draw_Element(hdc, 9 + i * 4, 6, FALSE);

    if (Common::Have_Floor) {
        if (IntersectRect(&destination_rect, &paint_area, &Floor_Rect)) {
            //Drawing floor
            for (int i = 0; i < 48; i++)//144
                Draw_Floor(hdc, 18 + i * 12, 591);//4
        }
    } else {
        if (IntersectRect(&destination_rect, &paint_area, &Floor_Rect)) {
            SelectObject(hdc, Common::BG_Pen);
            SelectObject(hdc, Common::BG_Brush);
            Rectangle(hdc, Floor_Rect.left, Floor_Rect.top, Floor_Rect.right, Floor_Rect.bottom);
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