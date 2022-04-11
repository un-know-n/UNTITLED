#pragma once

#include "Fade.h"
#include "Ball.h"

enum EBonus_Type {
    BNT_None,
    BNT_Circle
};

class Bonus {
public:
    Bonus(EBlock_Type block_type, EBonus_Type bonus_type, int x, int y);

    const EBonus_Type Bonus_Type;
    const EBlock_Type Block_Type;
    int X, Y;
    int Step, Action_Step;

    RECT Bonus_Rect, Prev_Bonus_Rect;

    void Draw(HDC hdc, RECT &paint_area);
    void Act();
    bool Is_Finished();

private:
    void Change_BG_Color(EBlock_Type block_type, HPEN& front_pen, HBRUSH& front_brush, HPEN& back_pen, HBRUSH& back_brush);
    void Draw_Block_Animation(HDC hdc);
};

class Level: public Main_Hit_Checker{
public:
    Level();

    RECT Level_Area;

    int Fading_Count;
    Fade_Block *Fading[Config::Max_Fading_Count];

    int Falling_Count;
    Bonus* Falling[Config::Max_Falling_Count];

    virtual bool Check_Colision(double next_x_pos, double next_y_pos, Ball* ball);
    void Init();
    void Draw(HDC hdc, RECT &paint_area);
    bool Check_Vertical_Hit(int level_y, int level_x, double next_x_pos, double next_y_pos, Ball* ball, double & reflection_pos);
    bool Check_Horizontal_Hit(int level_y, int level_x, double next_x_pos, double next_y_pos, Ball* ball, double& reflection_pos); 
    void What_After_Struck(int y_coord, int x_coord);
    void Add_Fading(int x_coord, int y_coord, EBlock_Type block_type);
    bool Add_Bonus(int y_coord, int x_coord, EBlock_Type block_type);
    void Act();

private:
    double Current_Block_Left_Side, Current_Block_Right_Side;
    double Current_Block_Bottom_Y_Pos, Current_Block_Top_Y_Pos;

    void Draw_Block(HDC hdc, int x, int y, EBlock_Type block_type);
};