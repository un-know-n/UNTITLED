
#include "Level.h"

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

char Test[Config::Level_X_Elems][Config::Level_Y_Elems] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

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

void Level::Draw_Block(HDC hdc, RECT &block_area, EBlock_Type block_type) {
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
    Rectangle(hdc, block_area.left, block_area.top, block_area.right - 1, block_area.bottom - 1);
}

void Level::Draw(HDC hdc, RECT &paint_area) {
    //It draws level map

    //Bonus falling_bonus(BT_Blue, BNT_Floor, 20 * Config::Extent, 150 * Config::Extent);
    //falling_bonus.Test_Falling_Bonus(hdc);

    RECT destination_rect, block_area;

    if ((IntersectRect(&destination_rect, &paint_area, &Level_Area))) {
        for (int i = 0; i < 14; i++) {
            for (int j = 0; j < 12; j++) {
                block_area.left = (Config::Level_X_Offset + j * Config::Cell_Width) * Config::Extent;
                block_area.top = (Config::Level_Y_Offset + i * Config::Cell_Height) * Config::Extent;
                block_area.right = block_area.left + Config::Block_Width * Config::Extent;
                block_area.bottom = block_area.top + Config::Block_Height * Config::Extent;
                if ((IntersectRect(&destination_rect, &paint_area, &block_area))) {
                    Draw_Block(hdc, block_area, (EBlock_Type)Level_01[i][j]);
                }
            }
        }

        //Draw fading blocks if we need to
        /*for (int i = 0; i < Config::Max_Fading_Count; i++) {
            if (Fading[i] != 0) Fading[i]->Draw(hdc, paint_area);
        }*/
        
        Design_Objects(hdc, paint_area, (Object_Designer**)&Fading, Config::Max_Fading_Count);
    }

    //COPYPASTE!!!!!!!!!!!!!!!!!!!!!!!!!!

    //Draw bonuses if we need to
    /*for (int i = 0; i < Config::Max_Falling_Count; i++) {
        if (Falling[i] != 0) Falling[i]->Draw(hdc, paint_area);
    }*/

    Design_Objects(hdc, paint_area, (Object_Designer**)&Falling, Config::Max_Falling_Count);
    
}

void Level::Design_Objects(HDC hdc, RECT& paint_area, Object_Designer** object_array, int max_counter) {
    for (int i = 0; i < max_counter; i++) {
        if (object_array[i] != 0) object_array[i]->Draw(hdc, paint_area);
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
            Level_01[y_coord][x_coord] = BT_None;
            break;
        }
    }
}

void Level::Act() {
    //We`re making every element in our array to continue their action till the end
    /*for (int i = 0; i < Config::Max_Fading_Count; i++) {
        if (Fading[i] != 0) {
            Fading[i]->Act();
            if (Fading[i]->Is_Finished()) {
                delete Fading[i];
                Fading[i] = 0;
                --Fading_Count;
            }
        }
    }*/

    Act_Objects((Object_Designer**)&Fading, Config::Max_Fading_Count, Fading_Count);

    //COPYPASTE!!!!!!!!!!!!!!!!!!!!!!!!!!

    /*for (int i = 0; i < Config::Max_Falling_Count; i++) {
        if (Falling[i] != 0) {
            Falling[i]->Act();
            if (Falling[i]->Is_Finished()) {
                delete Falling[i];
                Falling[i] = 0;
                --Falling_Count;
            }
        }
    }*/

    Act_Objects((Object_Designer **)&Falling, Config::Max_Falling_Count, Falling_Count);
}

void Level::Act_Objects(Object_Designer** object_array ,int max_count, int &counter) {
    for (int i = 0; i < max_count; i++) {
        if (object_array[i] != 0) {
            object_array[i]->Act();
            if (object_array[i]->Is_Finished()) {
                delete object_array[i];
                object_array[i] = 0;
                --counter;
            }
        }
    }
}

bool Level::Add_Bonus(int y_coord, int x_coord, EBlock_Type block_type) {
    EBonus_Type bonus_type;
    Bonus* falling_bonus;
    int bonus_x, bonus_y;
    int bonus_random;

    /*bonus_random = rand() % 20;
    if (bonus_random % 2 == 0) bonus_type = BNT_Floor;
    else if(bonus_random % 3 == 0) bonus_type = BNT_Tripple_Ball;
    else bonus_type = BNT_Additional_Life;*/

    bonus_type = BNT_Floor;

    bonus_x = (x_coord * Config::Cell_Width + Config::Level_X_Offset) * Config::Extent;
    bonus_y = (y_coord * Config::Cell_Height + Config::Level_Y_Offset) * Config::Extent;
    
    if (Falling_Count < Config::Max_Falling_Count) {
        falling_bonus = new Bonus(block_type, bonus_type, bonus_x, bonus_y);
        if (rand() % 1 == 0) {

            for (int i = 0; i < Config::Max_Falling_Count; i++) {
                if (Falling[i] == 0) {
                    Falling[i] = falling_bonus;
                    ++Falling_Count;
                    Level_01[y_coord][x_coord] = BT_None;
                    break;
                }
            }
            return true;
        }
    }
    return false;
}

bool Level::Have_Next_Bonus(int& index, Bonus** falling_bonus) {
    Bonus* current_falling;

    if (Falling_Count == 0) return false;

    if (index < 0 || index > Config::Max_Falling_Count) return false;

    while (index < Config::Max_Falling_Count) {
        current_falling = Falling[index++];
        if (current_falling != 0) {
            *falling_bonus = current_falling;
            return true;
        } 
    }
    return false;
}

/////////////////////////////////////////////////////////////////////