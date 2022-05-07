#include "Bonus.h"

//      BONUS

Bonus::Bonus(EBlock_Type block_type, EBonus_Type bonus_type, int x, int y)
    : Block_Type(block_type), Bonus_Type(bonus_type), X(x), Y(y), Step(0), Action_Step(0), Got_Hit(false), Finished(false)
{//Constructor
    Bonus_Rect.left = X;
    Bonus_Rect.top = Y;
    Bonus_Rect.right = Bonus_Rect.left + Common::Block_Width * Common::Extent;
    Bonus_Rect.bottom = Bonus_Rect.top + Common::Block_Height * Common::Extent;

    Prev_Bonus_Rect = Bonus_Rect;
}

void Bonus::Draw(HDC hdc, RECT& paint_area) {
    RECT destination_rect;

    //If last bonus rectangle crossed the paint area -> redraw it
    if (IntersectRect(&destination_rect, &paint_area, &Prev_Bonus_Rect)) {
        //Clear BG
        SelectObject(hdc, Common::BG_Pen);
        SelectObject(hdc, Common::BG_Brush);

        Rectangle(hdc, Prev_Bonus_Rect.left, Prev_Bonus_Rect.top, Prev_Bonus_Rect.right - 1, Prev_Bonus_Rect.bottom - 1);
    }

    if (Got_Hit == true) {
        Finished = true;
        return;
    }

    //If bonus rectangle crossed the paint area -> use animation
    if (IntersectRect(&destination_rect, &paint_area, &Bonus_Rect)) {
        Draw_Block_Animation(hdc);
    }

}

void Bonus::Animate() {
    //Check our falling process -> redrawing the block
    if (Got_Hit || Finished) return;

    if (Bonus_Rect.top > Common::Max_Y_Pos * Common::Extent + Common::Level_Y_Offset * 2) {
        Finalize();
        return;
    }

    Prev_Bonus_Rect = Bonus_Rect;

    ++Action_Step;
    if (Action_Step % 2 == 0) ++Step;

    Y += Common::Extent;
    Bonus_Rect.top += Common::Extent;
    Bonus_Rect.bottom += Common::Extent;

    InvalidateRect(Common::Hwnd, &Prev_Bonus_Rect, FALSE);
    InvalidateRect(Common::Hwnd, &Bonus_Rect, FALSE);
}

bool Bonus::Is_Finished() {
    return Finished;
}

void Bonus::Get_Bonus_Rect(RECT& bonus_rect) {
    bonus_rect = Bonus_Rect;
}

void Bonus::Finalize() {
    Got_Hit = true;

    InvalidateRect(Common::Hwnd, &Prev_Bonus_Rect, FALSE);
    InvalidateRect(Common::Hwnd, &Bonus_Rect, FALSE);
}

void Bonus::Change_BG_Color(EBlock_Type block_type, HPEN& front_pen, HBRUSH& front_brush, HPEN& back_pen, HBRUSH& back_brush) {
    //We can use drawing only to existing bricks
    if (!(block_type == BT_Blue || block_type == BT_Green || block_type == BT_Red || block_type == BT_Yellow)) return;
    else {
        if (block_type == BT_Blue) {
            front_pen = Common::Blue_Pen;
            front_brush = Common::Blue_Brush;

            back_pen = Common::Yellow_Pen;
            back_brush = Common::Yellow_Brush;
        }
        else if (block_type == BT_Yellow) {
            front_pen = Common::Yellow_Pen;
            front_brush = Common::Yellow_Brush;

            back_pen = Common::Blue_Pen;
            back_brush = Common::Blue_Brush;
        }
        else if (block_type == BT_Green) {
            front_pen = Common::Green_Pen;
            front_brush = Common::Green_Brush;

            back_pen = Common::Red_Pen;
            back_brush = Common::Red_Brush;
        }
        else if (block_type == BT_Red) {
            front_pen = Common::Red_Pen;
            front_brush = Common::Red_Brush;

            back_pen = Common::Green_Pen;
            back_brush = Common::Green_Brush;
        }
    }
}

