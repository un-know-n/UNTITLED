
#include "Platform.h"


//          CSPLATFORM

Platform::~Platform() {
    delete[] Platform_Scan;
}

Platform::Platform() : X_Position(0), Y_Position(Config::Platform_Y_Position), Width(28), Height(7), Inner_Platform_Width(21),
Ellipse_Platform_Brush(0), Ellipse_Platform_Pen(0), Platform_State(PS_StartGame), Step_Up(0), Platform_Step(3),
Platform_Rect{}, Platform_Normal_Width(Width * Config::Extent), Platform_Normal_Height(Height * Config::Extent),
Ellipse_Platform_Pen_Color(255, 255, 255), Rectangle_Platform_Pen_Color(81, 82, 81)
{//Constructor
    X_Position = (Config::Max_X) / 2 + 2 * Config::Extent;
}

void Platform::Init(){
    Config::Create_PenNBrush(255, 255, 255, Ellipse_Platform_Pen, Ellipse_Platform_Brush);
    Config::Create_PenNBrush(81, 82, 81, Rectangle_Platform_Pen, Rectangle_Platform_Brush);
}

void Platform::Redraw() {
    Prev_Platform_Rect = Platform_Rect;
    int temp;
    if (Platform_State == PS_StartGame) temp = Config::Circle_Size;
    else temp = Width;

    Platform_Rect.left = (Config::Level_X_Offset + X_Position) * Config::Extent;
    Platform_Rect.top = Config::Platform_Y_Position * Config::Extent;
    Platform_Rect.right = Platform_Rect.left + temp * Config::Extent;
    Platform_Rect.bottom = Platform_Rect.top + Config::Platform_Height * Config::Extent;

    if(Platform_State == PS_EndGame || Platform_State == PS_StartGame){
        Prev_Platform_Rect.bottom = 205 * Config::Extent;
    }
    if (Platform_State == PS_StartGame) {
        X_Position = (Config::Max_X) / 2 + 2 * Config::Extent;
    }

    InvalidateRect(Config::Hwnd, &Prev_Platform_Rect, FALSE);
    InvalidateRect(Config::Hwnd, &Platform_Rect, FALSE);
}

void Platform::Draw(HDC hdc, RECT &paint_area) {

    RECT destination_rect;
    if (!(IntersectRect(&destination_rect, &paint_area, &Platform_Rect))) return;

    switch (Platform_State) {
    case PS_Normal:
        Draw_Normal(hdc, paint_area);
        break;

    case PS_EndGame:
        Draw_EndGame(hdc, paint_area);
        break;

    case PS_StartGame:
        Draw_StartGame(hdc, paint_area);
        break;

    case PS_Extension:
        Draw_Extension(hdc, paint_area);
        break;
    }
}

void Platform::Draw_Normal(HDC hdc, RECT &paint_area){
    //if there`s collision with paint area -> draw the platform
    int x = Config::Level_X_Offset + X_Position;
    int y = Config::Platform_Y_Position;
    int inner_pl_width = Inner_Platform_Width;
    int offset = 0;

    Clear_BG(hdc);

    SelectObject(hdc, Ellipse_Platform_Pen);
    SelectObject(hdc, Ellipse_Platform_Brush);

    Ellipse(hdc, (x+1) * Config::Extent, (y+1) * Config::Extent,
        (x + 1 + Config::Circle_Size) * Config::Extent - 1, (y + 1 + Config::Circle_Size) * Config::Extent - 1);
    Ellipse(hdc, (x + 1 + inner_pl_width) * Config::Extent, (y+1) * Config::Extent,
        (x + 1 + Config::Circle_Size + inner_pl_width) * Config::Extent - 1, (y + 1 + Config::Circle_Size) * Config::Extent - 1);

    SelectObject(hdc, Rectangle_Platform_Pen);
    SelectObject(hdc, Rectangle_Platform_Brush);

    RoundRect(hdc, (x + 4) * Config::Extent, (y + 1) * Config::Extent,
        (x + inner_pl_width + 3) * Config::Extent - 1,
        (y + 6) * Config::Extent - 1, 3, 3);

    x *= Config::Extent;
    y *= Config::Extent;

    if (Platform_Scan == 0) {
        Platform_Scan = new int[Platform_Normal_Width * Platform_Normal_Height];

        for (int i = 0; i < Platform_Normal_Height; i++) {
            for (int j = 0; j < Platform_Normal_Width; j++) {
                Platform_Scan[offset++] = GetPixel(hdc, x + j, y + i);
            }
        }
    }
}

