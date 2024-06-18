#include <iostream>
#include "include/raylib.h"

using namespace std;

//Colors
Color yellow = {221, 216, 148, 255};
Color blue = {113, 197, 207, 255};
Color green = {116, 191, 46, 255};

//Variables and Functions

bool gameplay = true;
int score = 0;
int best_score = 0;


//Classes
class Bird;

class Pipe
{
public:

    float x;
    float y_top = 0, y_bottom;    
    float width = 75;
    float height_top, height_bottom;
    float speed = 2;
    friend class Bird;
    
    void checkScore()
    {
       if((x + width) >= 299 && (x + width) <= 301)
        {
            score ++;
        }
    }

    void draw()
    {
        DrawRectangle(x, y_top, width, height_top, green);
        DrawRectangle(x, y_bottom, width, height_bottom, green);   
    }

    void update()
    {
        checkScore();
        x -= speed;
        if(x <= -75)
        {
            x = 1425;
            height_top = GetRandomValue(40,360);
            y_bottom = height_top + 150;
            height_bottom = 550 - y_bottom;
        }        
    }
};

class Bird
{
public:

    float y = 100;
    float x = 300;
    float radius = 17;
    float gravity = 0.01;
    float velo = 0;
    float acce = 0;

    void draw()
    {
        DrawCircle(x, y, (float)radius, RED);
    }

    void checkCollisionWithGround()
    {
        if(y + radius >=550)
        {
            gameplay = false;
            y = 550 - radius;
            velo = 0;
            acce = 0;
        }
    }

    void update()
    {
        
        checkCollisionWithGround();
        if(IsKeyPressed(KEY_SPACE))
        {
            acce = 0;
            velo = -gravity / 0.00225;

        }
        else
        {
            acce += gravity;
            velo += acce;
            y+= velo;
        }     
    }
};

int main () 
{

//Creating Objects and Their Variables

//Pipes

Pipe p1;
Pipe p2;
Pipe p3;
Pipe p4;
Pipe p5;

p1.x = 825;
p1.y_bottom = 275;
p1.height_top = 125;
p1.height_bottom = 275;

p2.x = 1125;
p2.y_bottom = 375;
p2.height_top = 225;
p2.height_bottom = 175;

p3.x = 1425;
p3.y_bottom = 425;
p3.height_top = 275;
p3.height_bottom = 125;

p4.x = 1725;
p4.y_bottom = 350;
p4.height_top = 200;
p4.height_bottom = 200;

p5.x = 2025;
p5.y_bottom = 300;
p5.height_top = 150;
p5.height_bottom = 250;

//Bird

Bird bird;

//Creating Window

InitWindow(1200, 660, "Flappy Bird by STH");
SetTargetFPS(60);

//Game Loop

while(WindowShouldClose()==false)
{
    BeginDrawing();

    //Updating

    if(gameplay)
    {
        p1.update();
        p2.update();
        p3.update();
        p4.update();
        p5.update(); 
        bird.update();
        
        if(CheckCollisionCircleRec(Vector2{bird.x, bird.y}, bird.radius, Rectangle{p1.x, p1.y_top, p1.width, p1.height_top})) gameplay = false;
        if(CheckCollisionCircleRec(Vector2{bird.x, bird.y}, bird.radius, Rectangle{p1.x, p1.y_bottom, p1.width, p1.height_bottom})) gameplay = false;

        if(CheckCollisionCircleRec(Vector2{bird.x, bird.y}, bird.radius, Rectangle{p2.x, p2.y_top, p2.width, p2.height_top})) gameplay = false;
        if(CheckCollisionCircleRec(Vector2{bird.x, bird.y}, bird.radius, Rectangle{p2.x, p2.y_bottom, p2.width, p2.height_bottom})) gameplay = false;

        if(CheckCollisionCircleRec(Vector2{bird.x, bird.y}, bird.radius, Rectangle{p3.x, p3.y_top, p3.width, p3.height_top})) gameplay = false;
        if(CheckCollisionCircleRec(Vector2{bird.x, bird.y}, bird.radius, Rectangle{p3.x, p3.y_bottom, p3.width, p3.height_bottom})) gameplay = false;

        if(CheckCollisionCircleRec(Vector2{bird.x, bird.y}, bird.radius, Rectangle{p4.x, p4.y_top, p4.width, p4.height_top})) gameplay = false;
        if(CheckCollisionCircleRec(Vector2{bird.x, bird.y}, bird.radius, Rectangle{p4.x, p4.y_bottom, p4.width, p4.height_bottom})) gameplay = false;

        if(CheckCollisionCircleRec(Vector2{bird.x, bird.y}, bird.radius, Rectangle{p5.x, p5.y_top, p5.width, p5.height_top})) gameplay = false;
        if(CheckCollisionCircleRec(Vector2{bird.x, bird.y}, bird.radius, Rectangle{p5.x, p5.y_bottom, p5.width, p5.height_bottom})) gameplay = false;

        if(best_score < score) best_score = score;
    }
    else
    {
        if(IsKeyPressed(KEY_SPACE))
        {
            p1.x = 825;
            p2.x = 1125;
            p3.x = 1425;
            p4.x = 1725;
            p5.x = 2025;
            bird.y = 100;
            bird.acce = 0;
            bird.velo = 0;

            score = 0;
            gameplay = true;
        }
    }




    //Drawing

    ClearBackground(blue);    

    p1.draw();
    p2.draw();
    p3.draw();
    p4.draw();
    p5.draw(); 
    bird.draw();
    DrawRectangle(0, 550, 1200, 110, yellow);//Ground
    DrawText("SCORE: ", 250, 585, 50, WHITE);
    DrawText("BEST SCORE: ", 550 , 585, 50, WHITE);
    DrawText(TextFormat("%i", score), 440, 585, 50, WHITE);
    DrawText(TextFormat("%i", best_score), 905, 585, 50, WHITE);


    EndDrawing();
}
CloseWindow();
return 0;
}
