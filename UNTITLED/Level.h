#pragma once

#include "Fade.h"
#include "Ball.h"

enum ELetter_Type {
    ELT_None,
    ELT_Circle
};

class Level: public Main_Hit_Checker{
public:
    Level();

    HBRUSH Green_Brush, Blue_Brush, Red_Brush, Yellow_Brush;
    HPEN Green_Pen, Blue_Pen, Red_Pen, Yellow_Pen;
    RECT Level_Area;

    //Fade_Brick Fade;

    int Fading_Count;
    Fade_Brick *Fading[Config::Max_Fading_Count];

    virtual bool Check_Colision(double next_x_pos, double next_y_pos, Ball* ball);
    void Init();
    void Draw(HDC hdc, RECT &paint_area);
    void Change_BG_Color(EBrick_Type type, HPEN &front_pen, HBRUSH &front_brush, HPEN &back_pen, HBRUSH &back_brush);
    //bool Is_Horizontal_Check(double next_x_pos, double next_y_pos);
    bool Check_Vertical_Hit(int level_y, int level_x, double next_x_pos, double next_y_pos, Ball* ball, double & reflection_pos); //double &reflection_pos
    bool Check_Horizontal_Hit(int level_y, int level_x, double next_x_pos, double next_y_pos, Ball* ball, double& reflection_pos); //double &
    void Add_Fading(int x_coord, int y_coord);
    void Act();

private:
    double Current_Brick_Left_Side, Current_Brick_Right_Side;
    double Current_Brick_Bottom_Y_Pos, Current_Brick_Top_Y_Pos;

    void Draw_Brick(HDC hdc, int x, int y, EBrick_Type type);
    void Draw_Brick_Animation(HDC hdc, EBrick_Type type, ELetter_Type letter_type, int x, int y, int step);
    //static char Level_01[Config::Level_X_Elems][Config::Level_Y_Elems];

};