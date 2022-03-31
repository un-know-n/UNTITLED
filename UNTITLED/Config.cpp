#include "Config.h"

//          CCOLOR

CColor::CColor(unsigned char r, unsigned char g, unsigned char b)
    :   R(r), G(g), B(b)
{//Constructor
}

const CColor CsConfig::BG_Color(29, 31, 29);
const CColor CsConfig::Blue_Brick(43, 63, 97);
const CColor CsConfig::Green_Brick(43, 97, 49);
const CColor CsConfig::Yellow_Brick(112, 101, 46);
const CColor CsConfig::Red_Brick(97, 43, 43);

HPEN CsConfig::BG_Pen;
HBRUSH CsConfig::BG_Brush;
HWND CsConfig::Hwnd;
int CsConfig::Tick = 0;

//          CSCONFIG

void CsConfig::Setup_Colors(){
    CsConfig::Create_PenNBrush(CsConfig::BG_Color, CsConfig::BG_Pen, CsConfig::BG_Brush);
}

void CsConfig::Create_PenNBrush(const CColor &color, HPEN &pen, HBRUSH &brush) {
    pen = CreatePen(PS_SOLID, 0, RGB(color.R, color.G, color.B));
    brush = CreateSolidBrush(RGB(color.R, color.G, color.B));
}

void CsConfig::Create_PenNBrush(unsigned char r, unsigned char g, unsigned char b, HPEN &pen, HBRUSH &brush) {
    pen = CreatePen(PS_SOLID, 0, RGB(r, g, b));
    brush = CreateSolidBrush(RGB(r, g, b));
}

/////////////////////////////////////////////////////////////////////
