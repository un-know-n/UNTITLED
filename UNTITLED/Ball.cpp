
#include "Ball.h"

//          DRIVER

Driver::~Driver() {

}

///////////////////////////

const double Ball::Start_Y_Pos = 519.0;
const double Ball::Radius = 6.0;
int Ball::Hit_Counter = 0;
Main_Hit_Checker* Ball::Hit_Check[] = {};

Ball::Ball() : Ball_Pen(0), Ball_Brush(0), Central_X(0), Central_Y(Start_Y_Pos), Ball_Speed(9.0), Rest_Size(0),
Ball_Direction(M_PI - M_PI_4), Ball_Rect{}, Test_Active(false), Move_Pos(0), Ball_State(BS_Start) 
{//Constructor
}

void Ball::Initialization() {
    Prev_Ball_Rect = Ball_Rect;
}

void Ball::Finalization() {
    Redraw();
}

void Ball::Next_Step(double max_speed) {
    double next_x_pos, next_y_pos;
    double next_step;
    bool collided = true;

    if (Ball_State == BS_Disabled || Ball_State == BS_None) return;

    next_step = Ball_Speed / max_speed * Common::Step_Size;

    //If we`ve remaining space for the ball -> we use it and it won`t be lost
    while (collided) {
        collided = false;
        //Calculating new coords
        next_x_pos = Central_X + next_step * cos(Ball_Direction);//Common::Step_Size
        next_y_pos = Central_Y - next_step * sin(Ball_Direction);

        for (int i = 0; i < Hit_Counter; i++) {
            //If we`ve collided with smth (Platform || Border || Block)
            collided |= Hit_Check[i]->Check_Colision(next_x_pos, next_y_pos, this);// smth = state1 | state2 (Always true if it is)
        }

        if (!collided) {

            //Application of new coords
            Central_X = next_x_pos;
            Central_Y = next_y_pos;
        }

        //Only if we`re testing smth
        if (Test_Active) Rest_Test_Size -= next_step;

    }
}

double Ball::Get_Speed() {
    return Ball_Speed;
}

void Ball::Draw(HDC hdc, RECT& paint_area) {
    //if there`s no collision with painting area -> there`s no ball
    RECT destination_rect;

    if (Ball_State == BS_Disabled || Ball_State == BS_None) return;

    //if there`s any crossings with paint area -> draw the ball
    if (IntersectRect(&destination_rect, &paint_area, &Prev_Ball_Rect)) {
        //Clear BG
        SelectObject(hdc, Common::BG_Pen);
        SelectObject(hdc, Common::BG_Brush);

        Ellipse(hdc, Prev_Ball_Rect.left, Prev_Ball_Rect.top, Prev_Ball_Rect.right - 2, Prev_Ball_Rect.bottom - 2);
    }

    if (IntersectRect(&destination_rect, &paint_area, &Ball_Rect)) {
        //Draw the Ball
        SelectObject(hdc, Ball_Pen);
        SelectObject(hdc, Ball_Brush);

        Ellipse(hdc, Ball_Rect.left, Ball_Rect.top, Ball_Rect.right - 2, Ball_Rect.bottom - 2);
    }

}

void Ball::Animate(){
    //There`s nothing
}

bool Ball::Is_Finished() {
    //There`s nothing
    return false;
}

void Ball::Get_Center(double& ball_x_pos, double& ball_y_pos) {
    //Default getter
    ball_x_pos = Central_X;
    ball_y_pos = Central_Y;
}

void Ball::Init(){
    //Initialization of main pen and brush
    Common::Create_PenNBrush(255, 255, 255, Ball_Pen, Ball_Brush);
}

void Ball::Redraw() {
    //Creation of the rectangle area in which ball is placed
    Ball_Rect.left = (int)(Central_X - Radius);
    Ball_Rect.top = (int)(Common::Level_Y_Offset + Central_Y - Radius);
    Ball_Rect.right = (int)(Central_X + Radius);
    Ball_Rect.bottom = (int)(Common::Level_Y_Offset + Central_Y + Radius);

    //Redrawing old and new places of the ball
    InvalidateRect(Common::Hwnd, &Prev_Ball_Rect, FALSE);
    InvalidateRect(Common::Hwnd, &Ball_Rect, FALSE);
}

