#include "Ball_Pile.h"


//          BALL_PILE


void Ball_Pile::Initialization() {
    for (int i = 0; i < Common::Max_Ball_Count; i++) Balls[i].Initialization();
}

void Ball_Pile::Finalization() {
    for (int i = 0; i < Common::Max_Ball_Count; i++) Balls[i].Finalization();
}

void Ball_Pile::Next_Step(double max_speed) {
    for (int i = 0; i < Common::Max_Ball_Count; i++) Balls[i].Next_Step(max_speed);
}

double Ball_Pile::Get_Speed() {
    double max_speed = 0.0;

    for (int i = 0; i < Common::Max_Ball_Count; i++) {
        if (Balls[i].Ball_Speed > max_speed) max_speed = Balls[i].Ball_Speed;
    }

    return max_speed;
}

void Ball_Pile::Draw(HDC hdc, RECT& paint_area) {
    for (int i = 0; i < Common::Max_Ball_Count; i++) Balls[i].Draw(hdc, paint_area);
}

void Ball_Pile::Animate() {
    //There`s nothing
}

bool Ball_Pile::Is_Finished() {
    //There`s nothing
    return false;
}

void Ball_Pile::Release_Balls(double platform_pos) {
    Balls[0].Set_State(BS_Free, platform_pos);

    for (int i = 1; i < Common::Max_Ball_Count; i++) {
        Balls[i].Set_State(BS_Disabled, platform_pos);
    }

    //for (int i = 20; i < Common::Max_Ball_Count; i++) {
    //    //if(Balls[i].Get_State() == BS_Start)
    //    Balls[i].Set_State(BS_Disabled, 0);
    //}
}

void Ball_Pile::Set_On_Platform(double platform_pos) {
    Balls[0].Set_State(BS_Start, platform_pos);

    for (int i = 1; i < Common::Max_Ball_Count; i++) Balls[i].Set_State(BS_Disabled, platform_pos);
}

void Ball_Pile::Disable_Balls() {
    for (int i = 0; i < Common::Max_Ball_Count; i++) Balls[i].Set_State(BS_Disabled, 0);
}

bool Ball_Pile::If_Balls_Lost() {
    int active_balls = 0, fallen_balls = 0;

    //Balls moving
    for (int i = 0; i < Common::Max_Ball_Count; i++) {
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
    Ball* left_reason = 0, * right_reason = 0;
    double ball_x, ball_y, further_ball_x, further_ball_y;

    for (int i = 0; i < Common::Max_Ball_Count; i++) {
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

    for (int i = 0; i < Common::Max_Ball_Count; i++) {
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
    if (right_reason != 0) {
        *right_reason = *further_ball;
        right_reason->Set_Direction(right_reason->Get_Direction() - M_PI_4 / 2);
    }

}

////////////////////////////////////////////////////