void Platform::Draw_EndGame(HDC hdc, RECT &paint_area){
    
     Inner_Platform_Width = 21;
     int x, y, y_offset;
     int column_counter = 0;
     int area_width = Width * Config::Extent;
     //int area_height = Config::Platform_Height * Config::Extent;
     const int max_position = Config::Max_Y_Pos * Config::Extent;
     COLORREF pixel;
     COLORREF bg_pixel = RGB(Config::BG_Color.R, Config::BG_Color.G, Config::BG_Color.B);
     HPEN color_pen;
     int column_length = 0;

     for (int i = 0; i < area_width; i++) {
         if (EndGame_Elem_Position[i] > max_position) continue;

         ++column_counter;

         y_offset = rand() % 4 + 1;
         x = Platform_Rect.left + i;

         /*for (int j = 0; j < Platform_Normal_Height; j++) {

             y = EndGame_Elem_Position[i] + j;

             pixel = GetPixel(hdc, x, y);
             SetPixel(hdc, x, y + y_offset, pixel);
         }
         for (int j = 0; j < y_offset; j++) {
             y = EndGame_Elem_Position[i];
             SetPixel(hdc, x, y, bg_pixel);
         }*/

         ////////// PLACE TO DO CODE ------------- MUST BE FIXED!

         
         int j = 0;
         y = EndGame_Elem_Position[i];

         MoveToEx(hdc, x, y, 0);

         while (Get_Platform_Column_Color(i, j, color_pen, column_length)) {

             SelectObject(hdc, color_pen);
             LineTo(hdc, x, y + column_length);

             y += column_length;
             j += column_length;
         }

         y = EndGame_Elem_Position[i];
         MoveToEx(hdc, x, y, 0);
         SelectObject(hdc, Config::BG_Pen);
         LineTo(hdc, x, y + y_offset);

         ////////////////////////////

         EndGame_Elem_Position[i] += y_offset;
     }
     
     if (column_counter == 0) {
         Platform_State = PS_None;
         Sleep(200);
     }

}

bool Platform::Get_Platform_Column_Color(int x, int y, HPEN& color_pen, int& column_length) {

    int offset = y * Platform_Normal_Width + x;
    int color = 0;

    if (y > Platform_Normal_Height) return false;

    for (int i = y; i < Platform_Normal_Height; i++) {
        if (i == y) {
            color = Platform_Scan[offset];
            column_length = 1;
        }
        else {
            if (color == Platform_Scan[offset]) {
                column_length++;
            }
            else break;
        }
        
        offset += Platform_Normal_Width;
    }

    if (color == Ellipse_Platform_Pen_Color.Get_RGB()) {
        color_pen = Ellipse_Platform_Pen;
    }
    else if (color == Rectangle_Platform_Pen_Color.Get_RGB()) {
        color_pen = Rectangle_Platform_Pen;
    }
    else if (color == Config::BG_Color.Get_RGB()) {
        color_pen = Config::BG_Pen;
    }
    else color_pen = 0;

    return true;
}

void Platform::Draw_StartGame(HDC hdc, RECT& paint_area) {
    int x = (Config::Level_X_Offset + X_Position) * Config::Extent;
    int y = (Config::Level_Y_Offset * Config::Extent + Y_Position) * Config::Extent;
    int normal_coords = Config::Circle_Size * Config::Extent;
    XFORM xForm, old_xForm;
    double alpha;

    Clear_BG(hdc);

    SelectObject(hdc, Ellipse_Platform_Pen);
    SelectObject(hdc, Ellipse_Platform_Brush);

    Ellipse(hdc, x, y, x + normal_coords, y + normal_coords);

    //Rotate view

    alpha = 2.0 * M_PI / (double)(Max_Rotation) * (double)(Step_Up);
    ++Step_Up;

    //SetGraphicsMode(hdc, GM_ADVANCED);
    xForm.eM11 = (float)cos(alpha);
    xForm.eM12 = (float)sin(alpha);
    xForm.eM21 = (float)-sin(alpha);
    xForm.eM22 = (float)cos(alpha);
    xForm.eDx = (float)x + normal_coords / 2;
    xForm.eDy = (float)y + normal_coords / 2;
    GetWorldTransform(hdc, &old_xForm);
    SetWorldTransform(hdc, &xForm);

    SelectObject(hdc, Config::BG_Pen);
    SelectObject(hdc, Config::BG_Brush);

    Rectangle(hdc,-Config::Extent / 2, -normal_coords / 2, Config::Extent / 2, normal_coords / 2);

    if (y > Config::Platform_Y_Position * Config::Extent) --Y_Position;
    else {

        Platform_State = PS_Extension;
        Inner_Platform_Width = 1; // PROBLEM!!!
        
    }

    if (Step_Up >= Max_Rotation) Step_Up -= Max_Rotation;
    
    SetWorldTransform(hdc, &old_xForm);
}

