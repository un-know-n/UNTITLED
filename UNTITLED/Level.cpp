
#include "Level.h"

char Level_01[CsConfig::Level_X_Elems][CsConfig::Level_Y_Elems] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0,
    0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0,
    0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
    0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


//          CLEVEL

CLevel::CLevel() : Fade(EBT_Blue), Green_Brush(0), Blue_Brush(0), Red_Brush(0), Yellow_Brush(0),
Green_Pen(0), Blue_Pen(0), Red_Pen(0), Yellow_Pen(0), Level_Area{}
{//Constructor
}

void CLevel::Init(){
    CsConfig::Create_PenNBrush(CsConfig::Green_Brick, Green_Pen, Green_Brush);
    CsConfig::Create_PenNBrush(CsConfig::Blue_Brick, Blue_Pen, Blue_Brush);
    CsConfig::Create_PenNBrush(CsConfig::Red_Brick, Red_Pen, Red_Brush);
    CsConfig::Create_PenNBrush(CsConfig::Yellow_Brick, Yellow_Pen, Yellow_Brush);

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

    /*Rectangle(hdc, x * CsConfig::Extent, y * CsConfig::Extent,
        (x + CsConfig::Brick_Width) * CsConfig::Extent,
        (y + CsConfig::Brick_Height) * CsConfig::Extent);*/
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

    //Translation of old drawing area to new, which can be rotated in every angle we want to
    XFORM xForm, old_xForm;
    double offset;
    double rotation_angle;
    int half_height = CsConfig::Brick_Height * CsConfig::Extent / 2;

    HPEN front_pen, back_pen;
    HBRUSH front_brush, back_brush;

    //Check if rotation step is more than 16 -> change it
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

        Rectangle(hdc, x, y + half_height/2 + CsConfig::Extent, x + CsConfig::Brick_Width * CsConfig::Extent, y + half_height + CsConfig::Extent);

        //Draw back color
        SelectObject(hdc, back_pen);
        SelectObject(hdc, back_brush);

        Rectangle(hdc, x, y + half_height/2 + CsConfig::Extent, x + CsConfig::Brick_Width * CsConfig::Extent, y + half_height);

    }
    else {
        //Editing the matrix of the drawing area
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

        //Return it to the normal values
        SetWorldTransform(hdc, &old_xForm);
    }
}

void CLevel::Draw(HDC hdc, RECT &paint_area) {
    //It draws level map

    RECT destination_rect;

    if(!(IntersectRect(&destination_rect, &paint_area, &Level_Area))) return;

    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 12; j++) {
            Draw_Brick(hdc, CsConfig::Level_X_Offset + j * CsConfig::Cell_Width,
                CsConfig::Level_Y_Offset + i * CsConfig::Cell_Height, (EBrick_Type)Level_01[i][j]);
        }
    }

    //Fade.Draw(hdc);
}

bool CLevel::Check_Colision(double next_x_pos, double next_y_pos, CBall* ball) {
    //If struck with bricks

    double x, y;
    double direction = ball->Get_Direction();
    //int brick_x_pos = CsConfig::Level_Y_Elems * CsConfig::Cell_Width;

    for (int i = CsConfig::Level_X_Elems - 1; i >= 0; i--) {
        Current_Brick_Top_Y_Pos = i * CsConfig::Cell_Height;
        Current_Brick_Bottom_Y_Pos = Current_Brick_Top_Y_Pos + CsConfig::Brick_Height; //CsConfig::Level_X_Elems * CsConfig::Cell_Height
        
        for (int j = 0; j < CsConfig::Level_Y_Elems; j++) {
            if (Level_01[i][j] == 0) continue;

            Current_Brick_Left_Side = CsConfig::Level_X_Offset + j * CsConfig::Cell_Width;
            Current_Brick_Right_Side = Current_Brick_Left_Side + CsConfig::Brick_Width;

            if (Is_Horizontal_Check(next_x_pos, next_y_pos)) {
                if (Check_Horizontal_Hit(i, j,next_x_pos, next_y_pos, ball)) return true;
                if (Check_Vertical_Hit(i, j, next_x_pos, next_y_pos, ball)) return true;
            }
            else {
                if (Check_Vertical_Hit(i, j, next_x_pos, next_y_pos, ball)) return true;
                if (Check_Horizontal_Hit(i, j, next_x_pos, next_y_pos, ball)) return true;
            }

            //if (next_y_pos - ball->Radius / 2 < Current_Brick_Bottom_Y_Pos) {
                ////next_y_pos = Current_Brick_Bottom_Y_Pos - (next_y_pos - Current_Brick_Bottom_Y_Pos);
                //ball->Ball_Direction = -ball->Ball_Direction;
                //return true;
            //}
        }
        Current_Brick_Bottom_Y_Pos -= CsConfig::Cell_Height;
    }

    return false;
}

