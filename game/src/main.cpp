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

glm::vec2 pos = glm::vec2(0.0f, 0.0f);
float staffOffset = 0.4f;

int main()
{
    Window window = Window(1280, 720, "Sandbox");
    window.SetWindowIcon("../res/textures/icon.jpg");
    window.SetVsync(true);
    window.SetColor(44, 43, 64);

    Input input = Input({GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_LEFT, GLFW_KEY_RIGHT}, &window);

    Input action = Input({GLFW_KEY_SPACE}, &window);

    Input menu = Input({GLFW_KEY_ESCAPE}, &window);

    Sprite mage = Sprite(pos, 0.0f, glm::vec2(1.0), "../res/textures/mage.png", 3);

    Sprite staffRight = Sprite(glm::vec2(pos.x + staffOffset, pos.y), 0.0f, glm::vec2(1.0), "../res/textures/staff.png", 2);
    Sprite staffLeft = Sprite(glm::vec2(pos.x - staffOffset, pos.y), 0.0f, glm::vec2(1.0), "../res/textures/staff.png", 2);
    staffLeft.FlipX(true);

    Sprite circle = Sprite(pos, 0.0f, glm::vec2(5.0), "../res/textures/circle.png", 27);

    float elapsedTime = 0.0f;
    float staffTime = 0.0f;
    float circleTime = 0.0f;
    float circleDownTime = 0.0f;
    bool downSequence = false;

    glm::vec4 staffActionColor = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);

    while(window.IsRunning())
    {
        timer.Step();

        if(input.IsKeyPressed(GLFW_KEY_W) || input.IsKeyPressed(GLFW_KEY_UP))
        {
            pos.y += 5.0f * timer.GetDeltaTime();
        }
        if(input.IsKeyPressed(GLFW_KEY_S) || input.IsKeyPressed(GLFW_KEY_DOWN))
        {
            pos.y -= 5.0f * timer.GetDeltaTime();
        }
        if(input.IsKeyPressed(GLFW_KEY_A) || input.IsKeyPressed(GLFW_KEY_LEFT))
        {
            pos.x -= 5.0f * timer.GetDeltaTime();
            mage.FlipX(true);
        }
        if(input.IsKeyPressed(GLFW_KEY_D) || input.IsKeyPressed(GLFW_KEY_RIGHT))
        {
            pos.x += 5.0f * timer.GetDeltaTime();
            mage.FlipX(false);
        }

        if(menu.IsKeyPressed(GLFW_KEY_ESCAPE))
        {
            window.Close();
        }

        elapsedTime += timer.GetDeltaTime();
        staffTime += timer.GetDeltaTime();

        if(elapsedTime > 0.2f)
        {
            elapsedTime = 0.0f;
            mage.NextSprite();
        }
        if(staffTime > 0.3f)
        {
            staffTime = 0.0f;
            staffRight.NextSprite();
            staffLeft.NextSprite();
        }
        
        mage.SetPosition(pos);

        if(action.IsKeyPressed(GLFW_KEY_SPACE))
        {
            staffRight.SetPosition(glm::vec2(pos.x + staffOffset, pos.y + 0.3f));
            staffLeft.SetPosition(glm::vec2(pos.x - staffOffset, pos.y + 0.3f));
            circle.SetPosition(pos);

            staffRight.SetColor(staffActionColor);
            staffLeft.SetColor(staffActionColor);

            circleTime += timer.GetDeltaTime();
            if(circleTime > 0.2f)
            {
                circleTime = 0.0f;
                if(circle.GetSpriteIndex() <= 13)
                {
                    circle.NextSprite();
                    float colorIncrement = 255.0f / 13.0f;
                    staffActionColor.g -= colorIncrement;
                    staffActionColor.b -= colorIncrement;
                }
                if(circle.GetSpriteIndex() == 13)
                {
                    downSequence = true;
                }
            }
            circle.Render();
        }
        else if(!action.IsKeyPressed(GLFW_KEY_SPACE))
        {
            staffRight.SetPosition(glm::vec2(pos.x + staffOffset, pos.y + 0.1f));
            staffLeft.SetPosition(glm::vec2(pos.x - staffOffset, pos.y + 0.1f));
            circle.SetPosition(pos);

            staffRight.SetColor(staffActionColor);
            staffLeft.SetColor(staffActionColor);

            if(downSequence)
            {
                circleDownTime += timer.GetDeltaTime();
                if(circleDownTime > 0.2f)
                {
                    circleDownTime = 0.0f;
                    if(circle.GetSpriteIndex() <= 27)
                    {
                        if(staffActionColor.g < 255.0f)
                        {
                            staffActionColor.g += 255.0f / 14.0f;
                            staffActionColor.b += 255.0f / 14.0f;
                        }
                        else
                        {
                            staffActionColor = glm::vec4(255.0f);
                        }
                        circle.NextSprite();
                    }
                    if(circle.GetSpriteIndex() == 27)
                    {
                        downSequence = false;
                    }
                }
                circle.Render();
            }
            else{
                staffActionColor = glm::vec4(255.0f);
                circle.SetSpriteIndex(0);
            }
        }

        mage.Render();

        if(!mage.GetFlipX())
        {
            staffRight.Render();
        }
        else
        {
            staffLeft.Render();
        }
            
        window.Refresh();
    }

    return 0;
}