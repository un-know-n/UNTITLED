
#include "Engine.h"

char Level_01[CLevel::Level_X_Elems][CLevel::Level_Y_Elems] = {
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

CBall::CBall() : Ball_X_Pos(20), Ball_Y_Pos(170), Ball_Speed(3.0), 
Ball_Direction(M_PI - M_PI_4)
{//Constructor
}

void CBall::Init_Ball(){

    CsEngine::Create_PenNBrush(255, 255, 255, Ball_Pen, Ball_Brush);
}

void CBall::Draw_Ball(HDC hdc, RECT &paint_area, CsEngine *engine) {
    RECT destination_rect;
    if(!IntersectRect(&destination_rect, &paint_area, &Ball_Rect))
        return;

    //Clear BG
    SelectObject(hdc, engine->BG_Pen);
    SelectObject(hdc, engine->BG_Brush);

    Ellipse(hdc, Prev_Ball_Rect.left, Prev_Ball_Rect.top, Prev_Ball_Rect.right - 1, Prev_Ball_Rect.bottom - 1);

    //Draw the Ball
    SelectObject(hdc, Ball_Pen);
    SelectObject(hdc, Ball_Brush);

    Ellipse(hdc, Ball_Rect.left, Ball_Rect.top, Ball_Rect.right - 1, Ball_Rect.bottom - 1);
}

void CBall::Move_Ball(CsEngine *engine, CLevel *level, CsPlatform *platform) {
    int next_x_pos, next_y_pos;
    Prev_Ball_Rect = Ball_Rect;

    //Calculating new coords
    next_x_pos = Ball_X_Pos + (int)(Ball_Speed * cos(Ball_Direction));
    next_y_pos = Ball_Y_Pos - (int)(Ball_Speed * sin(Ball_Direction));

    //if we`ve collided with wall
    if (next_x_pos < CLevel::Level_X_Offset) {
        next_x_pos = CLevel::Level_X_Offset - (CLevel::Level_X_Offset - next_x_pos);
        Ball_Direction = M_PI - Ball_Direction;
    }

    if (next_y_pos < 0) {
        next_y_pos = CsBorder::Border_Y_Offset - (CsBorder::Border_Y_Offset - next_y_pos);
        Ball_Direction = -Ball_Direction;
    }

    if (next_x_pos > CsEngine::Max_X_Pos + CLevel::Level_X_Offset) {
        next_x_pos = CLevel::Level_X_Offset - (CLevel::Level_X_Offset - next_x_pos);
        Ball_Direction = M_PI - Ball_Direction;
    }

    if (next_y_pos > CsEngine::Max_Y_Pos) {
        next_y_pos = CLevel::Level_X_Offset - (CLevel::Level_X_Offset - next_y_pos);
        Ball_Direction = -Ball_Direction;
    }

    //If struck with platform

    if (next_y_pos > CsPlatform::Platform_Y_Position - 12) {
        if (next_x_pos >= platform->Platform_X_Position && next_x_pos <= platform->Platform_X_Position + platform->Platform_Width) {
            next_y_pos = CsPlatform::Platform_Y_Position - (CsPlatform::Platform_Y_Position - next_y_pos);
            Ball_Direction = -Ball_Direction;
        }

    }

    level->Check_Ball_Colision(next_y_pos, Ball_Direction);

    //Ball translation
    Ball_X_Pos = next_x_pos;
    Ball_Y_Pos = next_y_pos;

    Ball_Rect.left =  Ball_X_Pos * CsEngine::Global_Scale;
    Ball_Rect.top = (CLevel::Level_Y_Offset + Ball_Y_Pos) * CsEngine::Global_Scale;
    Ball_Rect.right = Ball_Rect.left + Ball_Size * CsEngine::Global_Scale;
    Ball_Rect.bottom = Ball_Rect.top + Ball_Size * CsEngine::Global_Scale;

    //Redraw ball
    InvalidateRect(engine->Hwnd, &Prev_Ball_Rect, FALSE);
    InvalidateRect(engine->Hwnd, &Ball_Rect, FALSE);
}


void CsPlatform::Init_Platform(){
    CsEngine::Create_PenNBrush(255, 255, 255, Ellipse_Platform_Pen, Ellipse_Platform_Brush);
    CsEngine::Create_PenNBrush(81, 82, 81, Rectangle_Platform_Pen, Rectangle_Platform_Brush);
}


void CLevel::Init_Level(){
    CsEngine::Create_PenNBrush(43, 97, 49, Green_Pen, Green_Brush);
    CsEngine::Create_PenNBrush(43, 63, 97, Blue_Pen, Blue_Brush);
    CsEngine::Create_PenNBrush(97, 43, 43, Red_Pen, Red_Brush);
    CsEngine::Create_PenNBrush(112, 101, 46, Yellow_Pen, Yellow_Brush);

    Level_Area.left = Level_X_Offset * CsEngine::Global_Scale;
    Level_Area.top = Level_Y_Offset * CsEngine::Global_Scale;
    Level_Area.right = Level_Area.left + Cell_Width * Level_X_Elems * CsEngine::Global_Scale;
    Level_Area.bottom = Level_Area.top + Cell_Height * Level_Y_Elems * CsEngine::Global_Scale;
}

void CsBorder::Init_Border(){
    CsEngine::Create_PenNBrush(133, 13, 37, Border_Main_Pen, Border_Main_Brush);
    CsEngine::Create_PenNBrush(255, 255, 255, Border_White_Pen, Border_White_Brush);
}


CsPlatform::CsPlatform() : Platform_X_Position(0), Platform_Width(28)
{//Constructor
}

CsEngine::CsEngine() : Inner_Platform_Width(21), Platform_Step(6)
{//Constructor
}

void CsEngine::Create_PenNBrush(unsigned char r, unsigned char g, unsigned char b, HPEN &pen, HBRUSH &brush) {
    pen = CreatePen(PS_SOLID, 0, RGB(r, g, b));
    brush = CreateSolidBrush(RGB(r, g, b));
}

void CsPlatform::Redraw_Platform(CsEngine *engine) {
    Prev_Platform_Rect = Platform_Rect;

    Platform_Rect.left = (CLevel::Level_X_Offset + Platform_X_Position) * CsEngine::Global_Scale;
    Platform_Rect.top = Platform_Y_Position * CsEngine::Global_Scale;
    Platform_Rect.right = Platform_Rect.left + Platform_Width * CsEngine::Global_Scale;
    Platform_Rect.bottom = Platform_Rect.top + Platform_Height * CsEngine::Global_Scale;

    InvalidateRect(engine->Hwnd, &Prev_Platform_Rect, FALSE);
    InvalidateRect(engine->Hwnd, &Platform_Rect, FALSE);
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
    RoundRect(hdc, x * CsEngine::Global_Scale, y * CsEngine::Global_Scale,
        (x + Brick_Width) * CsEngine::Global_Scale,
        (y + Brick_Height) * CsEngine::Global_Scale, 3, 3);
}

void CsEngine::Change_BG_Color(EBrick_Type type, HPEN &front_pen, HBRUSH &front_brush, HPEN &back_pen, HBRUSH &back_brush) {
    //We can change only existing bricks
    if (!(type == EBT_Blue || type == EBT_Green || type == EBT_Red || type == EBT_Yellow)) return;
    else {
        if (type == EBT_Blue) {
            front_pen = Level.Blue_Pen;
            front_brush = Level.Blue_Brush;

            back_pen = Level.Yellow_Pen;
            back_brush = Level.Yellow_Brush;
        }
        else if (type == EBT_Yellow) {
            front_pen = Level.Yellow_Pen;
            front_brush = Level.Yellow_Brush;

            back_pen = Level.Blue_Pen;
            back_brush = Level.Blue_Brush;
        }
        else if (type == EBT_Green) {
            front_pen = Level.Green_Pen;
            front_brush = Level.Green_Brush;

            back_pen = Level.Red_Pen;
            back_brush = Level.Red_Brush;
        }
        else if (type == EBT_Red) {
            front_pen = Level.Red_Pen;
            front_brush = Level.Red_Brush;

            back_pen = Level.Green_Pen;
            back_brush = Level.Green_Brush;
        }
    }
}

void CLevel::Draw_Brick_Animation(HDC hdc, EBrick_Type type, ELetter_Type letter_type, int x, int y, int step, CsEngine *engine) {//It draws falling of the bonuses

    XFORM xForm, old_xForm;
    double offset;
    double rotation_angle;
    int half_height = Brick_Height * CsEngine::Global_Scale / 2;

    HPEN front_pen, back_pen;
    HBRUSH front_brush, back_brush;

    step = step % 16;
    if (step < 8) {
        rotation_angle = 2.0 * M_PI / 16.0 * step;
    }
    else {
        rotation_angle = 2.0 * M_PI / 16.0 * (step - 8);
    }

    engine->Change_BG_Color(type, front_pen, front_brush, back_pen, back_brush);

    if (step == 4 || step == 12) {
        
        //Draw front color
        SelectObject(hdc, front_pen);
        SelectObject(hdc, front_brush);

        Rectangle(hdc, x, y + half_height/2 + CsEngine::Global_Scale, x + Brick_Width * CsEngine::Global_Scale, y + half_height + CsEngine::Global_Scale);

        //Draw back color
        SelectObject(hdc, back_pen);
        SelectObject(hdc, back_brush);

        Rectangle(hdc, x, y + half_height/2 + CsEngine::Global_Scale, x + Brick_Width * CsEngine::Global_Scale, y + half_height);

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

        offset = 3.0 * (1.0 - fabs(xForm.eM22)) * (double)CsEngine::Global_Scale;

        Rectangle(hdc, 0, -half_height - (int)round(offset),  Brick_Width * CsEngine::Global_Scale, half_height - (int)round(offset));

        SelectObject(hdc, front_pen);
        SelectObject(hdc, front_brush);

        Rectangle(hdc, 0, -half_height,  Brick_Width * CsEngine::Global_Scale, half_height);

        if (step > 4 && step < 12) {
            if (letter_type == ELT_Circle) {
                SelectObject(hdc, back_pen);
                SelectObject(hdc, back_brush);
                Ellipse(hdc, 0 + 5 * CsEngine::Global_Scale, -half_height + 2, 0 + 10 * CsEngine::Global_Scale, half_height - 2);
            }
        }
        
        
        SetWorldTransform(hdc, &old_xForm);
    }
}

void CLevel::Draw_Level(HDC hdc, RECT &paint_area) {//It draws level map

    RECT destination_rect;

    if(!(IntersectRect(&destination_rect, &paint_area, &Level_Area))) return;

    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 12; j++) {
            Draw_Brick(hdc, Level_X_Offset + j * Cell_Width,
                Level_Y_Offset + i * Cell_Height, (EBrick_Type)Level_01[i][j]);
        }
    }
}