bool CLevel::Is_Horizontal_Check(double next_x_pos, double next_y_pos) {
    double horizontal_min_line, vertical_min_line, another_min_line;

    //We`re making lines which can influence on future type of examination

    horizontal_min_line = fabs(next_x_pos - Current_Brick_Left_Side);
    another_min_line = fabs(next_x_pos - Current_Brick_Right_Side);

    if (another_min_line < horizontal_min_line) another_min_line = horizontal_min_line;

    vertical_min_line = fabs(next_y_pos - Current_Brick_Top_Y_Pos);
    another_min_line = fabs(next_y_pos - Current_Brick_Bottom_Y_Pos);

    if (another_min_line < vertical_min_line) vertical_min_line = another_min_line;

    if (horizontal_min_line <= vertical_min_line) return true;
    else return false;
}

bool CLevel::Check_Vertical_Hit(int level_y, int level_x, double next_x_pos, double next_y_pos, CBall* ball) {
    double direction = ball->Get_Direction();
    //Check bottom line of the brick
    if (direction > 0 && direction < M_PI) {
        if (Circle_Horizontal_Hit(next_y_pos - Current_Brick_Bottom_Y_Pos, next_x_pos, Current_Brick_Left_Side, Current_Brick_Right_Side, ball->Radius)) {
            //Check if we can reflect our ball down
            if (level_y < CsConfig::Level_Y_Elems - 1 && Level_01[level_y + 1][level_x] == 0) {
                ball->Reflect(false);
                return true;
            }
            else return false;
        }
    }

    //Check upper line of the brick
    if (direction >= M_PI && direction <= 2 * M_PI) {
        if (Circle_Horizontal_Hit(next_y_pos - Current_Brick_Top_Y_Pos, next_x_pos, Current_Brick_Left_Side, Current_Brick_Right_Side, ball->Radius)) {
            //Check if we can reflect our ball up
            if (level_y > 0 && Level_01[level_y - 1][level_x] == 0) {
                ball->Reflect(false);
                return true;
            }
            else return false;
        }
    }

    return false;
}

bool CLevel::Check_Horizontal_Hit(int level_y, int level_x, double next_x_pos, double next_y_pos, CBall* ball) {
    double direction = ball->Get_Direction();
    //Check left side of the brick
    if (direction > 0.0 && direction < M_PI_2 || direction > 3 * M_PI_2 && direction < 2 * M_PI) {
        if (Circle_Horizontal_Hit(Current_Brick_Left_Side - next_x_pos, next_y_pos, Current_Brick_Top_Y_Pos, Current_Brick_Bottom_Y_Pos, ball->Radius)) {
            //Check if we can reflect our ball to the left side
            if (level_x > 0 && Level_01[level_y][level_x - 1] == 0) {
                ball->Reflect(true);
                return true;
            }
            else return false;
        }
    }

    //Check right side of the brick
    if (direction > M_PI_2 && direction < 3 * M_PI_2) {
        if (Circle_Horizontal_Hit(Current_Brick_Right_Side - next_x_pos, next_y_pos, Current_Brick_Top_Y_Pos, Current_Brick_Bottom_Y_Pos, ball->Radius)) {
            //Check if we can reflect our ball to the right side
            if (level_x < CsConfig::Level_X_Elems && Level_01[level_y][level_x + 1] == 0) {
                ball->Reflect(true);
                return true;
            }
            else return false;
        }
    }
    return false;
}

bool CLevel::Circle_Horizontal_Hit(double y, double next_x_pos, double left_x, double right_x, double radius) {
    //Check if we`ve collided with horizontal line of brick(from left_x to right_x)
    //x^2 + y^2 = R^2
    //x = sqrt(R^2 - y^2)
    //y = sqrt(R^2 - x^2)

    double x;
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