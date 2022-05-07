#pragma once

//#include "Common.h"
#include "Ball.h"
#include "Bonus.h"

enum EPlatform_State{
    PS_None,
    PS_Normal,
    PS_PreEndGame,
    PS_EndGame,
    PS_StartGame,
    PS_Extension,
    PS_Ready
};

enum EPlatform_Move_State {
    PMS_Stop,
    PMS_Move_Left,
    PMS_Move_Right
};

class Platform: public Main_Hit_Checker, public Driver, public Object_Designer{
public:
    ~Platform();
    Platform();

    virtual void Initialization();
    virtual void Finalization();
    virtual bool Check_Colision(double next_x_pos, double next_y_pos, Ball* ball);
    virtual void Next_Step(double max_speed);
    virtual double Get_Speed();

    virtual void Draw(HDC hdc, RECT& paint_area);
    virtual void Animate();
    virtual bool Is_Finished();

    void Init();
    void Redraw();
    //void Draw(HDC hdc, RECT& paint_area);
    void Draw_Normal(HDC hdc, RECT& paint_area);
    void Draw_EndGame(HDC hdc, RECT& paint_area);
    void Draw_StartGame(HDC hdc, RECT& paint_area);
    void Draw_Extension(HDC hdc, RECT& paint_area);
    void Set_State(EPlatform_State platform_state);
    void Clear_BG(HDC hdc);
    //void Animate();
    void Move_To_Left(bool left_side, bool is_key_down);
    void Condition();
    void Take_Platform_Scan(HDC hdc);

    bool Get_Platform_Column_Color(int x, int y, HPEN& color_pen, int& column_length);
    bool Circular_Reflection(double next_x_pos, double next_y_pos, Ball* ball, double inner_width);
    bool Got_Hit_By(Bonus* falling_bonus);

    EPlatform_State Get_State();

    Color Ellipse_Platform_Pen_Color, Rectangle_Platform_Pen_Color;

    RECT Platform_Rect, Prev_Platform_Rect;
    HPEN Ellipse_Platform_Pen, Rectangle_Platform_Pen;
    HBRUSH Ellipse_Platform_Brush, Rectangle_Platform_Brush;

    EPlatform_State Platform_State;
    EPlatform_Move_State Platform_Move_State;

    static const int Default_Width = 28;
    static const int Max_Rotation = 36;
    static const int Platform_Step = Common::Extent;
        
    int Y_Position;
    int Step_Up;
    int Inner_Platform_Width;
    int Width;
    int Height;
    int EndGame_Elem_Position[Default_Width * Common::Extent];

    double X_Position;
    double Speed;

    bool Left_Key_Down, Right_Key_Down;

    const int Platform_Normal_Width, Platform_Normal_Height;
    int* Platform_Scan;
};