#pragma once

#include "Bonus.h"
#include "Ball.h"

class Level: public Main_Hit_Checker, public Object_Designer{
public:
    Level();
    
    virtual bool Check_Colision(double next_x_pos, double next_y_pos, Ball* ball);

    virtual void Draw(HDC hdc, RECT& paint_area);
    virtual void Act();
    virtual bool Is_Finished();

    void Init();
    //void Draw(HDC hdc, RECT &paint_area);
    void Design_Objects(HDC hdc, RECT& paint_area, Object_Designer** object_array, int max_counter);
    void What_After_Struck(int y_coord, int x_coord);
    void Add_Fading(int x_coord, int y_coord, EBlock_Type block_type);
    //void Act();
    void Act_Objects(Object_Designer** object_array, int max_count, int& counter);

    bool Check_Vertical_Hit(int level_y, int level_x, double next_x_pos, double next_y_pos, Ball* ball, double& reflection_pos);
    bool Check_Horizontal_Hit(int level_y, int level_x, double next_x_pos, double next_y_pos, Ball* ball, double& reflection_pos);
    bool Have_Next_Bonus(int& index, Bonus** falling_bonus);
    bool Add_Bonus(int y_coord, int x_coord, EBlock_Type block_type);

    RECT Level_Area;

    int Fading_Count;
    Fade_Block* Fading[Config::Max_Fading_Count];

    int Falling_Count;
    Bonus* Falling[Config::Max_Falling_Count];

private:

    void Draw_Block(HDC hdc, RECT& block_area, EBlock_Type block_type);

    double Current_Block_Left_Side, Current_Block_Right_Side;
    double Current_Block_Bottom_Y_Pos, Current_Block_Top_Y_Pos;
};