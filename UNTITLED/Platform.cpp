
#include "Platform.h"

//          PLATFORM

Platform::~Platform() {
    delete[] Platform_Scan;// delete[] - its used when pointer refers to an array
}

Platform::Platform() : X_Position(0), Y_Position(Common::Platform_Y_Position), Width(84), Height(21), Inner_Platform_Width(63),
Ellipse_Platform_Brush(0), Ellipse_Platform_Pen(0), Platform_State(PS_None), Platform_Move_State(PMS_Stop), Step_Up(0),
Platform_Rect{}, Platform_Normal_Width(Width), Platform_Normal_Height(Height),
Left_Key_Down(false), Right_Key_Down(false), Ellipse_Platform_Pen_Color(255, 255, 255), Rectangle_Platform_Pen_Color(81, 82, 81)
{//Constructor
    X_Position = (Common::Max_X) / 2 + 6;
}

void Platform::Init(){
    //Initialization of the main pens and brushes
    Common::Create_PenNBrush(255, 255, 255, Ellipse_Platform_Pen, Ellipse_Platform_Brush);
    Common::Create_PenNBrush(81, 82, 81, Rectangle_Platform_Pen, Rectangle_Platform_Brush);
}

void Platform::Redraw() {
    Prev_Platform_Rect = Platform_Rect;
    int temp_width;
    if (Platform_State == PS_StartGame) temp_width = Common::Circle_Size;
    else temp_width = Width;

    Platform_Rect.left = Common::Level_X_Offset + X_Position;
    Platform_Rect.top = Common::Platform_Y_Position;
    Platform_Rect.right = Platform_Rect.left + temp_width;
    Platform_Rect.bottom = Platform_Rect.top + Common::Platform_Height;

    if(Platform_State == PS_EndGame || Platform_State == PS_StartGame){
        Prev_Platform_Rect.bottom = 615;
    }
    if (Platform_State == PS_StartGame) {
        X_Position = (Common::Max_X) / 2 + 6;
    }

    InvalidateRect(Common::Hwnd, &Prev_Platform_Rect, FALSE);
    InvalidateRect(Common::Hwnd, &Platform_Rect, FALSE);
}

void Platform::Draw_Normal(HDC hdc, RECT &paint_area){
    //Here we draw platform in normal condition
    int x = Common::Level_X_Offset + X_Position;
    int y = Common::Platform_Y_Position;
    int inner_pl_width = Inner_Platform_Width;
    int offset = 0;

    Clear_BG(hdc);

    SelectObject(hdc, Ellipse_Platform_Pen);
    SelectObject(hdc, Ellipse_Platform_Brush);

    Ellipse(hdc, x + 3, y + 3, x + 2 + Common::Circle_Size, y + 2 + Common::Circle_Size);
    Ellipse(hdc, x + 3 + inner_pl_width, y + 3, x + 2 + Common::Circle_Size + inner_pl_width, y + 2 + Common::Circle_Size);

    SelectObject(hdc, Rectangle_Platform_Pen);
    SelectObject(hdc, Rectangle_Platform_Brush);

    RoundRect(hdc, x + 11, y + 4, x + inner_pl_width + 9, y + 16, 3, 3);

    Take_Platform_Scan(hdc);
}

void Platform::Take_Platform_Scan(HDC hdc) {
    //Making the "scan" of the platform due to make final animation
    int x = Common::Level_X_Offset + X_Position;
    int y = Common::Platform_Y_Position;
    int offset = 0;

    if (Platform_Scan == 0 && Platform_State == PS_Ready) {
        Platform_Scan = new int[Platform_Normal_Width * Platform_Normal_Height];

        //Taking every pixel to the platform scan array
        for (int i = 0; i < Platform_Normal_Height; i++) {
            for (int j = 0; j < Platform_Normal_Width; j++) {
                Platform_Scan[offset++] = GetPixel(hdc, x + j, y + i);
            }
        }
    }
}

void Platform::Draw_EndGame(HDC hdc, RECT &paint_area){
    //Here we draw platform in endgame condition
     Inner_Platform_Width = 63;
     int x, y, y_offset;
     int column_counter = 0;
     int area_width = Width;
     
     const int max_position = Common::Max_Y_Pos;
     COLORREF pixel;
     COLORREF bg_pixel = RGB(Common::BG_Color.R, Common::BG_Color.G, Common::BG_Color.B);
     HPEN color_pen;
     int column_length = 0;

     //Going through every column in platform area
     for (int i = 0; i < area_width; i++) {
         if (EndGame_Elem_Position[i] > max_position) continue;

         ++column_counter;

         //Making random offset due to prettier animation
         y_offset = rand() % 4 + 1;
         x = Platform_Rect.left + i;
  
         int j = 0;
         y = EndGame_Elem_Position[i];

         MoveToEx(hdc, x, y, 0);

         //While we can take color from column -> we move that column
         while (Get_Platform_Column_Color(i, j, color_pen, column_length)) {

             SelectObject(hdc, color_pen);
             LineTo(hdc, x, y + column_length);

             y += column_length;
             j += column_length;
         }

         //Drawing over moved area
         y = EndGame_Elem_Position[i];
         MoveToEx(hdc, x, y, 0);
         SelectObject(hdc, Common::BG_Pen);
         LineTo(hdc, x, y + y_offset);

         //Moving our index to offset value
         EndGame_Elem_Position[i] += y_offset;
     }
     
     //If we have no colums -> there`s no platform
     if (column_counter == 0) {
         Platform_State = PS_None;
         Sleep(200);
     }

}

