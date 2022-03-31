
#include "Platform.h"


//          CSPLATFORM

CsPlatform::CsPlatform() : X_Position(0), Y_Position(CsConfig::Platform_Y_Position), Width(28), Inner_Platform_Width(21),
Ellipse_Platform_Brush(0), Ellipse_Platform_Pen(0), Platform_State(EPS_Normal), Step_Up(0), Platform_Step(3),
Platform_Rect{}
{//Constructor
    X_Position = (CsConfig::Max_X) / 2;
}

void CsPlatform::Init(){
    CsConfig::Create_PenNBrush(255, 255, 255, Ellipse_Platform_Pen, Ellipse_Platform_Brush);
    CsConfig::Create_PenNBrush(81, 82, 81, Rectangle_Platform_Pen, Rectangle_Platform_Brush);
}

void CsPlatform::Redraw() {
    Prev_Platform_Rect = Platform_Rect;
    int temp;
    if (Platform_State == EPS_StartGame) temp = CsConfig::Circle_Size;
    else temp = Width;

    Platform_Rect.left = (CsConfig::Level_X_Offset + X_Position) * CsConfig::Extent;
    Platform_Rect.top = CsConfig::Platform_Y_Position * CsConfig::Extent;
    Platform_Rect.right = Platform_Rect.left + temp * CsConfig::Extent;
    Platform_Rect.bottom = Platform_Rect.top + CsConfig::Platform_Height * CsConfig::Extent;

    if(Platform_State == EPS_EndGame || Platform_State == EPS_StartGame){
        Prev_Platform_Rect.bottom = 200 * CsConfig::Extent;//EndGame_Position;
        //Prev_Platform_Rect.top -= 100;
    }

    InvalidateRect(CsConfig::Hwnd, &Prev_Platform_Rect, FALSE);
    InvalidateRect(CsConfig::Hwnd, &Platform_Rect, FALSE);
}

void CsPlatform::Draw(HDC hdc, RECT &paint_area) {

    RECT destination_rect;
    if (!(IntersectRect(&destination_rect, &paint_area, &Platform_Rect))) return;

    switch (Platform_State) {
    case EPS_Normal:
        Draw_Normal(hdc, paint_area);
        break;

    case EPS_EndGame:
        Draw_EndGame(hdc, paint_area);
        break;

    case EPS_StartGame:
        Draw_StartGame(hdc, paint_area);
        break;

    case EPS_Extension:
        Draw_Extension(hdc, paint_area);
        break;
    }
}

void CsPlatform::Draw_Normal(HDC hdc, RECT &paint_area){
    //if there`s collision with paint area -> draw the platform
    int x = CsConfig::Level_X_Offset + X_Position;
    int y = CsConfig::Platform_Y_Position;
    int inner_pl_width = Inner_Platform_Width;

    Clear_BG(hdc);

    SelectObject(hdc, Ellipse_Platform_Pen);
    SelectObject(hdc, Ellipse_Platform_Brush);

    Ellipse(hdc, (x+1) * CsConfig::Extent, (y+1) * CsConfig::Extent,
        (x + 1 + CsConfig::Circle_Size) * CsConfig::Extent, (y + 1 + CsConfig::Circle_Size) * CsConfig::Extent);
    Ellipse(hdc, (x + 1 + inner_pl_width) * CsConfig::Extent, (y+1) * CsConfig::Extent,
        (x + 1 + CsConfig::Circle_Size + inner_pl_width) * CsConfig::Extent, (y + 1 + CsConfig::Circle_Size) * CsConfig::Extent);

    SelectObject(hdc, Rectangle_Platform_Pen);
    SelectObject(hdc, Rectangle_Platform_Brush);

    RoundRect(hdc, (x + 4) * CsConfig::Extent, (y + 1) * CsConfig::Extent,
        (x + inner_pl_width + 3) * CsConfig::Extent,
        (y + 6) * CsConfig::Extent, 3, 3);
}

