
#include "Level.h"

//      BONUS

Bonus::Bonus(EBlock_Type block_type, EBonus_Type bonus_type, int x, int y)
    : Block_Type(block_type), Bonus_Type(bonus_type), X(x), Y(y), Step(0), Action_Step(0)
{//Constructor
    Bonus_Rect.left = X;//x * Config::Block_Width * Config::Extent + Config::Level_X_Offset    I var
    Bonus_Rect.top = Y;//(Config::Level_Y_Offset + Y * Config::Cell_Height) * Config::Extent    II var
    Bonus_Rect.right = Bonus_Rect.left + Config::Block_Width * Config::Extent;
    Bonus_Rect.bottom = Bonus_Rect.top + Config::Block_Height * Config::Extent;

    Prev_Bonus_Rect = Bonus_Rect;
}

void Bonus::Draw(HDC hdc, RECT &paint_area) {
    RECT destination_rect;

    if (IntersectRect(&destination_rect, &paint_area, &Prev_Bonus_Rect)) {
        //Clear BG
        SelectObject(hdc, Config::BG_Pen);
        SelectObject(hdc, Config::BG_Brush);

        Rectangle(hdc, Prev_Bonus_Rect.left, Prev_Bonus_Rect.top, Prev_Bonus_Rect.right - 1, Prev_Bonus_Rect.bottom - 1);
    }

    if (IntersectRect(&destination_rect, &paint_area, &Bonus_Rect)) {
        Draw_Block_Animation(hdc);
    }
        
}

void Bonus::Act() {
    //Check our falling process -> redrawing the block
    Prev_Bonus_Rect = Bonus_Rect;
    
    ++Action_Step;
    if (Action_Step % 2 == 0) ++Step;

    Y += Config::Extent;
    Bonus_Rect.top += Config::Extent;
    Bonus_Rect.bottom += Config::Extent;

    //if (Fade_Step < Max_Fade_Step - 1) {
        //++Fade_Step;
    InvalidateRect(Config::Hwnd, &Prev_Bonus_Rect, FALSE);
    InvalidateRect(Config::Hwnd, &Bonus_Rect, FALSE);
    //}
}

bool Bonus::Is_Finished() {
    if (Bonus_Rect.top > Config::Max_Y_Pos * Config::Extent + Config::Level_Y_Offset * 2) return true;
    else return false;
}


void Bonus::Change_BG_Color(EBlock_Type block_type, HPEN& front_pen, HBRUSH& front_brush, HPEN& back_pen, HBRUSH& back_brush) {
    //We can change only existing bricks
    if (!(block_type == BT_Blue || block_type == BT_Green || block_type == BT_Red || block_type == BT_Yellow)) return;
    else {
        if (block_type == BT_Blue) {
            front_pen = Config::Blue_Pen;
            front_brush = Config::Blue_Brush;

            back_pen = Config::Yellow_Pen;
            back_brush = Config::Yellow_Brush;
        }
        else if (block_type == BT_Yellow) {
            front_pen = Config::Yellow_Pen;
            front_brush = Config::Yellow_Brush;

            back_pen = Config::Blue_Pen;
            back_brush = Config::Blue_Brush;
        }
        else if (block_type == BT_Green) {
            front_pen = Config::Green_Pen;
            front_brush = Config::Green_Brush;

            back_pen = Config::Red_Pen;
            back_brush = Config::Red_Brush;
        }
        else if (block_type == BT_Red) {
            front_pen = Config::Red_Pen;
            front_brush = Config::Red_Brush;

            back_pen = Config::Green_Pen;
            back_brush = Config::Green_Brush;
        }
    }
}

