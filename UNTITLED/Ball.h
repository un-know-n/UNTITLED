#pragma once

#include "Config.h"

enum EBall_State {
    BS_Disabled,
    BS_None,

    BS_Test,    
    BS_Start,
    BS_Free
};

class Ball;

class Main_Hit_Checker {
public:
    virtual bool Check_Colision(double next_x_pos, double next_y_pos, Ball* ball) = 0;
    bool Dot_Circle_Hit(double y, double next_x_pos, double left_x, double right_x, double radius, double& x);//double &x
};

class Driver {
public:
    ~Driver();

    virtual void Initialization() = 0;
    virtual void Finalization() = 0;
    virtual void Next_Step(double max_speed) = 0;
    virtual double Get_Speed() = 0;

};

class Ball: public Driver, public Object_Designer {
public:
    Ball();

    virtual void Initialization();
    virtual void Finalization();
    virtual void Next_Step(double max_speed);
    virtual double Get_Speed();

    virtual void Draw(HDC hdc, RECT& paint_area);
    virtual void Act();
    virtual bool Is_Finished();
    
    static void Add_Hit_Checker(Main_Hit_Checker* hit_check);

    void Init();
    //void Draw(HDC hdc, RECT& paint_area);
    void Redraw();
    void Set_State(EBall_State state, int x_pos);
    void Set_Direction(double new_direction);
    void Is_Vertical_Reflect(bool is_vertical);
    void Set_Test();
    void Get_Center(double& ball_x_pos, double& ball_y_pos);

    bool Is_Test_Finished();
    bool Is_Going_Up();
    bool Is_Going_Left();

    double Get_Direction();    

    EBall_State Get_State();

    static Main_Hit_Checker* Hit_Check[3];
    RECT Ball_Rect, Prev_Ball_Rect;
    HPEN Ball_Pen;
    HBRUSH Ball_Brush;
    EBall_State Ball_State;

    static const double Radius;
    static const double Start_Y_Pos;

    static int Hit_Counter;

    double Central_X, Central_Y;
    double Rest_Size;
    double Rest_Test_Size;
    double Ball_Speed;
    
    int Move_Pos;
    bool Test_Active;

private:
    double Ball_Direction;
};