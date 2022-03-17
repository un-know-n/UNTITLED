#define _USE_MATH_DEFINES
#include <math.h>
#include "Engine.h"

//Main variables

enum EBrick_Type {
    EBT_None,
    EBT_Green,
    EBT_Blue, 
    EBT_Red,
    EBT_Yellow
};

enum ELetter_Type {
    ELT_None,
    ELT_Circle
};

HWND Hwnd;
HPEN Green_Pen, Blue_Pen, Red_Pen, Yellow_Pen, Ellipse_Platform_Pen, Rectangle_Platform_Pen, Arc_Pen, BG_Pen, Ball_Pen;
HBRUSH Green_Brush, Blue_Brush, Red_Brush, Yellow_Brush, Ellipse_Platform_Brush, Rectangle_Platform_Brush, BG_Brush, Ball_Brush;
RECT Platform_Rect, Prev_Platform_Rect;
RECT Level_Area;
RECT Ball_Rect, Prev_Ball_Rect;

const int Global_Scale = 3;
const int Brick_Width = 15;
const int Brick_Height = 7;
const int Cell_Width = (Brick_Width + 1);
const int Cell_Height = (Brick_Height + 1);
const int Level_X_Offset = 8;
const int Level_Y_Offset = 6;
const int Level_X_Elems = 14;
const int Level_Y_Elems = 12;
const int Circle_Size = 7;
const int Platform_Y_Position = 185;
const int Platform_Height = 7;
const int Ball_Size = 4;
const int Max_X_Pos = Level_X_Offset + Cell_Width * Level_X_Elems - Ball_Size;
const int Max_Y_Pos = (180 - Platform_Height + Ball_Size);

int Inner_Platform_Width = 21;
int Platform_X_Position = 0;
int Platform_Step = Global_Scale * 2;
int Platform_Width = 28;
int Ball_X_Pos = 20;
int Ball_Y_Pos = 170;

double Ball_Speed = 3.0;
double Ball_Direction = M_PI - M_PI_4;