bool Platform::Get_Platform_Column_Color(int x, int y, HPEN& color_pen, int& column_length) {

    int offset = y * Platform_Normal_Width + x;
    int color = 0;

    if (y > Platform_Normal_Height) return false;

    //Going through all platform height
    for (int i = y; i < Platform_Normal_Height; i++) {
        //if that is first iteration -> start to take the color
        if (i == y) {
            color = Platform_Scan[offset];
            column_length = 1;
        }
        else {
            //if colors are identical -> continue
            if (color == Platform_Scan[offset]) {
                column_length++;
            }
            else break;
        }
        
        offset += Platform_Normal_Width;
    }

    //Choose the color to painting
    if (color == Ellipse_Platform_Pen_Color.Get_RGB()) {
        color_pen = Ellipse_Platform_Pen;
    }
    else if (color == Rectangle_Platform_Pen_Color.Get_RGB()) {
        color_pen = Rectangle_Platform_Pen;
    }
    else if (color == Common::BG_Color.Get_RGB()) {
        color_pen = Common::BG_Pen;
    }
    else color_pen = 0;

    return true;
}

void Platform::Draw_StartGame(HDC hdc, RECT& paint_area) {
    //Drawing the start game animation
    int x = Common::Level_X_Offset + X_Position;
    int y = Common::Level_Y_Offset * 3 + Y_Position;

    int normal_coords = Common::Circle_Size;
    XFORM xForm, old_xForm;
    double alpha;

    Clear_BG(hdc);

    SelectObject(hdc, Ellipse_Platform_Pen);
    SelectObject(hdc, Ellipse_Platform_Brush);

    Ellipse(hdc, x, y, x + normal_coords, y + normal_coords);

    //Rotate view

    alpha = 2.0 * M_PI / (double)(Max_Rotation) * (double)(Step_Up);
    ++Step_Up;

    xForm.eM11 = (float)cos(alpha);
    xForm.eM12 = (float)sin(alpha);
    xForm.eM21 = (float)-sin(alpha);
    xForm.eM22 = (float)cos(alpha);
    xForm.eDx = (float)x + normal_coords / 2;
    xForm.eDy = (float)y + normal_coords / 2;
    GetWorldTransform(hdc, &old_xForm);
    SetWorldTransform(hdc, &xForm);

    SelectObject(hdc, Common::BG_Pen);
    SelectObject(hdc, Common::BG_Brush);

    Rectangle(hdc, -3 / 2, -normal_coords / 2, 3 / 2, normal_coords / 2 + 1);

    if (y > Common::Platform_Y_Position) Y_Position -= 3;
    else {

        Platform_State = PS_Extension;
        Inner_Platform_Width = 1; 
        
    }

    if (Step_Up >= Max_Rotation) Step_Up -= Max_Rotation;
    
    SetWorldTransform(hdc, &old_xForm);
}

void Platform::Draw_Extension(HDC hdc, RECT& paint_area) {
    //Draw the extension of the platform
    Draw_Normal(hdc, paint_area);
            
    if (Inner_Platform_Width <= 63) {
        --X_Position;
        Inner_Platform_Width += 9;
    }
    else {
        Platform_State = PS_Ready;
        Redraw();
        Inner_Platform_Width = 63;

    }    
}

EPlatform_State Platform::Get_State() {
    //Default getter
    return Platform_State;
}

void Platform::Set_State(EPlatform_State platform_state) {
    //Default setter
    if (platform_state == PS_EndGame) {
        int length = sizeof(EndGame_Elem_Position) / sizeof(EndGame_Elem_Position[0]);
        for (int i = 0; i < length; i++) {
            EndGame_Elem_Position[i] = Platform_Rect.top;
        }
    }

    Platform_State = platform_state;
}

void Platform::Clear_BG(HDC hdc) {
    SelectObject(hdc, Common::BG_Pen);
    SelectObject(hdc, Common::BG_Brush);

    Rectangle(hdc, Prev_Platform_Rect.left, Prev_Platform_Rect.top, Prev_Platform_Rect.right, Prev_Platform_Rect.bottom);
}

