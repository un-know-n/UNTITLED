#include "Config.h"

//          CCOLOR

Color::Color(unsigned char r, unsigned char g, unsigned char b)
    :   R(r), G(g), B(b)
{//Constructor
}

const Color Config::BG_Color(29, 31, 29);
const Color Config::Blue_Brick(43, 63, 97);
const Color Config::Green_Brick(43, 97, 49);
const Color Config::Yellow_Brick(112, 101, 46);
const Color Config::Red_Brick(97, 43, 43);

HPEN Config::BG_Pen;
HBRUSH Config::BG_Brush;
HWND Config::Hwnd;
int Config::Tick = 0;

//          CSCONFIG

void Config::Setup_Colors(){
    Config::Create_PenNBrush(Config::BG_Color, Config::BG_Pen, Config::BG_Brush);
}

//Using 3-rd principle - Polymorphism

void Config::Create_PenNBrush(const Color &color, HPEN &pen, HBRUSH &brush) {
    pen = CreatePen(PS_SOLID, 0, RGB(color.R, color.G, color.B));
    brush = CreateSolidBrush(RGB(color.R, color.G, color.B));
}

void Config::Create_PenNBrush(unsigned char r, unsigned char g, unsigned char b, HPEN &pen, HBRUSH &brush) {
    pen = CreatePen(PS_SOLID, 0, RGB(r, g, b));
    brush = CreateSolidBrush(RGB(r, g, b));
}

/////////////////////////////////////////////////////////////////////
