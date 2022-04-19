
#include "Engine.h"

//          BALL_PILE


void Ball_Pile::Initialization() {
    for (int i = 0; i < Config::Max_Ball_Count; i++) Balls[i].Initialization();
}

void Ball_Pile::Finalization() {
    for (int i = 0; i < Config::Max_Ball_Count; i++) Balls[i].Finalization();
}

void Ball_Pile::Next_Step(double max_speed) {
    for (int i = 0; i < Config::Max_Ball_Count; i++) Balls[i].Next_Step(max_speed);
}

double Ball_Pile::Get_Speed() {
    double max_speed = 0.0;

    for (int i = 0; i < Config::Max_Ball_Count; i++) {
        if (Balls[i].Ball_Speed > max_speed) max_speed = Balls[i].Ball_Speed;
    }

    return max_speed;
}

void Ball_Pile::Draw(HDC hdc, RECT& paint_area) {
    for (int i = 0; i < Config::Max_Ball_Count; i++) Balls[i].Draw(hdc, paint_area);
}

void Ball_Pile::Release_Balls(double platform_pos) {
    for (int i = 0; i < Config::Max_Ball_Count; i++) {
        Balls[i].Set_State(BS_Free, platform_pos); 
    }

    //for (int i = 20; i < Config::Max_Ball_Count; i++) {
    //    //if(Balls[i].Get_State() == BS_Start)
    //    Balls[i].Set_State(BS_Disabled, 0);
    //}
}

bool Ball_Pile::If_Balls_Lost() {
    int active_balls = 0, fallen_balls = 0;

    //Balls moving
    for (int i = 0; i < Config::Max_Ball_Count; i++) {
        if (Balls[i].Get_State() == BS_Disabled) continue;

        ++active_balls;

        if (Balls[i].Get_State() == BS_None) ++fallen_balls;
    }
    if (active_balls == fallen_balls && fallen_balls != 0 && active_balls != 0) return true;
    else return false;
}



////////////////////////////////////////////////////

//          HEADENGINE

HeadEngine::HeadEngine() : Game_State(GS_GameOver)
{//Constructor
}

void HeadEngine::Init_Engine(HWND hwnd) {
    //It initializes game engine
    // Initialization of specific random subsequence to our program

    SYSTEMTIME system_time;
    FILETIME file_time;

    GetSystemTime(&system_time);
    SystemTimeToFileTime(&system_time, &file_time);

    srand(file_time.dwLowDateTime);

    Config::Hwnd = hwnd;

    Config::Setup_Colors();

    Fade_Block::Set_Color();

    Level.Init();
    Border.Init();
    Platform.Init();

    for (int i = 0; i < Config::Max_Ball_Count; i++) {
        Ball_Pile.Balls[i].Init();

        Ball_Pile.Balls[i].Add_Hit_Checker(&Border);
        Ball_Pile.Balls[i].Add_Hit_Checker(&Level);
        Ball_Pile.Balls[i].Add_Hit_Checker(&Platform);
    }  

    //Ball.Set_State(BS_Start, Platform.X_Position + Platform.Width - Platform.Width / 2 + 2);
    //Platform.Set_State(PS_StartGame);
    Platform.Redraw();
    
    SetTimer(Config::Hwnd, Timer_ID, 1000 / Config::FPS, 0);

    memset(Object_Driver, 0, sizeof(Object_Driver));
    Object_Driver[0] = &Platform;
    Object_Driver[1] = &Ball_Pile;
}

void HeadEngine::Draw_Frame(HDC hdc, RECT &paint_area) {
    //It draws game screen (hdc - handle to device context)
    SetGraphicsMode(hdc, GM_ADVANCED);
    
    Level.Draw(hdc, paint_area);
    Border.Draw(hdc, paint_area);
    Platform.Draw(hdc, paint_area);
    Ball_Pile.Draw(hdc, paint_area);
}

int HeadEngine::On_Key(EKey_Type key_type, int button, HWND hwnd, bool is_key_down) {
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

int HeadEngine::On_Timer() {
    //Timer that is used to do the actions in time we ask to
    ++Config::Tick;

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
        if (Platform.Get_State() == PS_None) {
            Game_State = GS_Restart;
            Platform.Set_State(PS_StartGame);
        }
        break;

    case GS_Restart:
        if (Platform.Get_State() == PS_Ready) {
            for (int i = 0; i < Config::Max_Ball_Count; i++) {
                Ball_Pile.Balls[i].Set_State(BS_Start, Platform.X_Position + Platform.Width - Platform.Width / 4 + 2);
                Ball_Pile.Balls[i].Ball_Speed = 0.0;
            }
            Game_State = GS_Play;
        }        
        break;
    }

    Act();   

    return 0;
}

void HeadEngine::Play_Level() {
    Next_Driver_Step();

    if (Ball_Pile.If_Balls_Lost()) {
        Game_State = GS_GameOver;
        Platform.Set_State(PS_EndGame);
    } 

    /*if (Ball_Pile.Balls[0].Is_Test_Finished()) {
        Game_State = GS_Test;
    }*/
    
}

void HeadEngine::Next_Driver_Step() {
    double rest_distance, max_speed = 0.0;
    double current_speed = 0.0;

    //Platform moving

    for (int i = 0; i < Config::Max_Driver_Count; i++) {
        if (Object_Driver[i] != 0) {
            Object_Driver[i]->Initialization();
            current_speed = Object_Driver[i]->Get_Speed();
            if (current_speed > max_speed) max_speed = current_speed;
        }
    }

    rest_distance = max_speed;

    while (rest_distance > 0.0) {
        for (int i = 0; i < Config::Max_Driver_Count; i++) {
            if (Object_Driver[i] != 0) Object_Driver[i]->Next_Step(max_speed);
        }
        rest_distance -= Config::Step_Size;
    }

    for (int i = 0; i < Config::Max_Driver_Count; i++) {
        if (Object_Driver[i] != 0) {
            Object_Driver[i]->Finalization();
        }
    }
}

void HeadEngine::Act() {
    Platform.Act();
    Level.Act();

    int index = 0;
    Bonus* falling_bonus;

    while (Level.Have_Next_Bonus(index, &falling_bonus)) {
        if (Platform.Got_Hit_By(falling_bonus)) {
            On_Falling_Bonus(falling_bonus);
        }
    }
}

void HeadEngine::On_Falling_Bonus(Bonus* falling_bonus) {
    /*if (falling_bonus->Bonus_Type == BNT_Tripple_Ball) {

    }*/
    falling_bonus->Finalize();
}
/////////////////////////////////////////////////////////////////////