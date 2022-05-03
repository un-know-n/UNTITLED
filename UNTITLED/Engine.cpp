
#include "Engine.h"

//          HEAD_ENGINE

Head_Engine::Head_Engine() : Game_State(GS_GameOver), Life_Counter(1), Game_Done(false), Game_Over(false)
{//Constructor
    Level_Area_Rect.left = Common::Level_X_Offset * Common::Extent;
    Level_Area_Rect.top = Common::Level_Y_Offset * Common::Extent;
    Level_Area_Rect.right = Common::Level_Y_Elems * Common::Cell_Width * Common::Extent + Common::Level_X_Offset * Common::Extent;
    Level_Area_Rect.bottom = Common::Max_Y_Pos * Common::Extent;
}

void Head_Engine::Init_Engine(HWND hwnd) {
    //It initializes game engine
    //Initialization of specific random subsequence to our program

    //////      "REAL" RANDOM SYSTEM        //////
    SYSTEMTIME system_time;
    FILETIME file_time;

    GetSystemTime(&system_time);
    SystemTimeToFileTime(&system_time, &file_time);

    srand(file_time.dwLowDateTime);
    //////////////////////////////////////////////

    Common::Hwnd = hwnd;

    Common::Setup_Colors();

    Fade_Block::Set_Color();

    /////// Initialization of main subsequences ///////
    Level.Init();
    Border.Init();
    Platform.Init();

    for (int i = 0; i < Common::Max_Ball_Count; i++) {
        Ball_Pile.Balls[i].Init();

        Ball_Pile.Balls[i].Add_Hit_Checker(&Border);
        Ball_Pile.Balls[i].Add_Hit_Checker(&Level);
        Ball_Pile.Balls[i].Add_Hit_Checker(&Platform);
    }  
    ///////////////////////////////////////////////////

    Level.Set_Level(Level::Level_01);
    Platform.Redraw();

    SetTimer(Common::Hwnd, Timer_ID, 1000 / Common::FPS, 0);

    //Clearing of the main object array
    memset(Object_Driver, 0, sizeof(Object_Driver));
    Object_Driver[0] = &Platform;
    Object_Driver[1] = &Ball_Pile;

    //Pushing main subsequences into modules
    Module.push_back(&Level);
    Module.push_back(&Border);
    Module.push_back(&Platform);
    Module.push_back(&Ball_Pile);
}

void Head_Engine::Draw_Frame(HDC hdc, RECT &paint_area) {
    //It draws game screen (hdc - handle to device context)
    SetGraphicsMode(hdc, GM_ADVANCED);

    //Redrawing every module in one step
    for (auto *current_module : Module)
        current_module->Draw(hdc, paint_area);
}

void Head_Engine::Draw_Ending(HDC hdc, RECT& paint_area) {
    //If game is finished(won) -> we use that func
    Platform.Set_State(PS_None);
    Ball_Pile.Disable_Balls();

    Draw_Level_Rect(hdc);
    TextOut(hdc, 240, 300, TEXT("You`ve finished the game"), strlen("You`ve finished the game"));
}

void Head_Engine::Draw_GameOver(HDC hdc, RECT& paint_area) {
    //If game is lost -> we use that func

    Draw_Level_Rect(hdc);
    TextOut(hdc, 272, 300, TEXT("GAME OVER"), strlen("GAME OVER"));
}

void Head_Engine::Draw_Level_Rect(HDC hdc) {
    SelectObject(hdc, Common::BG_Pen);
    SelectObject(hdc, Common::BG_Brush);

    Rectangle(hdc, Level_Area_Rect.left, Level_Area_Rect.top, Level_Area_Rect.right, Level_Area_Rect.bottom);
}

int Head_Engine::On_Key(EKey_Type key_type, int button, HWND hwnd, bool is_key_down) {
    //Check what type of key is currently pressed
    switch (key_type) {
    case KT_Left:
        Platform.Move_To_Left(true, is_key_down);
        break;
    case KT_Right:
        Platform.Move_To_Left(false, is_key_down);
        break;
    case KT_Space:
        if (is_key_down) {
            if (Platform.Get_State() == PS_Ready) {
                Ball_Pile.Release_Balls(Platform.X_Position + Platform.Width - Platform.Width / 4 + 2);
                Platform.Set_State(PS_Normal);
            }
        }        
        break;
    case KT_Escape:
        DestroyWindow(hwnd);
        break;
    }
    switch (button) {
    case Button_A:
        Platform.Move_To_Left(true, is_key_down);
        break;
    case Button_D:
        Platform.Move_To_Left(false, is_key_down);
        break;
    }
    return 0;
}