void CsPlatform::Draw_Platform(HDC hdc, int x, int y, CsEngine *engine, RECT &paint_area) {//It draws platform
    RECT destination_rect;

    if(!(IntersectRect(&destination_rect, &paint_area, &Platform_Rect))) return;

    SelectObject(hdc, engine->BG_Pen);
    SelectObject(hdc, engine->BG_Brush);

    Rectangle(hdc, Prev_Platform_Rect.left, Prev_Platform_Rect.top, Prev_Platform_Rect.right, Prev_Platform_Rect.bottom);

    SelectObject(hdc, Ellipse_Platform_Pen);
    SelectObject(hdc, Ellipse_Platform_Brush);

    Ellipse(hdc, (x+1) * CsEngine::Global_Scale, (y+1) * CsEngine::Global_Scale,
        (x + 1 + Circle_Size) * CsEngine::Global_Scale, (y + 1 + Circle_Size) * CsEngine::Global_Scale);
    Ellipse(hdc, (x + 1 + engine->Inner_Platform_Width) * CsEngine::Global_Scale, (y+1) * CsEngine::Global_Scale,
        (x + 1 + Circle_Size + engine->Inner_Platform_Width) * CsEngine::Global_Scale, (y + 1 + Circle_Size) * CsEngine::Global_Scale);

    /*SelectObject(hdc, Arc_Pen);

    Arc(hdc, (x + 1) * CsEngine::Global_Scale, (y + 1) * CsEngine::Global_Scale,
        (x + Circle_Size - 1) * CsEngine::Global_Scale, (y + Circle_Size - 1) * CsEngine::Global_Scale,
        (x + 2) * CsEngine::Global_Scale, (y + 1) * CsEngine::Global_Scale,
        (x + 1) * CsEngine::Global_Scale, (y + 3) * CsEngine::Global_Scale);*/

    SelectObject(hdc, Rectangle_Platform_Pen);
    SelectObject(hdc, Rectangle_Platform_Brush);

    RoundRect(hdc, (x + 4) * CsEngine::Global_Scale, (y + 1) * CsEngine::Global_Scale,
        (x + engine->Inner_Platform_Width + 3) * CsEngine::Global_Scale,
        (y + 6) * CsEngine::Global_Scale, 3, 3);
}



