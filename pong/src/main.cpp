#include <iostream>

#include "engine/window/window.h"
#include "engine/timer/timer.h"
#include "engine/graphics/sprite.h"
#include "engine/input/input.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace engine;

Timer timer;

int main()
{
    Window window = Window(1280, 720, "Sandbox");
    window.SetWindowIcon("../res/textures/icon.jpg");
    window.SetVsync(false);
    //SlateGray 	#708090 	rgb(112, 128, 144)
    window.SetColor(112, 128, 144);

    glm::vec2 screenUnits = window.GetUnitSize();
    float padding = 1.8f / 4.0f;

    glm::vec2 p1Pos = glm::vec2(-screenUnits.x * padding, 0.0f);
    glm::vec2 p2Pos = glm::vec2(screenUnits.x * padding, 0.0f);

    Input player1 = Input({GLFW_KEY_W, GLFW_KEY_S}, &window);
    Input player2 = Input({GLFW_KEY_UP, GLFW_KEY_DOWN}, &window);

    // 	MidnightBlue 	#191970 	rgb(25, 25, 112)
    glm::vec4 p1Color = glm::vec4(25.0f / 255.0f, 25.0f / 255.0f, 112.0f / 255.0f, 1.0f);
    //Maroon 	#800000 	rgb(128, 0, 0)
    glm::vec4 p2Color = glm::vec4(128.0f / 255.0f, 0.0f, 0.0f, 1.0f);

    Sprite paddle1 = Sprite(p1Pos, 0.0f, glm::vec2(0.2, 0.7), p1Color);
    Sprite paddle2 = Sprite(p2Pos, 0.0f, glm::vec2(0.2, 0.7) , p2Color);

    glm::vec2 ballPos = glm::vec2(0.0f, 0.0f);
    float ballSpeed = 1.5f;
    float randX = (rand() % 2) == 0 ? -1.0f : 1.0f;
    float randY = (rand() % 2) == 0 ? -1.0f : 1.0f;
    int collisionCounter = 0;

    int blueScore = 0;
    int redScore = 0;

    //  	Wheat 	#F5DEB3 	rgb(245, 222, 179) 
    glm::vec4 ballColor = glm::vec4(245.0f / 255.0f, 222.0f / 255.0f, 179.0f / 255.0f, 1.0f);
    Sprite ball = Sprite(ballPos, 0.0f, glm::vec2(0.15f), ballColor);

    while(window.IsRunning())
    {
        timer.Step();

        if(window.IsResized())
        {
            screenUnits = window.GetUnitSize();
            
            p1Pos = glm::vec2(-screenUnits.x * padding, p1Pos.y);
            p2Pos = glm::vec2(screenUnits.x * padding, p2Pos.y);
            window.ResetResized();
        }

        if(player1.IsKeyPressed(GLFW_KEY_W))
        {
            p1Pos.y += 5.0f * timer.GetDeltaTime();
        }
        if(player1.IsKeyPressed(GLFW_KEY_S))
        {
            p1Pos.y -= 5.0f * timer.GetDeltaTime();
        }

        if(player2.IsKeyPressed(GLFW_KEY_UP))
        {
            p2Pos.y += 5.0f * timer.GetDeltaTime();
        }
        if(player2.IsKeyPressed(GLFW_KEY_DOWN))
        {
            p2Pos.y -= 5.0f * timer.GetDeltaTime();
        }

        // Check collision with walls
        if(p1Pos.y >= screenUnits.y / 2.0f - 0.35f)
        {
            p1Pos.y = screenUnits.y / 2.0f - 0.35f;
        }
        if(p1Pos.y <= -screenUnits.y / 2.0f + 0.35f)
        {
            p1Pos.y = -screenUnits.y / 2.0f + 0.35f;
        }

        if(p2Pos.y >= screenUnits.y / 2.0f - 0.35f)
        {
            p2Pos.y = screenUnits.y / 2.0f - 0.35f;
        }
        if(p2Pos.y <= -screenUnits.y / 2.0f + 0.35f)
        {
            p2Pos.y = -screenUnits.y / 2.0f + 0.35f;
        }

        paddle1.SetPosition(p1Pos);
        paddle2.SetPosition(p2Pos);

        if(ballPos.y >= screenUnits.y / 2.0f || ballPos.y <= -screenUnits.y / 2.0f)
        {
            randY *= -1.0f;
            collisionCounter++;
        }
        if(ballPos.x >= screenUnits.x / 2.0f)
        {
            ballPos = glm::vec2(0.0f, 0.0f);
            ball.SetPosition(ballPos);
            randX = (rand() % 2) == 0 ? -1.0f : 1.0f;
            randY = (rand() % 2) == 0 ? -1.0f : 1.0f;
            blueScore++;
            ballSpeed = 1.5f;
            std::cout << "Blue: " << blueScore << " Red: " << redScore << std::endl;
        }
        if(ballPos.x <= -screenUnits.x / 2.0f)
        {
            ballPos = glm::vec2(0.0f, 0.0f);
            ball.SetPosition(ballPos);
            randX = (rand() % 2) == 0 ? -1.0f : 1.0f;
            randY = (rand() % 2) == 0 ? -1.0f : 1.0f;
            redScore++;
            ballSpeed = 1.5f;
            std::cout << "Blue: " << blueScore << " Red: " << redScore << std::endl;
        }

        if(ballPos.x <= p1Pos.x + 0.1f && ballPos.y <= p1Pos.y + 0.35f && ballPos.y >= p1Pos.y - 0.35f)
        {
            randX *= -1.0f;
            collisionCounter++;
        }
        if(ballPos.x >= p2Pos.x - 0.1f && ballPos.y <= p2Pos.y + 0.35f && ballPos.y >= p2Pos.y - 0.35f)
        {
            randX *= -1.0f;
            collisionCounter++;
        }

        // Uncomment to increase ball speed after 5 collisions
        // if(collisionCounter >= 5)
        // {
        //     ballSpeed += 0.02f;
        //     collisionCounter = 0;
        // }

        ballPos.x += randX * timer.GetDeltaTime() * ballSpeed;
        ballPos.y += randY * timer.GetDeltaTime() * ballSpeed;

        ball.SetPosition(ballPos);

        ball.Render();
        paddle1.Render();
        paddle2.Render();
            
        window.Refresh();
    }

    return 0;
}