void Bonus::Draw_Block_Animation(HDC hdc) {
    //It draws falling of the bonuses

    //Translation of old drawing area to new, which can be rotated in every angle we want to
    XFORM xForm, old_xForm;
    double offset;
    double rotation_angle;
    
    HPEN front_pen, back_pen;
    HBRUSH front_brush, back_brush;

    rotation_angle = 2.0 * M_PI / 16.0 * Step;

    if (Step >= 8)Step = 8;

    Change_BG_Color(Block_Type, front_pen, front_brush, back_pen, back_brush);

    if (Step == 4) {// || Step == 12

        //Draw front color
        SelectObject(hdc, front_pen);
        SelectObject(hdc, front_brush);

        Rectangle(hdc, X, Y + Half_Height / 2 + Common::Extent, X + Common::Block_Width * Common::Extent, Y + Half_Height + Common::Extent);

        //Draw back color
        SelectObject(hdc, back_pen);
        SelectObject(hdc, back_brush);

        Rectangle(hdc, X, Y + Half_Height / 2 + Common::Extent, X + Common::Block_Width * Common::Extent, Y + Half_Height);

    }
    else {
        //Editing the matrix of the drawing area
        xForm.eM11 = 1.0f;
        xForm.eM12 = 0.0f;
        xForm.eM21 = 0.0f;
        xForm.eM22 = (float)cos(rotation_angle);
        xForm.eDx = (float)X;
        xForm.eDy = (float)Y + (float)Half_Height;
        GetWorldTransform(hdc, &old_xForm);
        SetWorldTransform(hdc, &xForm);

        offset = 3.0 * (1.0 - fabs(xForm.eM22)) * (double)Common::Extent;

        if (Step > 4) Draw_Front_Block_Animation(hdc, front_pen, front_brush, back_pen, back_brush, offset);
        else Draw_Front_Block_Animation(hdc, back_pen, back_brush, front_pen, front_brush, offset);
        
        if (Step > 4 && Step <= 8) {//Step > 4 && Step < 12
            SelectObject(hdc, front_pen);
            SelectObject(hdc, front_brush);
            if (Bonus_Type == BNT_Tripple_Ball) {
                Ellipse(hdc, 5 * Common::Extent, -Half_Height + 2, 10 * Common::Extent, Half_Height - 2);
            }
            else if (Bonus_Type == BNT_Additional_Life) {
                Rectangle(hdc, 5 * Common::Extent, -Half_Height / 4 + 1, 10 * Common::Extent, Half_Height / 4 - 1);
                Rectangle(hdc, (Common::Block_Width / 2) * Common::Extent, -2 * Common::Extent, (Common::Block_Width / 2) * Common::Extent + Common::Extent, 2 * Common::Extent);
            }
            else if(Bonus_Type == BNT_Floor) {
                Rectangle(hdc, 5 * Common::Extent, -Half_Height / 4 + 1, 10 * Common::Extent, Half_Height / 4 - 1);
            } else return;
        
        }

        //Return it to the normal values
        SetWorldTransform(hdc, &old_xForm);
    }
}

void Bonus::Draw_Front_Block_Animation(HDC hdc, HPEN& first_pen, HBRUSH& first_brush, HPEN& second_pen, HBRUSH& second_brush, double& offset) {
    
    SelectObject(hdc, first_pen);//back
    SelectObject(hdc, first_brush);

    Rectangle(hdc, 0, -Half_Height - (int)round(offset), Common::Block_Width * Common::Extent, Half_Height - (int)round(offset));                   

    SelectObject(hdc, second_pen);//front
    SelectObject(hdc, second_brush);

    Rectangle(hdc, 0, -Half_Height, Common::Block_Width * Common::Extent, Half_Height);
}

void Bonus::Test_Falling_Bonus(HDC hdc)
{
    int X_pos = Common::Cell_Width * Common::Extent;

    for (int i = 0; i < 9; i++) {
        Draw_Block_Animation(hdc);

        X += X_pos;
        Bonus_Rect.left += X_pos;
        Bonus_Rect.right += X_pos;

        ++Step;
    }

}
///////////////////////////////////////////////////////////////////////