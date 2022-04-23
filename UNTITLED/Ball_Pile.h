#pragma once

#include "Ball.h"

class Ball_Pile : public Driver, public Object_Designer {
public:

    virtual void Initialization();
    virtual void Finalization();
    virtual void Next_Step(double max_speed);
    virtual double Get_Speed();

    virtual void Draw(HDC hdc, RECT& paint_area);
    virtual void Animate();
    virtual bool Is_Finished();

    //void Draw(HDC hdc, RECT& paint_area);
    void Release_Balls(double platform_pos);
    void Set_On_Platform(double platform_pos);
    void Tripple_Balls();

    bool If_Balls_Lost();

    Ball Balls[Common::Max_Ball_Count];
};