void Bonus::Draw_Block_Animation(HDC hdc) {
    //It draws falling of the bonuses

    //Translation of old drawing area to new, which can be rotated in every angle we want to
    XFORM xForm, old_xForm;
    double offset;
    double rotation_angle;
    int half_height = Config::Block_Height * Config::Extent / 2;

    HPEN front_pen, back_pen;
    HBRUSH front_brush, back_brush;

    //HPEN TEST_front_pen, TEST_back_pen;
    //HBRUSH TEST_front_brush, TEST_back_brush;

    //TEST_front_pen = CreatePen(PS_SOLID, 0, RGB(97, 43, 43));
    //TEST_front_brush = CreateSolidBrush(RGB(97, 43, 43));
    //TEST_back_pen = CreatePen(PS_SOLID, 0, RGB(43, 63, 97));
    //TEST_back_brush = CreateSolidBrush(RGB(43, 63, 97));

    //Check if rotation step is more than 16 -> change it
    Step = Step % 16;
    if (Step < 8) {
        rotation_angle = 2.0 * M_PI / 16.0 * Step;
    }
    else {
        rotation_angle = 2.0 * M_PI / 16.0 * (Step - 8);
    }

    Change_BG_Color(Block_Type, front_pen, front_brush, back_pen, back_brush);

    if (Step == 4 || Step == 12) {

        //Draw front color
        SelectObject(hdc, front_pen);
        SelectObject(hdc, front_brush);

        Rectangle(hdc, X, Y + half_height / 2 + Config::Extent, X + Config::Block_Width * Config::Extent, Y + half_height + Config::Extent);

        //Draw back color
        SelectObject(hdc, back_pen);
        SelectObject(hdc, back_brush);

        Rectangle(hdc, X, Y + half_height / 2 + Config::Extent, X + Config::Block_Width * Config::Extent, Y + half_height);

    }
    else {
        //Editing the matrix of the drawing area
        xForm.eM11 = 1.0f;
        xForm.eM12 = 0.0f;
        xForm.eM21 = 0.0f;
        xForm.eM22 = (float)cos(rotation_angle);
        xForm.eDx = (float)X;
        xForm.eDy = (float)Y + (float)half_height;
        GetWorldTransform(hdc, &old_xForm);
        SetWorldTransform(hdc, &xForm);

        SelectObject(hdc, back_pen);
        SelectObject(hdc, back_brush);

        offset = 3.0 * (1.0 - fabs(xForm.eM22)) * (double)Config::Extent;

        Rectangle(hdc, 0, -half_height - (int)round(offset), Config::Block_Width * Config::Extent, half_height - (int)round(offset));//0, -half_height - (int)round(offset), Config::Block_Width * Config::Extent, half_height - (int)round(offset)                   

        SelectObject(hdc, front_pen);
        SelectObject(hdc, front_brush);

        Rectangle(hdc, 0, -half_height, Config::Block_Width * Config::Extent, half_height);//0, -half_height, Config::Block_Width * Config::Extent, half_height

        if (Step > 4 && Step < 12) {
            if (Bonus_Type == BNT_Circle) {
                SelectObject(hdc, back_pen);
                SelectObject(hdc, back_brush);
                Ellipse(hdc, 0 + 5 * Config::Extent, -half_height + 2, 0 + 10 * Config::Extent, half_height - 2);
            }
        }

        //Return it to the normal values
        SetWorldTransform(hdc, &old_xForm);
    }
}

//          LEVEL

char Level_01[Config::Level_X_Elems][Config::Level_Y_Elems] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

//char Level_01[Config::Level_X_Elems][Config::Level_Y_Elems] = {
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2,
//    0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
//    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//    0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0,
//    0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0,
//    0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
//    0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//};

//char Level_01[Config::Level_X_Elems][Config::Level_Y_Elems] = {
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//};

Level::Level() : Level_Area{}, Fading_Count(0), Falling_Count(0)
{//Constructor
}

void Level::Init(){
    
    //Creation of the rectangle in which level is put
    Level_Area.left = Config::Level_X_Offset * Config::Extent;
    Level_Area.top = Config::Level_Y_Offset * Config::Extent;
    Level_Area.right = Level_Area.left + Config::Cell_Width * Config::Level_X_Elems * Config::Extent;
    Level_Area.bottom = Level_Area.top + Config::Cell_Height * Config::Level_Y_Elems * Config::Extent;
}

void Level::Draw_Block(HDC hdc, int x, int y, EBlock_Type block_type) {
    //It draws different types of game blocks 

    HPEN pen;
    HBRUSH brush;

    switch (block_type) {
    case BT_Green:
        pen = Config::Green_Pen;
        brush = Config::Green_Brush;
        break;
    case BT_Blue:
        pen = Config::Blue_Pen;
        brush = Config::Blue_Brush;
        break;
    case BT_Red:
        pen = Config::Red_Pen;
        brush = Config::Red_Brush;
        break;
    case BT_Yellow:
        pen = Config::Yellow_Pen;
        brush = Config::Yellow_Brush;
        break;
    case BT_None: return;
    default: return;
    }
    SelectObject(hdc, pen);
    SelectObject(hdc, brush);
    Rectangle(hdc, x * Config::Extent, y * Config::Extent, (x + Config::Block_Width) * Config::Extent - 1, (y + Config::Block_Height) * Config::Extent - 1);
    //RoundRect(hdc, x * Config::Extent, y * Config::Extent, (x + Config::Block_Width) * Config::Extent, (y + Config::Block_Height) * Config::Extent, 3, 3);
}