void Platform::Move_To_Left(bool left_side, bool is_key_down) {
    //Making right movement system for platform
    if (Get_State() != PS_Normal) return;

    if (left_side) Left_Key_Down = is_key_down;
    else Right_Key_Down = is_key_down;

    if (Left_Key_Down && Right_Key_Down) return;
    if (!Left_Key_Down && !Right_Key_Down) {
        Speed = 0.0;
        Platform_Move_State = PMS_Stop;
        return;
    }

    if (Left_Key_Down) {
        Platform_Move_State = PMS_Move_Left;
        Speed = -Platform_Step;

    } 
    if(Right_Key_Down) {
        Platform_Move_State = PMS_Move_Right;
        Speed = Platform_Step;
    }
}

void Platform::Next_Step(double max_speed) {
    //Making next step, depending on a few factors
    double next_step = Speed / max_speed * Common::Step_Size;
    X_Position += next_step;
    Condition();
    //Redraw();
}

double Platform::Get_Speed() {
    //Default getter
    return Speed;
}

void Platform::Draw(HDC hdc, RECT& paint_area) {

    RECT destination_rect;
    if (!(IntersectRect(&destination_rect, &paint_area, &Platform_Rect))) return;

    switch (Platform_State) {
    case PS_Normal:
    case PS_Ready:
        Draw_Normal(hdc, paint_area);
        break;

    case PS_PreEndGame:
        Draw_Normal(hdc, paint_area);
        Speed = 0.0;
        Set_State(PS_EndGame);
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

void Platform::Animate() {

    switch (Platform_State) {
    case PS_EndGame:
    case PS_StartGame:
    case PS_Extension:
        Redraw();
        break;
    }
}

bool Platform::Is_Finished() {
    //There`s nothing
    return false;
}

void Platform::Condition() {
    //Check border collapse with platform
    if (X_Position < Common::Min_X-7) X_Position = Common::Min_X-7;
    if (X_Position > Common::Max_X+3) X_Position = Common::Max_X+3;
}

void Platform::Initialization() {
    //There`s nothing
}
void Platform::Finalization() {
    Redraw();
}

bool Platform::Check_Colision(double next_x_pos, double next_y_pos, Ball* ball) {
    double reflection_pos;
    double inner_top_y = Common::Platform_Y_Position - 15;
    double inner_bottom_y = Common::Platform_Height + Common::Platform_Y_Position - 6;
    double inner_platform_left = X_Position + 2 * Common::Circle_Size - 3;
    double inner_platform_right = X_Position + Width + 2 * Common::Circle_Size - 3;

    if (next_y_pos + ball->Radius < Common::Platform_Y_Position - 10) return false;
    

    //We look if our ball is going to the left side 

    if (Circular_Reflection(next_x_pos, next_y_pos, ball, 0))return true;

    //We look if our ball is going to the right side

    if (Circular_Reflection(next_x_pos, next_y_pos, ball, Inner_Platform_Width))return true;

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

bool Platform::Circular_Reflection(double next_x_pos, double next_y_pos, Ball* ball, double inner_width) {
    //The hardest topic
    //Reflection from the circles on the platform
    double dx_range, dy_range;
    double temporary_distance, radius_summ, platform_ball_radius;
    double platform_ball_x, platform_ball_y;
    double beta_angle, alpha_angle, gamma_angle;
    double related_ball_direction = 0;

    platform_ball_radius = (double)Common::Circle_Size / 2.0;

    platform_ball_x = Platform_Rect.left / 3 + platform_ball_radius + 2 + inner_width;
    platform_ball_y = Platform_Rect.top / 3 - platform_ball_radius;

    dx_range = next_x_pos - platform_ball_x;
    dy_range = next_y_pos - platform_ball_y;

    radius_summ = platform_ball_radius + ball->Radius;

    temporary_distance = sqrt(dx_range * dx_range + dy_range * dy_range);

    if (fabs(temporary_distance - radius_summ) < Common::Step_Size) {//temporary_distance <= radius_summ || // temporary_distance + Common::Step_Size <= radius_summ

        beta_angle = atan2(-dy_range, dx_range);

        related_ball_direction = ball->Get_Direction();
        related_ball_direction -= beta_angle;

        if (related_ball_direction > 2.0 * M_PI) related_ball_direction -= 2.0 * M_PI;

        if (related_ball_direction > M_PI_2 || related_ball_direction < M_PI + M_PI_2) {
            alpha_angle = beta_angle + M_PI - ball->Get_Direction();
            gamma_angle = alpha_angle + beta_angle;

            ball->Set_Direction(gamma_angle);
            return true;
        }        
        
    }
    return false;
}

bool Platform::Got_Hit_By(Bonus* falling_bonus) {
    //Check if platform has collided with bonus

    RECT destination_rect, bonus_rect;

    falling_bonus->Get_Bonus_Rect(bonus_rect);

    if ((IntersectRect(&destination_rect, &bonus_rect, &Platform_Rect))) return true;
    else return false;
}

/////////////////////////////////////////////////////////////////////