void CsPlatform::Draw_EndGame(HDC hdc, RECT &paint_area){

     int x, y, y_offset;
     int area_width = Width * CsConfig::Extent;
     int area_height = CsConfig::Platform_Height * CsConfig::Extent;
     COLORREF pixel;
     COLORREF bg_pixel = RGB(CsConfig::BG_Color.R, CsConfig::BG_Color.G, CsConfig::BG_Color.B);

     for (int i = 0; i < area_width; i++) {
         y_offset = rand() % 4 + 1;
         x = Platform_Rect.left + i;
         for (int j = 0; j < area_height; j++) {

             y = EndGame_Elem_Position[i] - j;

             pixel = GetPixel(hdc, x, y);
             SetPixel(hdc, x, y + y_offset, pixel);
         }
         for (int j = 0; j < y_offset; j++) {
             y = EndGame_Elem_Position[i] - area_height + j;
             SetPixel(hdc, x, y, bg_pixel);
         }

         EndGame_Elem_Position[i] += y_offset;
     }
}

void CsPlatform::Draw_StartGame(HDC hdc, RECT& paint_area) {
    int x = (CsConfig::Level_X_Offset + X_Position) * CsConfig::Extent;
    int y = (CsConfig::Level_Y_Offset * CsConfig::Extent + Y_Position) * CsConfig::Extent;
    int normal_coords = CsConfig::Circle_Size * CsConfig::Extent;
    XFORM xForm, old_xForm;
    double alpha;

    Clear_BG(hdc);

    SelectObject(hdc, Ellipse_Platform_Pen);
    SelectObject(hdc, Ellipse_Platform_Brush);

    Ellipse(hdc, x, y, x + normal_coords, y + normal_coords);

    //Rotate view

    alpha = 2.0 * M_PI / (double)(Max_Rotation) * (double)(Step_Up);
    ++Step_Up;

    SetGraphicsMode(hdc, GM_ADVANCED);
    xForm.eM11 = (float)cos(alpha);
    xForm.eM12 = (float)sin(alpha);
    xForm.eM21 = (float)-sin(alpha);
    xForm.eM22 = (float)cos(alpha);
    xForm.eDx = (float)x + normal_coords / 2;
    xForm.eDy = (float)y + normal_coords / 2;
    GetWorldTransform(hdc, &old_xForm);
    SetWorldTransform(hdc, &xForm);

    SelectObject(hdc, CsConfig::BG_Pen);
    SelectObject(hdc, CsConfig::BG_Brush);

    Rectangle(hdc,-CsConfig::Extent / 2, -normal_coords / 2, CsConfig::Extent / 2, normal_coords / 2);

    if (y > CsConfig::Platform_Y_Position * CsConfig::Extent) --Y_Position;
    else {
        Platform_State = EPS_Extension;
        Inner_Platform_Width = 1;
    }
    if (Step_Up >= Max_Rotation) Step_Up -= Max_Rotation;
    
    SetWorldTransform(hdc, &old_xForm);
}

void CsPlatform::Draw_Extension(HDC hdc, RECT& paint_area) {
    Draw_Normal(hdc, paint_area);
    
    if(Inner_Platform_Width <= 21){
        --X_Position;
        Inner_Platform_Width += 3;
    } else Platform_State = EPS_Normal;
}

void CsPlatform::Set_State(EPlatform_State platform_state) {
    if (Platform_State == platform_state) return;
    else Platform_State = platform_state;
    if (platform_state == EPS_EndGame) {
        int length = sizeof(EndGame_Elem_Position) / sizeof(EndGame_Elem_Position[0]);
        for (int i = 0; i < length; i++) {
            EndGame_Elem_Position[i] = Platform_Rect.bottom;
        }
    }
}

void CsPlatform::Clear_BG(HDC hdc) {
    SelectObject(hdc, CsConfig::BG_Pen);
    SelectObject(hdc, CsConfig::BG_Brush);

    Rectangle(hdc, Prev_Platform_Rect.left, Prev_Platform_Rect.top, Prev_Platform_Rect.right, Prev_Platform_Rect.bottom);
}

void CsPlatform::Act(){
    
    switch (Platform_State) {
    case EPS_EndGame:
    case EPS_StartGame:
    case EPS_Extension:
        Redraw();
        break;
    }
}

void CsPlatform::Condition() {
    if (X_Position < CsConfig::Min_X-2)
        X_Position = CsConfig::Min_X-2;
    if (X_Position > CsConfig::Max_X+1)
        X_Position = CsConfig::Max_X+1;
}

/////////////////////////////////////////////////////////////////////
