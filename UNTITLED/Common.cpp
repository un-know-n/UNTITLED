#include "Common.h"

//          COLOR

Color::Color(unsigned char r, unsigned char g, unsigned char b)
    :   R(r), G(g), B(b)
{//Constructor
}

int Color::Get_RGB() const {
    return RGB(R, G, B);
}

const Color Common::BG_Color(29, 31, 29);
const Color Common::Blue_Block(43, 63, 97);
const Color Common::Green_Block(43, 97, 49);
const Color Common::Yellow_Block(112, 101, 46);
const Color Common::Red_Block(97, 43, 43);

//          CONFIG

HPEN Common::Green_Pen, Common::Blue_Pen, Common::Red_Pen, Common::Yellow_Pen;
HBRUSH Common::Green_Brush, Common::Blue_Brush, Common::Red_Brush, Common::Yellow_Brush;

HPEN Common::BG_Pen;
HBRUSH Common::BG_Brush;
HWND Common::Hwnd;
int Common::Tick = 0;
int Common::Floor_Tick = 0;

const double Common::Step_Size = 1.0 / Common::Extent;

bool Common::Have_Floor = false;

void Common::Setup_Colors(){
    Common::Create_PenNBrush(Common::Green_Block, Common::Green_Pen, Common::Green_Brush);
    Common::Create_PenNBrush(Common::Blue_Block, Common::Blue_Pen, Common::Blue_Brush);
    Common::Create_PenNBrush(Common::Red_Block, Common::Red_Pen, Common::Red_Brush);
    Common::Create_PenNBrush(Common::Yellow_Block, Common::Yellow_Pen, Common::Yellow_Brush);

    Common::Create_PenNBrush(Common::BG_Color, Common::BG_Pen, Common::BG_Brush);
}

//Using 3-rd principle - Polymorphism

void Common::Create_PenNBrush(const Color &color, HPEN &pen, HBRUSH &brush) {
    pen = CreatePen(PS_SOLID, 0, RGB(color.R, color.G, color.B));
    brush = CreateSolidBrush(RGB(color.R, color.G, color.B));
}

void Common::Create_PenNBrush(unsigned char r, unsigned char g, unsigned char b, HPEN &pen, HBRUSH &brush) {
    pen = CreatePen(PS_SOLID, 0, RGB(r, g, b));//PS_DOT
    brush = CreateSolidBrush(RGB(r, g, b));
}

/////////////////////////////////////////////////////////////////////
