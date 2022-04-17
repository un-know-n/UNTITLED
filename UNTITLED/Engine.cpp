
#include "Engine.h"

/////////////////////////////////////////////////////////////////////

//          CSENGINE

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
        Balls[i].Init();

        Balls[i].Add_Hit_Checker(&Border);
        Balls[i].Add_Hit_Checker(&Level);
        Balls[i].Add_Hit_Checker(&Platform);
    }  

    //Ball.Set_State(BS_Start, Platform.X_Position + Platform.Width - Platform.Width / 2 + 2);
    //Platform.Set_State(PS_StartGame);
    Platform.Redraw();
    
    SetTimer(Config::Hwnd, Timer_ID, 1000 / Config::FPS, 0);
}

void HeadEngine::Draw_Frame(HDC hdc, RECT &paint_area) {
    //It draws game screen (hdc - handle to device context)
    SetGraphicsMode(hdc, GM_ADVANCED);
    
    Level.Draw(hdc, paint_area);

    for(int i = 0; i < Config::Max_Ball_Count; i++) Balls[i].Draw(hdc, paint_area);


    Border.Draw(hdc, paint_area);
    Platform.Draw(hdc, paint_area);
}

int HeadEngine::On_Key_Down(EKey_Type key_type, int button, HWND hwnd) {
    //Check what type of key is currently pressed
    switch (key_type) {
    case KT_Left:
        Platform.Move_To_Left(true);
        break;
    case KT_Right:
        Platform.Move_To_Left(false);
        break;
    case KT_Space:
        if (Platform.Get_State() == PS_Ready) {

            for (int i = 0; i < 3; i++) {
                Balls[i].Set_State(BS_Free, Platform.X_Position + Platform.Width - Platform.Width / 4 + 2);
            }

            for (int i = 3; i < Config::Max_Ball_Count; i++) {
                //if(Balls[i].Get_State() == BS_Start)
                Balls[i].Set_State(BS_Disabled, 0);
            }
            Platform.Set_State(PS_Normal);
        }
        break;
    case KT_Escape:
        DestroyWindow(hwnd);
        break;
    }
    switch (button) {
    case Button_A:
        Platform.Move_To_Left(true);
        break;
    case Button_D:
        Platform.Move_To_Left(false);
        break;
    }
    return 0;
}

int HeadEngine::On_Timer() {
    //Timer that is used to do the actions in time we ask to
    ++Config::Tick;

    switch (Game_State) {
    case GS_Test:
        Balls[0].Set_Test();
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
                Balls[i].Set_State(BS_Start, Platform.X_Position + Platform.Width - Platform.Width / 4 + 2);// -Platform.Width / 4
                Balls[i].Ball_Speed = 0.0;
            }
            //for (int i = 1; i < Config::Max_Ball_Count; i++)
            Game_State = GS_Play;
        }        
        break;
    }

    Act();   

    return 0;
}

void HeadEngine::Play_Level() {
    int active_balls = 0, fallen_balls = 0;
    for (int i = 0; i < Config::Max_Ball_Count; i++) {
        if (Balls[i].Get_State() == BS_Disabled) continue;
        ++active_balls;
        if (Balls[i].Get_State() == BS_None) ++fallen_balls;
        Balls[i].Move();
    }
    if (Balls[0].Is_Test_Finished()) {
        Game_State = GS_Test;
    }
    if (active_balls == fallen_balls && fallen_balls != 0 && active_balls != 0) {
        Game_State = GS_GameOver;
        Platform.Set_State(PS_EndGame);
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