void CsBorder::Draw_Border_Element(HDC hdc, int x, int y, BOOL is_vertical) {
    //Draw main line
    SelectObject(hdc, Border_Main_Pen);
    SelectObject(hdc, Border_Main_Brush);

    if (is_vertical) 
        Rectangle(hdc, (x + 1) * CsEngine::Global_Scale, y * CsEngine::Global_Scale, (x + 4) * CsEngine::Global_Scale, (y + 4) * CsEngine::Global_Scale);
    else 
        Rectangle(hdc, x * CsEngine::Global_Scale, (y + 1) * CsEngine::Global_Scale, (x + 4) * CsEngine::Global_Scale, (y + 4) * CsEngine::Global_Scale);

    //White line
    SelectObject(hdc, Border_White_Pen);
    SelectObject(hdc, Border_White_Brush);

    if(is_vertical)
        Rectangle(hdc, x * CsEngine::Global_Scale, y * CsEngine::Global_Scale, (x + 1) * CsEngine::Global_Scale - 1, (y + 4) * CsEngine::Global_Scale);
    else
        Rectangle(hdc, x * CsEngine::Global_Scale, y * CsEngine::Global_Scale, (x + 4) * CsEngine::Global_Scale, (y + 1) * CsEngine::Global_Scale - 1);

    //White inner-dot
    SelectObject(hdc, Border_White_Pen);
    SelectObject(hdc, Border_White_Brush);

    if(is_vertical)
        Rectangle(hdc, (x + 2) * CsEngine::Global_Scale, (y + 1) * CsEngine::Global_Scale, (x + 3) * CsEngine::Global_Scale, (y + 2) * CsEngine::Global_Scale);
    else
        Rectangle(hdc, (x + 2) * CsEngine::Global_Scale, (y + 2) * CsEngine::Global_Scale, (x + 3) * CsEngine::Global_Scale, (y + 3) * CsEngine::Global_Scale);
    
}