int Head_Engine::On_Timer() {
    //Timer that is used to do the actions in time we ask to
    ++Common::Tick;

    if (Common::Have_Floor == true) ++Common::Floor_Tick;
    if (Common::Floor_Tick % 250 == 0) {
        Common::Have_Floor = false;
        Common::Floor_Tick = 0;
        Border.Redraw_Floor();
    }

    switch (Game_State) {
    case GS_Test:
        Ball_Pile.Balls[0].Set_Test();
        Platform.Set_State(PS_Normal);
        Game_State = GS_Play;
        break;

        
    case GS_Play:
        Play_Level();
    break;
        
    case GS_GameOver:
        //if (Game_Done == true) break;
        if (Platform.Get_State() == PS_None) {
            Game_State = GS_Restart;
            Platform.Set_State(PS_StartGame);
        }
        break;

    case GS_Restart:
        if (Platform.Get_State() == PS_Ready) {
            Ball_Pile.Set_On_Platform(Platform.X_Position + Platform.Width - Platform.Width / 4 + 2);
            Game_State = GS_Play;
        }        
        break;
    }

    Animate();   

    return 0;
}

void Head_Engine::Play_Level() {
    Next_Driver_Step();

    if (Ball_Pile.If_Balls_Lost()) {
        --Life_Counter;
        Game_State = GS_Restart;
        Platform.Set_State(PS_StartGame);
        if (Life_Counter == 0) {
            Game_Over = true;
            //Gaame_State = GS_GameOaver;
            //Platform.Set_State(PS_PreEndGame);
        }
    }

    if (Level.Is_Level_Done()) {
        Game_Done = true;
    }

    /*if (Ball_Pile.Balls[0].Is_Test_Finished()) {
        Game_State = GS_Test;
    }*/
    
}

void Head_Engine::Next_Driver_Step() {
    double rest_distance, max_speed = 0.0;
    double current_speed = 0.0;

    ////    Platform moving     ////

    for (int i = 0; i < Common::Max_Driver_Count; i++) {
        if (Object_Driver[i] != 0) {
            Object_Driver[i]->Initialization();
            current_speed = Object_Driver[i]->Get_Speed();
            if (current_speed > max_speed) max_speed = current_speed;
        }
    }

    rest_distance = max_speed;

    // Saving the rest of the distance for the smooth of the moving
    while (rest_distance > 0.0) {
        for (int i = 0; i < Common::Max_Driver_Count; i++) {
            if (Object_Driver[i] != 0) Object_Driver[i]->Next_Step(max_speed);
        }
        rest_distance -= Common::Step_Size;
    }

    // Finalizing of moving of every object(redrawing them)
    for (int i = 0; i < Common::Max_Driver_Count; i++) {
        if (Object_Driver[i] != 0) {
            Object_Driver[i]->Finalization();
        }
    }
}

void Head_Engine::Animate() {
    //It animates every object that needs to be in one step
    Platform.Animate();
    Level.Animate();

    int index = 0;
    Bonus* falling_bonus;

    //If we have enough space in our array -> do something
    while (Level.Have_Next_Bonus(index, &falling_bonus)) {
        if (Platform.Got_Hit_By(falling_bonus)) {
            On_Falling_Bonus(falling_bonus);
        }
    }
}

void Head_Engine::On_Falling_Bonus(Bonus* falling_bonus) {
    //Do the action depending on the type of the bonus
    if (falling_bonus->Bonus_Type == BNT_Tripple_Ball) {
        Ball_Pile.Tripple_Balls();
    }
    else if (falling_bonus->Bonus_Type == BNT_Additional_Life) {
        if (Life_Counter < Common::Max_Life_Counter) Life_Counter++;
    }
    else if (falling_bonus->Bonus_Type == BNT_Floor) {
        Common::Have_Floor = true;
        Border.Redraw_Floor();
    }
    falling_bonus->Finalize();
}
/////////////////////////////////////////////////////////////////////