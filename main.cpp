#include <raylib.h>
#include <string>

struct MoveableRect{
    int x = 20;
    int y = 400;
    int w = 10;
    int h = 75;
    int v = 5; // Speed
};

struct MoveableCirc{
    int x = 400;
    int y = 400;
    int r = 20;
    int xv = 8; // Speed
    int yv = 2; // Speed
};

void rectKeyPressed(MoveableRect& r)
{
    if(IsKeyDown(KEY_DOWN))
        {
            r.y += r.v;
            if(r.y+r.h > 800)
            {
                r.y -= r.v;
            }
        } else if(IsKeyDown(KEY_UP))
        {
            r.y -= r.v;
            if(r.y < 0)
            {
                r.y += r.v;
            }
        }
}

bool windowCollision(MoveableCirc& c)
{
    if(c.y-c.r < 0)
    {
        c.y = 0 + c.r;
        c.yv *= -1;
    }  else if(c.y+c.r > 800)
    {
        c.y = 800 - c.r;
        c.yv *= -1;
    }

    if (c.x-c.r < 0)
    {
        return 1;
    } else if(c.x+c.r > 800)
    {
        c.x = 800 - c.r;
        c.xv *= -1;
    }
    return 0;
}

bool rectCollision(MoveableCirc& c, MoveableRect& r)
{
    if(c.x-c.r < r.x + r.w)
    {
        if(c.y + c.r > r.y && c.y - c.r < r.y + r.h)
        {
            c.x = r.x + r.w + c.r;
            c.xv *= -1;
            c.xv += 1;
            return 1;
        }
    }
    return 0;
}

bool moveCirc(MoveableCirc& c, MoveableRect& r, int& score)
{
    c.y += c.yv;
    c.x += c.xv;
    if (rectCollision(c, r))
    {
        score++;
    }
    return windowCollision(c);
}

int main()
{
    InitWindow(800,800, "Titre");
    SetTargetFPS(60);
    MoveableRect pipe;
    MoveableCirc ball;
    int score = 0;
    bool lose = 0;
    std::string scoreText ="Score : 0";

    //Game loop
    while(!WindowShouldClose())
    {
        if (!lose)
        {
            //Event Handling
            rectKeyPressed(pipe);

            //Updating positions
            lose = moveCirc(ball, pipe, score);

            //Drawning
            BeginDrawing();
            ClearBackground(BLACK);
            scoreText = "Score : " + std::to_string(score); 
            DrawText(scoreText.c_str(), 350, 50, 20, LIGHTGRAY);
            DrawCircle(ball.x,ball.y,ball.r,GOLD);
            DrawRectangle(pipe.x,pipe.y,pipe.w,pipe.h,DARKBLUE);
            EndDrawing();
        }
        else
        {    
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Congrats! You lose!", 300, 200, 20, LIGHTGRAY);
            DrawText(scoreText.c_str(), 350, 250, 20, LIGHTGRAY);
            DrawRectangle(350,400,100,50,LIGHTGRAY);
            DrawText("Retry", 370, 415, 20, GRAY);
            EndDrawing();

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (GetMouseX() < 450 && GetMouseX() > 350 && GetMouseY() < 450 && GetMouseY() > 400) {
                    ball.x = 400;
                    ball.y = 400;
                    ball.xv = 8;
                    score = 0;
                    lose = 0;
                }
            }
        }
    }
    CloseWindow();
    return 0; 
}