
#include "Ball.h"

//      CBALL

CBall::CBall() : Ball_Pen(0), Ball_Brush(0), Y_Pos(172.0), Ball_Speed(4.6), 
Ball_Direction(M_PI - M_PI_4), Ball_Rect{}, Ball_State(EBS_Normal)
{//Constructor
    //X_Pos = CsConfig::Max_X / 2;
}

void CBall::Init(int x_pos){
    X_Pos = x_pos;
    CsConfig::Create_PenNBrush(255, 255, 255, Ball_Pen, Ball_Brush);
}

void CBall::Draw(HDC hdc, RECT &paint_area) {
    //if there`s no collision with painting area -> there`s no ball
    RECT destination_rect;
    if(!IntersectRect(&destination_rect, &paint_area, &Prev_Ball_Rect))
        return;

    //Clear BG
    SelectObject(hdc, CsConfig::BG_Pen);
    SelectObject(hdc, CsConfig::BG_Brush);

    Ellipse(hdc, Prev_Ball_Rect.left, Prev_Ball_Rect.top, Prev_Ball_Rect.right - 1, Prev_Ball_Rect.bottom - 1);

    //Draw the Ball
    SelectObject(hdc, Ball_Pen);
    SelectObject(hdc, Ball_Brush);

    Ellipse(hdc, Ball_Rect.left, Ball_Rect.top, Ball_Rect.right - 1, Ball_Rect.bottom - 1);
}

void CBall::Move(HWND hwnd, CLevel *level, int x_pos, int width) {
    double next_x_pos, next_y_pos;
    Prev_Ball_Rect = Ball_Rect;

    if(Ball_State == EBS_None) return;

    //Calculating new coords
    next_x_pos = X_Pos + Ball_Speed * cos(Ball_Direction);
    next_y_pos = Y_Pos - Ball_Speed * sin(Ball_Direction);

    //if we`ve collided with wall
    if (next_x_pos < CsConfig::Level_X_Offset) {
        next_x_pos = CsConfig::Level_X_Offset - (CsConfig::Level_X_Offset - next_x_pos);
        Ball_Direction = M_PI - Ball_Direction;
    }

    if (next_y_pos < 0) {
        next_y_pos = CsConfig::Level_Y_Offset - (CsConfig::Level_Y_Offset - next_y_pos);
        Ball_Direction = -Ball_Direction;
    }

    if (next_x_pos > CsConfig::Max_X_Pos + CsConfig::Level_X_Offset) {
        next_x_pos = CsConfig::Level_X_Offset - (CsConfig::Level_X_Offset - next_x_pos);
        Ball_Direction = M_PI - Ball_Direction;
    }

    if (next_y_pos > CsConfig::Max_Y_Pos + CsConfig::Level_X_Offset + CsConfig::Ball_Size) {
        Ball_State = EBS_None;
        //next_y_pos = CsConfig::Level_X_Offset - (CsConfig::Level_X_Offset - next_y_pos);
        //Ball_Direction = -Ball_Direction;
    }

    //If struck with platform

    if (next_y_pos > CsConfig::Platform_Y_Position - 12) {
        if (next_x_pos >= x_pos && next_x_pos <= x_pos + width) {
            next_y_pos = CsConfig::Platform_Y_Position - (CsConfig::Platform_Y_Position - next_y_pos);
            Ball_Direction = -Ball_Direction;
        }

    }

    level->Check_Ball_Colision(next_y_pos, Ball_Direction);

    //Ball translation
    X_Pos = next_x_pos;
    Y_Pos = next_y_pos;

    Ball_Rect.left =  (int)(X_Pos * CsConfig::Extent);
    Ball_Rect.top = (int)(CsConfig::Level_Y_Offset + Y_Pos) * CsConfig::Extent;
    Ball_Rect.right = Ball_Rect.left + CsConfig::Ball_Size * CsConfig::Extent;
    Ball_Rect.bottom = Ball_Rect.top + CsConfig::Ball_Size * CsConfig::Extent;

    //Redraw ball
    InvalidateRect(hwnd, &Prev_Ball_Rect, FALSE);
    InvalidateRect(hwnd, &Ball_Rect, FALSE);
}

/////////////////////////////////////////////////////////////////////