EBall_State Ball::Get_State() {
    //Default getter
    return Ball_State;
}

void Ball::Set_State(EBall_State state, int x_pos) {
    //Applying new state with new options
    switch (state) {
    case BS_Disabled:
        Ball_Speed = 0.0;
        Rest_Size = 0.0;
        break;    

    case BS_None:
        Ball_Speed = 0.0;
        Rest_Size = 0.0;
        break;

    case BS_Test:
        Central_X = x_pos;
        Central_Y = 575;//140
        Ball_Speed = 9.0;
        Rest_Size = 0.0;
        Ball_Direction = M_PI_4;//M_PI - M_PI_4
        break;

    case BS_Start:
        Central_X = x_pos;
        Central_Y = Start_Y_Pos;
        Ball_Speed = 0.0;
        Rest_Size = 0.0;
        Ball_Direction = M_PI - M_PI_4;
        Redraw();
        break;

    case BS_Free:
        Central_X = x_pos;
        Central_Y = Start_Y_Pos;//82 - 52
        Ball_Speed = 9.0;
        Rest_Size = 0.0;
        Ball_Direction = M_PI - M_PI_4;
        break;
    }

    Ball_State = state;
}

double Ball::Get_Direction() {
    //Default getter
    return Ball_Direction;
}

void Ball::Set_Direction(double new_direction) {
    //Implemented new function to reduce too positive/negative angle of the ball
    while (new_direction > 2.0 * M_PI) new_direction -= 2.0 * M_PI;
    while (new_direction < 0) new_direction += 2.0 * M_PI;
    //If we already have this direction -> do nothing
    if (Ball_Direction == new_direction) return;
    else Ball_Direction = new_direction;
}

void Ball::Is_Vertical_Reflect(bool is_vertical) {
    if (is_vertical) {
        Set_Direction(M_PI - Ball_Direction);
    }
    else {
        Set_Direction(-Ball_Direction);
    }
}

void Ball::Add_Hit_Checker(Main_Hit_Checker* hit_check) {
    //Applying new type of object that needs to be added to the array of hit-checkers (Border || Platform...)
    if (Hit_Counter >= sizeof(Hit_Check) / sizeof(Hit_Check[0])) return;
    Hit_Check[Hit_Counter++] = hit_check;
}

void Ball::Set_Test(){
    //Automatically sets ball to the test mode
    Rest_Test_Size = 30.0;
    Set_State(BS_Test, 375 + Move_Pos);//85
    ++Move_Pos;
    Test_Active = true;
}

bool Ball::Is_Test_Finished(){
    //Check if we`ve flown needed area
    if(Test_Active){
        if(Rest_Test_Size <= 0) {
            return true;
            Set_State(BS_None, 0);
            Test_Active = false;
        } else return false;
    }
}

bool Ball::Is_Going_Up() {
    //Check if our angle from 0 to M_PI
    if (Ball_Direction >= 0.0 && Ball_Direction < M_PI) return true;
    else return false;
}

bool Ball::Is_Going_Left() {
    //Check if our angle from M_PI to 3/2 * M_PI
    if (Ball_Direction > M_PI_2 && Ball_Direction < 3 * M_PI_2) return true;
    else return false;
}

/////////////////////////////////////////////////////////////////////

bool Main_Hit_Checker::Dot_Circle_Hit(double y, double next_x_pos, double left_x, double right_x, double radius, double& x) {//double &x
    //Check if we`ve collided with horizontal line of block(from left_x to right_x)
    //Circle equation that helps us to make right reflection
    //x^2 + y^2 = R^2
    //x = sqrt(R^2 - y^2)
    //y = sqrt(R^2 - x^2)

    double min_x;
    double max_x;

    if (y > radius) return false;

    x = sqrt(radius * radius - y * y);

    min_x = next_x_pos - x;
    max_x = next_x_pos + x;

    if (max_x >= left_x && max_x <= right_x || min_x >= left_x && min_x <= right_x) return true;
    else return false;
}

/////////////////////////////////////////////////////////////////////