char Level_01[Level_X_Elems][Level_Y_Elems] = {
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

void Create_PenNBrush(unsigned char r, unsigned char g, unsigned char b, HPEN &pen, HBRUSH &brush) {
    pen = CreatePen(PS_SOLID, 0, RGB(r, g, b));
    brush = CreateSolidBrush(RGB(r, g, b));
}

void Redraw_Platform() {
    Prev_Platform_Rect = Platform_Rect;

    Platform_Rect.left = (Level_X_Offset + Platform_X_Position) * Global_Scale;
    Platform_Rect.top = Platform_Y_Position * Global_Scale;
    Platform_Rect.right = Platform_Rect.left + Platform_Width * Global_Scale;
    Platform_Rect.bottom = Platform_Rect.top + Platform_Height * Global_Scale;

    InvalidateRect(Hwnd, &Prev_Platform_Rect, FALSE);
    InvalidateRect(Hwnd, &Platform_Rect, FALSE);
}

void Init_Engine(HWND hwnd) {//It initializes game engine

    Hwnd = hwnd;
    Arc_Pen = CreatePen(PS_SOLID, 0, RGB(81, 82, 81));

    Create_PenNBrush(43, 97, 49, Green_Pen, Green_Brush);
    Create_PenNBrush(43, 63, 97, Blue_Pen, Blue_Brush);
    Create_PenNBrush(97, 43, 43, Red_Pen, Red_Brush);
    Create_PenNBrush(112, 101, 46, Yellow_Pen, Yellow_Brush);
    Create_PenNBrush(255, 255, 255, Ellipse_Platform_Pen, Ellipse_Platform_Brush);
    Create_PenNBrush(81, 82, 81, Rectangle_Platform_Pen, Rectangle_Platform_Brush);
    Create_PenNBrush(29, 31, 29, BG_Pen, BG_Brush);
    Create_PenNBrush(255, 255, 255, Ball_Pen, Ball_Brush);

    Level_Area.left = Level_X_Offset * Global_Scale;
    Level_Area.top = Level_Y_Offset * Global_Scale;
    Level_Area.right = Level_Area.left + Cell_Width * Level_X_Elems * Global_Scale;
    Level_Area.bottom = Level_Area.top + Cell_Height * Level_Y_Elems * Global_Scale;

    Redraw_Platform();

    SetTimer(Hwnd, Timer_ID, 50, 0);
}

void Draw_Brick(HDC hdc, int x, int y, EBrick_Type type) {//It draws game brick

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
    RoundRect(hdc, x * Global_Scale, y * Global_Scale,
        (x + Brick_Width) * Global_Scale,
        (y + Brick_Height) * Global_Scale, 3, 3);
}

void Change_BG_Color(EBrick_Type type, HPEN &front_pen, HBRUSH &front_brush, HPEN &back_pen, HBRUSH &back_brush) {
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

void Draw_Brick_Animation(HDC hdc, EBrick_Type type, ELetter_Type letter_type, int x, int y, int step) {//It draws falling of the bonuses

    XFORM xForm, old_xForm;
    double offset;
    double rotation_angle;
    int half_height = Brick_Height * Global_Scale / 2;

    HPEN front_pen, back_pen;
    HBRUSH front_brush, back_brush;

    step = step % 16;
    if (step < 8) {
        rotation_angle = 2.0 * M_PI / 16.0 * step;
    }
    else {
        rotation_angle = 2.0 * M_PI / 16.0 * (step - 8);
    }

    Change_BG_Color(type, front_pen, front_brush, back_pen, back_brush);

    if (step == 4 || step == 12) {
        
        //Draw front color
        SelectObject(hdc, front_pen);
        SelectObject(hdc, front_brush);

        Rectangle(hdc, x, y + half_height/2 + Global_Scale, x + Brick_Width * Global_Scale, y + half_height + Global_Scale);

        //Draw back color
        SelectObject(hdc, back_pen);
        SelectObject(hdc, back_brush);

        Rectangle(hdc, x, y + half_height/2 + Global_Scale, x + Brick_Width * Global_Scale, y + half_height);

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

        offset = 3.0 * (1.0 - fabs(xForm.eM22)) * (double)Global_Scale;

        Rectangle(hdc, 0, -half_height - (int)round(offset),  Brick_Width * Global_Scale, half_height - (int)round(offset));

        SelectObject(hdc, front_pen);
        SelectObject(hdc, front_brush);

        Rectangle(hdc, 0, -half_height,  Brick_Width * Global_Scale, half_height);

        if (step > 4 && step < 12) {
            if (letter_type == ELT_Circle) {
                SelectObject(hdc, back_pen);
                SelectObject(hdc, back_brush);
                Ellipse(hdc, 0 + 5 * Global_Scale, -half_height + 2, 0 + 10 * Global_Scale, half_height - 2);
            }
        }
        
        
        SetWorldTransform(hdc, &old_xForm);
    }
}

void Draw_Level(HDC hdc) {//It draws level map
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 12; j++) {
            Draw_Brick(hdc, Level_X_Offset + j * Cell_Width,
                Level_Y_Offset + i * Cell_Height, (EBrick_Type)Level_01[i][j]);
        }
    }
}

void Draw_Platform(HDC hdc, int x, int y) {//It draws platform

    SelectObject(hdc, BG_Pen);
    SelectObject(hdc, BG_Brush);

    Rectangle(hdc, Prev_Platform_Rect.left, Prev_Platform_Rect.top, Prev_Platform_Rect.right, Prev_Platform_Rect.bottom);

    SelectObject(hdc, Ellipse_Platform_Pen);
    SelectObject(hdc, Ellipse_Platform_Brush);

    Ellipse(hdc, x * Global_Scale, y * Global_Scale,
        (x + Circle_Size) * Global_Scale, (y + Circle_Size) * Global_Scale);
    Ellipse(hdc, (x + Inner_Platform_Width) * Global_Scale, y * Global_Scale,
        (x + Circle_Size + Inner_Platform_Width) * Global_Scale, (y + Circle_Size) * Global_Scale);

    /*SelectObject(hdc, Arc_Pen);

    Arc(hdc, (x + 1) * Global_Scale, (y + 1) * Global_Scale,
        (x + Circle_Size - 1) * Global_Scale, (y + Circle_Size - 1) * Global_Scale,
        (x + 2) * Global_Scale, (y + 1) * Global_Scale,
        (x + 1) * Global_Scale, (y + 3) * Global_Scale);*/

    SelectObject(hdc, Rectangle_Platform_Pen);
    SelectObject(hdc, Rectangle_Platform_Brush);

    RoundRect(hdc, (x + 4) * Global_Scale, (y + 1) * Global_Scale,
        (x + Inner_Platform_Width + 3) * Global_Scale,
        (y + 6) * Global_Scale, 3, 3);
}

