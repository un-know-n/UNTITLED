
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
    Balls[0].Set_State(BS_Free, platform_pos);

    for (int i = 1; i < Config::Max_Ball_Count; i++) {
        Balls[i].Set_State(BS_Disabled, platform_pos); 
    }

    //for (int i = 20; i < Config::Max_Ball_Count; i++) {
    //    //if(Balls[i].Get_State() == BS_Start)
    //    Balls[i].Set_State(BS_Disabled, 0);
    //}
}

void Ball_Pile::Set_On_Platform(double platform_pos) {
    Balls[0].Set_State(BS_Start, platform_pos);

    for(int i = 1; i < Config::Max_Ball_Count; i++) Balls[i].Set_State(BS_Disabled, platform_pos);
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

void Ball_Pile::Tripple_Balls() {

    Ball* current_ball;
    Ball* further_ball = 0;
    Ball* left_reason = 0, *right_reason = 0;
    double ball_x, ball_y, further_ball_x, further_ball_y;

    for (int i = 0; i < Config::Max_Ball_Count; i++) {
        current_ball = &Balls[i];

        if (current_ball->Get_State() != BS_Free) continue;

        if (further_ball == 0) {
            further_ball = current_ball;
        }
        else {
            current_ball->Get_Center(ball_x, ball_y);
            further_ball->Get_Center(further_ball_x, further_ball_y);
            if (further_ball_y > ball_y) further_ball = current_ball;
        }
    }

    if (further_ball == 0) return;
    
    for (int i = 0; i < Config::Max_Ball_Count; i++) {
        current_ball = &Balls[i];

        if (current_ball->Get_State() == BS_Disabled || current_ball->Get_State() == BS_None) {
            if (left_reason == 0) left_reason = current_ball;
            else if (right_reason == 0) {
                right_reason = current_ball;
                break;
            }
            //else return;
        }
    }

    if (left_reason != 0) {
        *left_reason = *further_ball;
        left_reason->Set_Direction(left_reason->Get_Direction() + M_PI_4 / 2);
    }
    if (right_reason != 0){
        *right_reason = *further_ball;
        right_reason->Set_Direction(right_reason->Get_Direction() - M_PI_4 / 2);
    }

}

////////////////////////////////////////////////////

//          HEADENGINE

Head_Engine::Head_Engine() : Game_State(GS_GameOver), Life_Counter(0)
{//Constructor
}

void Head_Engine::Init_Engine(HWND hwnd) {
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

void Head_Engine::Draw_Frame(HDC hdc, RECT &paint_area) {
    //It draws game screen (hdc - handle to device context)
    SetGraphicsMode(hdc, GM_ADVANCED);
    
    Level.Draw(hdc, paint_area);
    Border.Draw(hdc, paint_area);
    Platform.Draw(hdc, paint_area);
    Ball_Pile.Draw(hdc, paint_area);
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
            Ball_Pile.Set_On_Platform(Platform.X_Position + Platform.Width - Platform.Width / 4 + 2);
            Game_State = GS_Play;
        }        
        break;
    }

    Act();   

    return 0;
}

void Head_Engine::Play_Level() {
    Next_Driver_Step();

    if (Ball_Pile.If_Balls_Lost()) {
        Game_State = GS_GameOver;
        Platform.Set_State(PS_PreEndGame);
    } 

    /*if (Ball_Pile.Balls[0].Is_Test_Finished()) {
        Game_State = GS_Test;
    }*/
    
}

void Head_Engine::Next_Driver_Step() {
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

void Head_Engine::Act() {
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

void Head_Engine::On_Falling_Bonus(Bonus* falling_bonus) {
    if (falling_bonus->Bonus_Type == BNT_Tripple_Ball) {
        Ball_Pile.Tripple_Balls();
    }
    else if (falling_bonus->Bonus_Type == BNT_Additional_Life) {
        if (Life_Counter < Config::Max_Life_Counter) Life_Counter++;
    }
    falling_bonus->Finalize();
}
/////////////////////////////////////////////////////////////////////