
#include "Platform.h"


//          CSPLATFORM

CsPlatform::CsPlatform() : X_Position(0), Width(28), Inner_Platform_Width(21),
Ellipse_Platform_Brush(0), Ellipse_Platform_Pen(0), Platform_State(EPS_Normal),
Platform_Rect{}
{//Constructor
    X_Position = (CsConfig::Max_X) / 2;
}

void CsPlatform::Init(){
    CsConfig::Create_PenNBrush(255, 255, 255, Ellipse_Platform_Pen, Ellipse_Platform_Brush);
    CsConfig::Create_PenNBrush(81, 82, 81, Rectangle_Platform_Pen, Rectangle_Platform_Brush);
}

void CsPlatform::Redraw(HWND hwnd) {
    Prev_Platform_Rect = Platform_Rect;

    Platform_Rect.left = (CsConfig::Level_X_Offset + X_Position) * CsConfig::Extent;
    Platform_Rect.top = CsConfig::Platform_Y_Position * CsConfig::Extent;
    Platform_Rect.right = Platform_Rect.left + Width * CsConfig::Extent;
    Platform_Rect.bottom = Platform_Rect.top + CsConfig::Platform_Height * CsConfig::Extent;

    if(Platform_State == EPS_Animation){
        Prev_Platform_Rect.bottom = 199 * CsConfig::Extent;//Anim_Position;
    }

    InvalidateRect(hwnd, &Prev_Platform_Rect, FALSE);
    InvalidateRect(hwnd, &Platform_Rect, FALSE);
}

void CsPlatform::Draw(HDC hdc, RECT &paint_area) {

    switch(Platform_State){
    case EPS_Normal:
        Draw_Normal(hdc, paint_area);
        break;

    case EPS_Animation:
        Draw_Animation(hdc, paint_area);
        break;
    }
    
}

void CsPlatform::Draw_Normal(HDC hdc, RECT &paint_area){
    //if there`s collision with paint area -> draw the platform
    int x = CsConfig::Level_X_Offset + X_Position;
    int y = CsConfig::Platform_Y_Position;
    int inner_pl_width = Inner_Platform_Width;
    RECT destination_rect;
    if(!(IntersectRect(&destination_rect, &paint_area, &Platform_Rect))) return;

    SelectObject(hdc, CsConfig::BG_Pen);
    SelectObject(hdc, CsConfig::BG_Brush);

    Rectangle(hdc, Prev_Platform_Rect.left, Prev_Platform_Rect.top, Prev_Platform_Rect.right, Prev_Platform_Rect.bottom);

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

void CsPlatform::Draw_Animation(HDC hdc, RECT &paint_area){

     int x, y, y_offset = 1;
     int area_width = Width * CsConfig::Extent;
     int area_height = CsConfig::Platform_Height * CsConfig::Extent;
     COLORREF pixel;
     COLORREF bg_pixel = RGB(CsConfig::BG_Color.R, CsConfig::BG_Color.G, CsConfig::BG_Color.B);

     for(int i = 0; i < area_width; i++){
         y_offset = 1;
         x = Platform_Rect.left + i;
         for(int j = 0; j < area_height; j++){
             
              y = Anim_Position - j;

              pixel = GetPixel(hdc, x, y);
              SetPixel(hdc, x, y + y_offset, pixel);
         }
         for(int j = 0; j < y_offset; j++){
             y = Anim_Position - area_height + j;
             SetPixel(hdc, x, y, bg_pixel);
         }
     }

     ++Anim_Position;
}

void CsPlatform::Act(HWND hwnd){
    
    if(Platform_State != EPS_Animation){
        Platform_State = EPS_Animation;
        Anim_Position = Platform_Rect.bottom;
    }

    if(Platform_State == EPS_Animation) Redraw(hwnd);
}

void CsPlatform::Condition() {
    if (X_Position < CsConfig::Min_X-2)
        X_Position = CsConfig::Min_X-2;
    if (X_Position > CsConfig::Max_X+1)
        X_Position = CsConfig::Max_X+1;
}

/////////////////////////////////////////////////////////////////////
