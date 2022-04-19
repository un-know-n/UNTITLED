#include "Config.h"

//          COLOR

Color::Color(unsigned char r, unsigned char g, unsigned char b)
    :   R(r), G(g), B(b)
{//Constructor
}

int Color::Get_RGB() const {
    return RGB(R, G, B);
}

const Color Config::BG_Color(29, 31, 29);
const Color Config::Blue_Block(43, 63, 97);
const Color Config::Green_Block(43, 97, 49);
const Color Config::Yellow_Block(112, 101, 46);
const Color Config::Red_Block(97, 43, 43);

//          CONFIG

HPEN Config::Green_Pen, Config::Blue_Pen, Config::Red_Pen, Config::Yellow_Pen;
HBRUSH Config::Green_Brush, Config::Blue_Brush, Config::Red_Brush, Config::Yellow_Brush;

HPEN Config::BG_Pen;
HBRUSH Config::BG_Brush;
HWND Config::Hwnd;
int Config::Tick = 0;

const double Config::Step_Size = 1.0 / Config::Extent;

void Config::Setup_Colors(){
    Config::Create_PenNBrush(Config::Green_Block, Config::Green_Pen, Config::Green_Brush);
    Config::Create_PenNBrush(Config::Blue_Block, Config::Blue_Pen, Config::Blue_Brush);
    Config::Create_PenNBrush(Config::Red_Block, Config::Red_Pen, Config::Red_Brush);
    Config::Create_PenNBrush(Config::Yellow_Block, Config::Yellow_Pen, Config::Yellow_Brush);

    Config::Create_PenNBrush(Config::BG_Color, Config::BG_Pen, Config::BG_Brush);
}

//Using 3-rd principle - Polymorphism

void Config::Create_PenNBrush(const Color &color, HPEN &pen, HBRUSH &brush) {
    pen = CreatePen(PS_SOLID, 0, RGB(color.R, color.G, color.B));
    brush = CreateSolidBrush(RGB(color.R, color.G, color.B));
}

void Config::Create_PenNBrush(unsigned char r, unsigned char g, unsigned char b, HPEN &pen, HBRUSH &brush) {
    pen = CreatePen(PS_SOLID, 0, RGB(r, g, b));//PS_DOT
    brush = CreateSolidBrush(RGB(r, g, b));
}

/////////////////////////////////////////////////////////////////////