void CsBorder::Draw_Border(HDC hdc, RECT &paint_area) {

    //Drawing left/right border
    for(int i = 0; i < 50; i++)
        Draw_Border_Element(hdc, 2, 1 + i * 4, TRUE);

    for(int i = 0; i < 50; i++)
        Draw_Border_Element(hdc, 201, 1 + i * 4, TRUE);

    //Drawing top border
    for(int i = 0; i < 50; i++)
        Draw_Border_Element(hdc, 3 + i * 4, 0, FALSE);
}

void CsPlatform::Platform_Condition() {
    if (Platform_X_Position < Min_Platform_X-2)
        Platform_X_Position = Min_Platform_X-2;
    if (Platform_X_Position > Max_Platform_X+1)
        Platform_X_Position = Max_Platform_X+1;
}

void CLevel::Check_Ball_Colision(int &next_y_pos, double &ball_direction) {

    //If struck woth bricks

    int brick_y_pos = Level_X_Elems * Cell_Height;

    for (int i = Level_X_Elems - 1; i >= 0; i--) {
        for (int j = 0; j < Level_Y_Elems; j++) {
            if (Level_01[i][j] == 0) continue;
            else {
                if (next_y_pos < brick_y_pos) {
                    next_y_pos = brick_y_pos - (next_y_pos - brick_y_pos);
                    ball_direction = -ball_direction;
                }
            }
        }
        brick_y_pos -= Cell_Height;
    }
}