void Draw_Ball(HDC hdc, RECT &paint_area) {

    //Clear BG
    SelectObject(hdc, BG_Pen);
    SelectObject(hdc, BG_Brush);

    Ellipse(hdc, Prev_Ball_Rect.left, Prev_Ball_Rect.top, Prev_Ball_Rect.right - 1, Prev_Ball_Rect.bottom - 1);

    //Draw the Ball
    SelectObject(hdc, Ball_Pen);
    SelectObject(hdc, Ball_Brush);

    Ellipse(hdc, Ball_Rect.left, Ball_Rect.top, Ball_Rect.right - 1, Ball_Rect.bottom - 1);
}

void Draw_Frame(HDC hdc, RECT &paint_area) {//It draws game screen(hdc - handle to device context)

    RECT destination_rect;

    if(IntersectRect(&destination_rect, &paint_area, &Level_Area))
    Draw_Level(hdc);

    if(IntersectRect(&destination_rect, &paint_area, &Platform_Rect))
    Draw_Platform(hdc, Level_X_Offset + Platform_X_Position, Platform_Y_Position);

    /*for (int i = 0; i < 16; i++) {
        Draw_Brick_Animation(hdc, EBT_Blue, ELT_Circle, 20 + i * (Brick_Width + 1) * Global_Scale, 100, i);
        Draw_Brick_Animation(hdc, EBT_Yellow, ELT_Circle, 20 + i * (Brick_Width + 1) * Global_Scale, 140, i);
        Draw_Brick_Animation(hdc, EBT_Green, ELT_Circle, 20 + i * (Brick_Width + 1) * Global_Scale, 180, i);
        Draw_Brick_Animation(hdc, EBT_Red, ELT_Circle, 20 + i * (Brick_Width + 1) * Global_Scale, 220, i);
    }*/
    if(IntersectRect(&destination_rect, &paint_area, &Ball_Rect))
    Draw_Ball(hdc, paint_area);
    
}

int On_Key_Down(EKey_Type key_type, int button) {
    switch (key_type) {
        case EKT_Left:
            Platform_X_Position -= Platform_Step;
            Redraw_Platform();
        break;
        case EKT_Right:
            Platform_X_Position += Platform_Step;
            Redraw_Platform();
        break;
        case EKT_Space:
            //Throw_Ball();
        break;
    }
    switch (button) {
    case Button_A:
        Platform_X_Position -= Platform_Step;
        Redraw_Platform();
        break;
    case Button_D:
        Platform_X_Position += Platform_Step;
        Redraw_Platform();
        break;
    }
    return 0;
}

void Move_Ball() {
    int next_x_pos, next_y_pos;

    Prev_Ball_Rect = Ball_Rect;

    next_x_pos = Ball_X_Pos + (int)Ball_Speed * cos(Ball_Direction);
    next_y_pos = Ball_Y_Pos - (int)Ball_Speed * sin(Ball_Direction);

    if (next_x_pos < 0) {
        next_x_pos = -next_x_pos;
        Ball_Direction = M_PI - Ball_Direction;
    }

    if (next_y_pos < Level_Y_Offset) {
        next_y_pos = Level_Y_Offset - (next_y_pos - Level_Y_Offset);
        Ball_Direction = -Ball_Direction;
    }

    if (next_x_pos > Max_X_Pos) {
        next_x_pos = Max_X_Pos - (next_x_pos - Max_X_Pos);
        Ball_Direction = M_PI - Ball_Direction;
    }

    if (next_y_pos > Max_Y_Pos) {
        next_y_pos = Max_Y_Pos - (next_y_pos - Max_Y_Pos);
        Ball_Direction -= 2 * Ball_Direction;
    }
    Ball_X_Pos = next_x_pos;
    Ball_Y_Pos = next_y_pos;



    Ball_Rect.left = (Ball_X_Pos + Level_X_Offset) * Global_Scale;
    Ball_Rect.top = (Ball_Y_Pos + Level_Y_Offset) * Global_Scale;
    Ball_Rect.right = Ball_Rect.left + Ball_Size * Global_Scale - 1;
    Ball_Rect.bottom = Ball_Rect.top + Ball_Size * Global_Scale - 1;

    InvalidateRect(Hwnd, &Prev_Ball_Rect, FALSE);
    InvalidateRect(Hwnd, &Ball_Rect, FALSE);
}

int On_Timer() {
    Move_Ball();
    return 0;
}