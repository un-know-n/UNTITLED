
#include "Level.h"

//          LEVEL

char Level::Level_01[Common::Level_X_Elems][Common::Level_Y_Elems] = {
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

//char Level::Level_01[Common::Level_X_Elems][Common::Level_Y_Elems] = {
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//};

//char Level::Level_02[Common::Level_X_Elems][Common::Level_Y_Elems] = {
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
//    2, 2, 2, 4, 4, 2, 2, 4, 4, 2, 2, 2,
//    2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2,
//    2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2,
//    2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2,
//    2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2,
//    2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2,
//    2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2,
//    2, 2, 2, 4, 4, 4, 4, 4, 4, 2, 2, 2,
//    2, 2, 2, 2, 4, 4, 4, 4, 2, 2, 2, 2,
//    2, 2, 2, 2, 2, 4, 4, 2, 2, 2, 2, 2,
//    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//};
//
//char Level::Level_03[Common::Level_X_Elems][Common::Level_Y_Elems] = {
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
//    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
//    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
//    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
//    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
//    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
//    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
//    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//};

//char Level::Test[Common::Level_X_Elems][Common::Level_Y_Elems] = {
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

Level::Level() : Level_Area{}
{//Constructor
}

void Level::Init(){
    
    //Creation of the rectangle in which level is put
    Level_Area.left = Common::Level_X_Offset * Common::Extent;
    Level_Area.top = Common::Level_Y_Offset * Common::Extent;
    Level_Area.right = Level_Area.left + Common::Cell_Width * Common::Level_X_Elems * Common::Extent;
    Level_Area.bottom = Level_Area.top + Common::Cell_Height * Common::Level_Y_Elems * Common::Extent;

    //Initializing all the elements of current level with zero values
    memset(Current_Level, 0, sizeof(Current_Level));
}

void Level::Set_Level(char level[Common::Level_X_Elems][Common::Level_Y_Elems]) {
    //Copying needed level to our current level
    memcpy(Current_Level, level, sizeof(Current_Level));
}

void Level::Draw_Block(HDC hdc, RECT &block_area, EBlock_Type block_type) {
    //It draws different types of game blocks 

    HPEN pen;
    HBRUSH brush;

    //Depending on the type of the block we apply current pen and brush
    switch (block_type) {
    case BT_Green:
        pen = Common::Green_Pen;
        brush = Common::Green_Brush;
        break;
    case BT_Blue:
        pen = Common::Blue_Pen;
        brush = Common::Blue_Brush;
        break;
    case BT_Red:
        pen = Common::Red_Pen;
        brush = Common::Red_Brush;
        break;
    case BT_Yellow:
        pen = Common::Yellow_Pen;
        brush = Common::Yellow_Brush;
        break;
    case BT_None: return;
    default: return;
    }
    SelectObject(hdc, pen);
    SelectObject(hdc, brush);
    Rectangle(hdc, block_area.left, block_area.top, block_area.right - 1, block_area.bottom - 1);
}

void Level::Design_Objects(HDC hdc, RECT& paint_area, Object_Designer** object_array, int max_counter) {
    //Redrawing of every element in array for one step
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
    if(next_y_pos > (Common::Level_X_Elems) * Common::Cell_Height + Common::Block_Height) return false;

    for (int i = Common::Level_Y_Elems; i >= 0; i--) { 
        //Calculating top and bottom sides of the current block
        Current_Block_Top_Y_Pos = i * Common::Cell_Height;
        Current_Block_Bottom_Y_Pos = Current_Block_Top_Y_Pos + Common::Block_Height;
        
        for (int j = 0; j <= Common::Level_X_Elems; j++) { 
            //if there`s no brick -> miss that iteration
            if (Current_Level[i][j] == 0) continue;

            //Calculating left and right sides of the current block
            Current_Block_Left_Side = Common::Level_X_Offset + j * Common::Cell_Width;
            Current_Block_Right_Side = Current_Block_Left_Side + Common::Block_Width;

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
        Current_Block_Bottom_Y_Pos -= Common::Cell_Height;
    }

    return false;
}

void Level::Draw(HDC hdc, RECT& paint_area) {
    //It draws level map

    //Bonus falling_bonus(BT_Blue, BNT_Floor, 20 * Common::Extent, 150 * Common::Extent);
    //falling_bonus.Test_Falling_Bonus(hdc);

    RECT destination_rect, block_area;

    //if level area croses paint area -> redraw elems
    if ((IntersectRect(&destination_rect, &paint_area, &Level_Area))) {
        for (int i = 0; i < Common::Level_X_Elems; i++) {
            for (int j = 0; j < Common::Level_Y_Elems; j++) {
                block_area.left = (Common::Level_X_Offset + j * Common::Cell_Width) * Common::Extent;
                block_area.top = (Common::Level_Y_Offset + i * Common::Cell_Height) * Common::Extent;
                block_area.right = block_area.left + Common::Block_Width * Common::Extent;
                block_area.bottom = block_area.top + Common::Block_Height * Common::Extent;
                if ((IntersectRect(&destination_rect, &paint_area, &block_area))) {
                    Draw_Block(hdc, block_area, (EBlock_Type)Current_Level[i][j]);
                }
            }
        }

        //Design_Objects(hdc, paint_area, (Object_Designer**)&Fading, Common::Max_Fading_Count);

        //Redraw every fading block on its own time
        for (auto* fading : Fading) {
            fading->Draw(hdc, paint_area);
        }
    }

    //Design_Objects(hdc, paint_area, (Object_Designer**)&Falling, Common::Max_Falling_Count);

    //Redraw evere bonus on its own time
    for (auto* falling : Falling) {
        falling->Draw(hdc, paint_area);
    }

}

bool Level::Is_Level_Done() {
    //It checks if we have no blocks left on the map
    int level_blocks_counter = 0;
    for (int i = 0; i < Common::Level_X_Elems; i++) {
        for (int j = 0; j < Common::Level_Y_Elems; j++) {
            if (Current_Level[i][j] != 0) ++level_blocks_counter;
        }
    }
    if (level_blocks_counter == 0) return true;
    return false;
}

void Level::Animate() {
    //It continues/starts animation
    Animate_Objects(Fading);
    Animate_Objects(Falling);
}

void Level::Suspend_Animation() {
    //It stops animation with object deleting
    Delete_Objects(Fading);
    Delete_Objects(Falling);
}

void Level::Delete_Objects(std::vector<Object_Designer *> & vector_array) {
    //Creation of the iterator with specified vector type
    std::vector<Object_Designer *>::iterator it;

    //Check all the elems in vector and delete them
    for (it = vector_array.begin(); it != vector_array.end(); it++) delete* it;

    //Erase the vector itself
    vector_array.erase(vector_array.begin(), vector_array.end());
}

bool Level::Is_Finished() {
    //There`s nothing
    return false;
}

bool Level::Check_Horizontal_Hit(int level_y, int level_x, double next_x_pos, double next_y_pos, Ball* ball, double & reflection_pos) {
    double direction = ball->Get_Direction();
    
    if (ball->Is_Going_Up()) {
        //Check bottom line of the block
        if (Dot_Circle_Hit(next_y_pos - Current_Block_Bottom_Y_Pos, next_x_pos, Current_Block_Left_Side, Current_Block_Right_Side, ball->Radius, reflection_pos)) { 
            //Check if we can reflect our ball down
            if (level_y < Common::Level_X_Elems - 1 && Current_Level[level_y + 1][level_x] == 0) return true;
            else return false;
        }
    }
    else {
        //Check upper line of the block
        if (Dot_Circle_Hit(next_y_pos - Current_Block_Top_Y_Pos, next_x_pos, Current_Block_Left_Side, Current_Block_Right_Side, ball->Radius, reflection_pos)) { 
            //Check if we can reflect our ball up
            if (level_y > 0 && Current_Level[level_y - 1][level_x] == 0) return true;
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
            if (level_x < Common::Level_X_Elems && Current_Level[level_y][level_x + 1] == 0) return true;
            else return false;
        }
    }
    else {
        //Check left side of the block
        if (Dot_Circle_Hit(Current_Block_Left_Side - next_x_pos, next_y_pos, Current_Block_Top_Y_Pos, Current_Block_Bottom_Y_Pos, ball->Radius, reflection_pos)) { 
            //Check if we can reflect our ball to the left side
            if (level_x > 0 && Current_Level[level_y][level_x - 1] == 0) return true;
            else return false;
        }
    }

    return false;
}

void Level::What_After_Struck(int y_coord, int x_coord) {
    EBlock_Type block_type;

    //Creation of variable which contains the color of the block
    block_type = (EBlock_Type)Current_Level[y_coord][x_coord];

    //Check if we can add bonus
    if (!Add_Bonus(y_coord, x_coord, block_type)) Add_Fading(y_coord, x_coord, block_type);
}

void Level::Add_Fading(int y_coord, int x_coord, EBlock_Type block_type) {
    
    Fade_Block* fading;

    //Check if our number of fading blocks is within the array
    if (Fading.size() >= Common::Max_Fading_Count) return;

    if(block_type == BT_None) return;

    //Creation of new poiner to the current block
    fading = new Fade_Block(block_type, x_coord, y_coord);

    //Pushing it to the dynamical array
    Falling.push_back(fading);
    Current_Level[y_coord][x_coord] = BT_None;
}

void Level::Animate_Objects(std::vector<Object_Designer *> &vector_array) {

    //Creation of the iterator with specified vector type
    std::vector<Object_Designer *>::iterator it;

    //Check all the elems in vector -> animate || finished -> erase the elem
    for (it = vector_array.begin(); it != vector_array.end(); it++) {
        (*it)->Animate();
        if ((*it)->Is_Finished()) {
            delete *it;
            it = vector_array.erase(it);
        }
    }
}

bool Level::Add_Bonus(int y_coord, int x_coord, EBlock_Type block_type) {
    EBonus_Type bonus_type;
    Bonus* falling_bonus;
    int bonus_x, bonus_y;
    int bonus_random;

    //Creation of the random bonus and probability distribution to every bonus type
    bonus_random = rand() % 20;
    if (bonus_random % 3 == 0) bonus_type = BNT_Floor;
    else if(bonus_random % 2 == 0) bonus_type = BNT_Tripple_Ball;
    else bonus_type = BNT_Additional_Life;

    //bonus_type = BNT_Floor;

    //Applying the coords to the current bonus
    bonus_x = (x_coord * Common::Cell_Width + Common::Level_X_Offset) * Common::Extent;
    bonus_y = (y_coord * Common::Cell_Height + Common::Level_Y_Offset) * Common::Extent;
    
    //If we have place in our array -> go on
    if (Falling.size() < Common::Max_Falling_Count) {
        if (rand() % 2 == 0) {
            //Creation of new example of bonus
            falling_bonus = new Bonus(block_type, bonus_type, bonus_x, bonus_y);

            //Pushing it to the array
            Falling.push_back(falling_bonus);
            
            //Replacing current block with void
            Current_Level[y_coord][x_coord] = BT_None;
            
            return true;
        }
    }
    return false;
}

bool Level::Have_Next_Bonus(int& index, Bonus** falling_bonus) {
    //If we have place in array -> go on
    if (index < Falling.size()) {
        //Applying address of the next elem in array to our pointer
        *falling_bonus = (Bonus *)Falling[index++];
        return true;
    }

    return false;
}

/////////////////////////////////////////////////////////////////////