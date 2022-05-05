#pragma once

#include "Fade.h"

enum EBonus_Type {
    BNT_None,
    BNT_Tripple_Ball,
    BNT_Additional_Life,
    BNT_Floor
};

class Bonus : public Object_Designer {
public:
    Bonus(EBlock_Type block_type, EBonus_Type bonus_type, int x, int y);

    virtual void Draw(HDC hdc, RECT& paint_area);
    virtual void Animate();
    virtual bool Is_Finished();

    void Get_Bonus_Rect(RECT& bonus_rect);
    void Finalize();
    void Draw_Front_Block_Animation(HDC hdc, HPEN& first_pen, HBRUSH& first_brush, HPEN& second_pen, HBRUSH& second_brush, double& offset);
    void Test_Falling_Bonus(HDC hdc);

    const EBonus_Type Bonus_Type;
    const EBlock_Type Block_Type;

    static const int Half_Height = Common::Block_Height / 2;

    int X, Y;
    int Step, Action_Step;

    bool Got_Hit;
    bool Finished;

    RECT Bonus_Rect, Prev_Bonus_Rect;

private:
    void Change_BG_Color(EBlock_Type block_type, HPEN& front_pen, HBRUSH& front_brush, HPEN& back_pen, HBRUSH& back_brush);
    void Draw_Block_Animation(HDC hdc);
};