void CsEngine::Init_Engine(HWND hwnd) {//It initializes game engine

    Hwnd = hwnd;
    //Arc_Pen = CreatePen(PS_SOLID, 0, RGB(81, 82, 81));

    Create_PenNBrush(29, 31, 29, BG_Pen, BG_Brush);

    Level.Init_Level();
    Ball.Init_Ball();
    Platform.Init_Platform();
    Border.Init_Border();

    Platform.Redraw_Platform(this);

    SetTimer(Hwnd, Timer_ID, 50, 0);
}

void CsEngine::Draw_Frame(HDC hdc, RECT &paint_area) {//It draws game screen(hdc - handle to device context)

    RECT destination_rect;

    Level.Draw_Level(hdc, paint_area);
    
    Platform.Draw_Platform(hdc, CLevel::Level_X_Offset + Platform.Platform_X_Position, Platform.Platform_Y_Position, this, paint_area);

    /*for (int i = 0; i < 16; i++) {
    Draw_Brick_Animation(hdc, EBT_Blue, ELT_Circle, 20 + i * (Brick_Width + 1) * Global_Scale, 100, i);
    Draw_Brick_Animation(hdc, EBT_Yellow, ELT_Circle, 20 + i * (Brick_Width + 1) * Global_Scale, 140, i);
    Draw_Brick_Animation(hdc, EBT_Green, ELT_Circle, 20 + i * (Brick_Width + 1) * Global_Scale, 180, i);
    Draw_Brick_Animation(hdc, EBT_Red, ELT_Circle, 20 + i * (Brick_Width + 1) * Global_Scale, 220, i);
    }*/
    Ball.Draw_Ball(hdc, paint_area, this);

    Border.Draw_Border(hdc, paint_area);
}

int CsEngine::On_Key_Down(EKey_Type key_type, int button) {
    switch (key_type) {
    case EKT_Left:
        Platform.Platform_X_Position -= Platform_Step;
        Platform.Platform_Condition();
        Platform.Redraw_Platform(this);
        break;
    case EKT_Right:
        Platform.Platform_X_Position += Platform_Step;
        Platform.Platform_Condition();
        Platform.Redraw_Platform(this);
        break;
    case EKT_Space:
        //Throw_Ball();
        break;
    }
    switch (button) {
    case Button_A:
        Platform.Platform_X_Position -= Platform_Step;
        Platform.Platform_Condition();
        Platform.Redraw_Platform(this);
        break;
    case Button_D:
        Platform.Platform_X_Position += Platform_Step;
        Platform.Platform_Condition();
        Platform.Redraw_Platform(this);
        break;
    }
    return 0;
}

int CsEngine::On_Timer() {
    Ball.Move_Ball(this, &Level, &Platform);
    return 0;
}