void Platform::Draw_Extension(HDC hdc, RECT& paint_area) {
    Draw_Normal(hdc, paint_area);
            
    if (Inner_Platform_Width <= 21) {
        --X_Position;
        Inner_Platform_Width += 3;
    }
    else {
        Platform_State = PS_Ready;
        Redraw();
        Inner_Platform_Width = 21;

    }    
}

EPlatform_State Platform::Get_State() {
    return Platform_State;
}

void Platform::Set_State(EPlatform_State platform_state) {
    //if (Platform_State == platform_state) return;
    if (platform_state == PS_EndGame) {
        int length = sizeof(EndGame_Elem_Position) / sizeof(EndGame_Elem_Position[0]);
        for (int i = 0; i < length; i++) {
            EndGame_Elem_Position[i] = Platform_Rect.top;
        }
    }

    Platform_State = platform_state;
}

void Platform::Clear_BG(HDC hdc) {
    SelectObject(hdc, Config::BG_Pen);
    SelectObject(hdc, Config::BG_Brush);

    Rectangle(hdc, Prev_Platform_Rect.left, Prev_Platform_Rect.top, Prev_Platform_Rect.right, Prev_Platform_Rect.bottom);
}

void Platform::Act(){
    
    //if (Config::Tick % 10 == 0) {
        switch (Platform_State) {
        case PS_EndGame:
        case PS_StartGame:
        case PS_Extension:
            Redraw();
            break;
        }
    //}    
}

void Platform::Move_To_Left(bool left_side) {
    if (Get_State() == PS_Normal) {
        if (left_side) {

            X_Position -= Platform_Step;
            Condition();
            Redraw();
        }
        else {
            if (Get_State() == PS_Normal) {
                X_Position += Platform_Step;
                Condition();
                Redraw();
            }
        }
    }
}

void Platform::Condition() {
    if (X_Position < Config::Min_X-2)
        X_Position = Config::Min_X-2;
    if (X_Position > Config::Max_X+1)
        X_Position = Config::Max_X+1;
}

bool Platform::Check_Colision(double next_x_pos, double next_y_pos, Ball* ball) {
    double reflection_pos;
    double inner_top_y = Config::Platform_Y_Position - 5;
    double inner_bottom_y = Config::Platform_Height + Config::Platform_Y_Position - 6;
    double inner_platform_left = X_Position + 3 * Config::Circle_Size - 1;
    double inner_platform_right = X_Position + Width + Config::Circle_Size;

    //ball->Ball_Speed = 3.0;

    if (next_y_pos + ball->Radius < Config::Platform_Y_Position - 10) return false;

    //ball->Ball_Speed = 0.3;

    if (ball->Is_Going_Up()) {
        //We look if our ball is going going up -> reflect it from bottom inner side of the platform
        if (Dot_Circle_Hit(next_y_pos - inner_bottom_y, next_x_pos, inner_platform_left, inner_platform_right, ball->Radius, reflection_pos)) {
            ball->Set_Direction(-ball->Get_Direction());
            return true;
        }
    }
    else {
        //We look if our ball is going going down -> reflect it from upper inner side of the platform
        if (Dot_Circle_Hit(next_y_pos - inner_top_y, next_x_pos, inner_platform_left, inner_platform_right, ball->Radius, reflection_pos)) {
            ball->Set_Direction(-ball->Get_Direction());
            return true;
        }
    }
    return false;
}

/////////////////////////////////////////////////////////////////////
