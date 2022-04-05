
#include "Ball.h"

//      CBALL

const double CBall::Start_Y_Pos = 173.0;
const double CBall::Radius = 2.0;
int CBall::Hit_Counter = 0;
Hit_Checker* CBall::Hit_Check[] = {};

CBall::CBall() : Ball_Pen(0), Ball_Brush(0), Central_X(0), Central_Y(Start_Y_Pos), Ball_Speed(3.0), Rest_Size(0),
Ball_Direction(M_PI - M_PI_4), Ball_Rect{}, Ball_State(EBS_Start) //M_PI - M_PI_4
{//Constructor
    Central_X = CsConfig::Max_X / 2;
    Set_State(EBS_Start, Central_X);
    //Set_Direction(M_PI_4);
}

void CBall::Init(){
    CsConfig::Create_PenNBrush(255, 255, 255, Ball_Pen, Ball_Brush);
}

void CBall::Draw(HDC hdc, RECT &paint_area) {
    //if there`s no collision with painting area -> there`s no ball
    RECT destination_rect;

    if (IntersectRect(&destination_rect, &paint_area, &Prev_Ball_Rect)) {
        //Clear BG
        SelectObject(hdc, CsConfig::BG_Pen);
        SelectObject(hdc, CsConfig::BG_Brush);

        Ellipse(hdc, Prev_Ball_Rect.left, Prev_Ball_Rect.top, Prev_Ball_Rect.right - 1, Prev_Ball_Rect.bottom - 1);
    }
    
    if (IntersectRect(&destination_rect, &paint_area, &Ball_Rect)) {
        //Draw the Ball
        SelectObject(hdc, Ball_Pen);
        SelectObject(hdc, Ball_Brush);

        Ellipse(hdc, Ball_Rect.left, Ball_Rect.top, Ball_Rect.right - 1, Ball_Rect.bottom - 1);
    }
    
}

void CBall::Move() { //Hit_Checker*level_hit, Hit_Checker *border_hit, Hit_Checker*platform_hit
    double next_x_pos, next_y_pos;
    double step_size = 1.0 / CsConfig::Extent;
    Rest_Size += Ball_Speed;
    bool collided;
    Prev_Ball_Rect = Ball_Rect;
    //int hit_counter = 3;

    while (Rest_Size >= step_size) {
        collided = false;
        //Calculating new coords
        next_x_pos = Central_X + step_size * cos(Ball_Direction);
        next_y_pos = Central_Y - step_size * sin(Ball_Direction);

        for (int i = 0; i < Hit_Counter; i++) {
            //If we`ve collided with smth
            collided |= Hit_Check[i]->Check_Colision(next_x_pos, next_y_pos, this);// smth = state1 | state2 (Always true if it is)
        }

        //If we`ve collided with border
        //collided |= border_hit->Check_Colision(next_x_pos, next_y_pos, this);// smth = state1 | state2 (Always true if it is)

        //If we`ve collided with blocks
        //collided |= level_hit->Check_Colision(next_x_pos, next_y_pos, this); // smth = state1 | state2 (Always true if it is)
               
        //If struck with platform
        //collided |= platform_hit->Check_Colision(next_x_pos, next_y_pos, this); // smth = state1 | state2 (Always true if it is)

        if (!collided) {
            //Ball translation if we haven't collided with anything
            Rest_Size -= step_size;

            Central_X = next_x_pos;
            Central_Y = next_y_pos;
            
        }
        
    }
    Redraw();
    
}

void CBall::Redraw() {

    Ball_Rect.left = (int)((Central_X - Radius) * CsConfig::Extent);
    Ball_Rect.top = (int)(CsConfig::Level_Y_Offset + Central_Y - Radius) * CsConfig::Extent;
    Ball_Rect.right = (int)((Central_X + Radius) * CsConfig::Extent);
    Ball_Rect.bottom = (int)(CsConfig::Level_Y_Offset + Central_Y + Radius) * CsConfig::Extent;

    InvalidateRect(CsConfig::Hwnd, &Prev_Ball_Rect, FALSE);
    InvalidateRect(CsConfig::Hwnd, &Ball_Rect, FALSE);
}

EBall_State CBall::Get_State() {
    return Ball_State;
}

void CBall::Set_State(EBall_State state, int x_pos) {
    /*if (Ball_State == state) return;
    else Ball_State = state;*/
    switch (state) {
    case EBS_None:
        Ball_Speed = 0.0;
        Rest_Size = 0.0;
        break;

    case EBS_Start:
        Central_X = x_pos;
        Central_Y = Start_Y_Pos;
        Ball_Speed = 0.0;
        Rest_Size = 0.0;
        Ball_Direction = M_PI - M_PI_4;
        Redraw();
        break;

    case EBS_Free:
        Central_X = x_pos;
        Central_Y = Start_Y_Pos;
        Ball_Speed = 3.0;
        Rest_Size = 0.0;
        Ball_Direction = M_PI - M_PI_4;
        break;
    }

    Ball_State = state;
}

double CBall::Get_Direction() {
    return Ball_Direction;
}

void CBall::Set_Direction(double new_direction) {
    while (new_direction > 2.0 * M_PI) new_direction -= 2.0 * M_PI;
    while (new_direction < 0) new_direction += 2.0 * M_PI;
    if (Ball_Direction == new_direction) return;
    else Ball_Direction = new_direction;
}

void CBall::Reflect(bool is_vertical) {
    if (is_vertical) {
        Set_Direction(M_PI - Ball_Direction);
    }
    else {
        Set_Direction(-Ball_Direction);
    }
}

void CBall::Add_Hit_Checker(Hit_Checker* hit_check) {
    if (Hit_Counter >= sizeof(Hit_Check) / sizeof(Hit_Check[0])) return;
    Hit_Check[Hit_Counter++] = hit_check;
}

/////////////////////////////////////////////////////////////////////