void Level::Draw(HDC hdc, RECT &paint_area) {
    //It draws level map

    RECT destination_rect;

    if ((IntersectRect(&destination_rect, &paint_area, &Level_Area))) {
        for (int i = 0; i < 14; i++) {
            for (int j = 0; j < 12; j++) {
                Draw_Block(hdc, Config::Level_X_Offset + j * Config::Cell_Width,
                    Config::Level_Y_Offset + i * Config::Cell_Height, (EBlock_Type)Level_01[i][j]);
            }
        }

        //Draw fading blocks if we need to
        for (int i = 0; i < Config::Max_Fading_Count; i++) {
            if (Fading[i] != 0) Fading[i]->Draw(hdc);
        }
               
    }

    //Draw bonuses if we need to
    for (int i = 0; i < Config::Max_Falling_Count; i++) {
        if (Falling[i] != 0) Falling[i]->Draw(hdc, paint_area);
    }
    
}

bool Level::Check_Colision(double next_x_pos, double next_y_pos, Ball* ball) {
    //If struck with blocks

    double x, y;
    double direction = ball->Get_Direction();
    bool got_horizontal_hit, got_vertical_hit;
    double horizontal_reflect_pos, vertical_reflect_pos;

    //Check our y position relatively to max y element
    if(next_y_pos > (Config::Level_Y_Elems) * Config::Cell_Height + Config::Block_Height) return false;

    for (int i = Config::Level_Y_Elems; i >= 0; i--) { 
        //Calculating top and bottom sides of the current block
        Current_Block_Top_Y_Pos = i * Config::Cell_Height;
        Current_Block_Bottom_Y_Pos = Current_Block_Top_Y_Pos + Config::Block_Height;
        
        for (int j = 0; j <= Config::Level_X_Elems; j++) { 
            if (Level_01[i][j] == 0) continue;

            //Calculating left and right sides of the current block
            Current_Block_Left_Side = Config::Level_X_Offset + j * Config::Cell_Width;
            Current_Block_Right_Side = Current_Block_Left_Side + Config::Block_Width;

            //Making variables which helps us to see which side was collided
            got_horizontal_hit = Check_Horizontal_Hit(i, j,next_x_pos, next_y_pos, ball, horizontal_reflect_pos);
            got_vertical_hit = Check_Vertical_Hit(i, j, next_x_pos, next_y_pos, ball, vertical_reflect_pos);

            //Check the collision scenario
            if(got_horizontal_hit && got_vertical_hit){
                if(horizontal_reflect_pos <= vertical_reflect_pos){
                    ball->Is_Vertical_Reflect(false);
                    What_After_Struck(i, j);
                } else {
                    ball->Is_Vertical_Reflect(true);
                    What_After_Struck(i, j);
                }
            } else if(got_horizontal_hit){
                ball->Is_Vertical_Reflect(false);
                What_After_Struck(i, j);
                return true;
            } else if(got_vertical_hit){
                ball->Is_Vertical_Reflect(true);
                What_After_Struck(i, j);
                return true;
            }
        }
        //Going down to the next row of blocks
        Current_Block_Bottom_Y_Pos -= Config::Cell_Height;
    }

    return false;
}

bool Level::Check_Horizontal_Hit(int level_y, int level_x, double next_x_pos, double next_y_pos, Ball* ball, double & reflection_pos) {
    double direction = ball->Get_Direction();
    
    if (ball->Is_Going_Up()) {
        //Check bottom line of the block
        if (Dot_Circle_Hit(next_y_pos - Current_Block_Bottom_Y_Pos, next_x_pos, Current_Block_Left_Side, Current_Block_Right_Side, ball->Radius, reflection_pos)) { 
            //Check if we can reflect our ball down
            if (level_y < Config::Level_Y_Elems - 1 && Level_01[level_y + 1][level_x] == 0) return true;
            else return false;
        }
    }
    else {
        //Check upper line of the block
        if (Dot_Circle_Hit(next_y_pos - Current_Block_Top_Y_Pos, next_x_pos, Current_Block_Left_Side, Current_Block_Right_Side, ball->Radius, reflection_pos)) { 
            //Check if we can reflect our ball up
            if (level_y > 0 && Level_01[level_y - 1][level_x] == 0) return true;
            else return false;
        }
    }

    return false;
}

