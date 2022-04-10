#pragma once

#include "Fade.h"
#include "Ball.h"

enum EBonus_Type {
    BNT_None,
    BNT_Circle
};

class Bonus {
public:
    Bonus(EBonus_Type bonus_type);

    const EBonus_Type Bonus_Type;
};

class Level: public Main_Hit_Checker{
public:
    Level();

    HBRUSH Green_Brush, Blue_Brush, Red_Brush, Yellow_Brush;
    HPEN Green_Pen, Blue_Pen, Red_Pen, Yellow_Pen;
    RECT Level_Area;

    int Fading_Count;
    Fade_Block *Fading[Config::Max_Fading_Count];

    int Falling_Count;
    Bonus* Falling_Bonus[Config::Max_Falling_Count];

    virtual bool Check_Colision(double next_x_pos, double next_y_pos, Ball* ball);
    void Init();
    void Draw(HDC hdc, RECT &paint_area);
    void Change_BG_Color(EBlock_Type type, HPEN &front_pen, HBRUSH &front_brush, HPEN &back_pen, HBRUSH &back_brush);
    bool Check_Vertical_Hit(int level_y, int level_x, double next_x_pos, double next_y_pos, Ball* ball, double & reflection_pos); //double &reflection_pos
    bool Check_Horizontal_Hit(int level_y, int level_x, double next_x_pos, double next_y_pos, Ball* ball, double& reflection_pos); //double &
    void Add_Fading(int x_coord, int y_coord);
    void What_After_Struck(int y_coord, int x_coord);
    void Add_Bonus(int y_coord, int x_coord);
    void Act();

private:
    double Current_Block_Left_Side, Current_Block_Right_Side;
    double Current_Block_Bottom_Y_Pos, Current_Block_Top_Y_Pos;

    void Draw_Block(HDC hdc, int x, int y, EBlock_Type type);
    void Draw_Brick_Animation(HDC hdc, EBlock_Type type, EBonus_Type letter_type, int x, int y, int step);

};