bool Level::Check_Vertical_Hit(int level_y, int level_x, double next_x_pos, double next_y_pos, Ball* ball, double &reflection_pos) {
    double direction = ball->Get_Direction();

    if (ball->Is_Going_Left()) {
        //Check right side of the block
        if (Dot_Circle_Hit(Current_Block_Right_Side - next_x_pos, next_y_pos, Current_Block_Top_Y_Pos, Current_Block_Bottom_Y_Pos, ball->Radius, reflection_pos)) { 
            //Check if we can reflect our ball to the right side
            if (level_x < Config::Level_X_Elems && Level_01[level_y][level_x + 1] == 0) return true;
            else return false;
        }
    }
    else {
        //Check left side of the block
        if (Dot_Circle_Hit(Current_Block_Left_Side - next_x_pos, next_y_pos, Current_Block_Top_Y_Pos, Current_Block_Bottom_Y_Pos, ball->Radius, reflection_pos)) { 
            //Check if we can reflect our ball to the left side
            if (level_x > 0 && Level_01[level_y][level_x - 1] == 0) return true;
            else return false;
        }
    }

    return false;
}

void Level::What_After_Struck(int y_coord, int x_coord) {
    EBlock_Type block_type;

    //Creation of variable which contains the color of the block
    block_type = (EBlock_Type)Level_01[y_coord][x_coord];

    //Check if we can add bonus
    if (!Add_Bonus(y_coord, x_coord, block_type)) Add_Fading(y_coord, x_coord, block_type);
}

void Level::Add_Fading(int y_coord, int x_coord, EBlock_Type block_type) {
    
    Fade_Block* fading;

    //Check if our number of fading blocks is within the array
    if (Fading_Count >= Config::Max_Fading_Count) return;

    if(block_type == BT_None) return;

    //Creation of new poiner to the current block
    fading = new Fade_Block(block_type, x_coord, y_coord);

    //Check if we have place in our array and if not -> move to the next cell
    for (int i = 0; i < Config::Max_Fading_Count; i++) {
        if (Fading[i] == 0) {
            Fading[i] = fading;
            ++Fading_Count;
            break;
        }
    }
}

void Level::Act() {
    //We`re making every element in our array to continue their action till the end
    for (int i = 0; i < Config::Max_Fading_Count; i++) {
        if (Fading[i] != 0) {
            Fading[i]->Act();
            if (Fading[i]->Is_Finished()) {
                delete Fading[i];
                Fading[i] = 0;
                --Fading_Count;
            }
        }
    }

    for (int i = 0; i < Config::Max_Falling_Count; i++) {
        if (Falling[i] != 0) {
            Falling[i]->Act();
            if (Falling[i]->Is_Finished()) {
                delete Falling[i];
                Falling[i] = 0;
                --Falling_Count;
            }
        }
    }
}

bool Level::Add_Bonus(int y_coord, int x_coord, EBlock_Type block_type) {
    //EBlock_Type block_type;
    Bonus* falling_bonus;
    int bonus_x, bonus_y;
    //block_type = (EBlock_Type)Level_01[y_coord][x_coord];
    bonus_x = (x_coord * Config::Cell_Width + Config::Level_X_Offset) * Config::Extent;
    bonus_y = (y_coord * Config::Cell_Height + Config::Level_Y_Offset) * Config::Extent;
    
    if (Falling_Count < Config::Max_Falling_Count) {
        falling_bonus = new Bonus(block_type, BNT_Circle, bonus_x, bonus_y);
        //if (rand() % 1 == 0) {

            for (int i = 0; i < Config::Max_Falling_Count; i++) {
                if (Falling[i] == 0) {
                    Falling[i] = falling_bonus;
                    ++Falling_Count;
                    Level_01[y_coord][x_coord] = BT_None;
                    break;
                }
            }
            return true;
        //}
    }
    return false;
}

/////////////////////////////////////////////////////////////////////