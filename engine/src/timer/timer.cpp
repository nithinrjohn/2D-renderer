#include "timer.h"

namespace engine {
    void Timer::Step()
    {
        currTime = glfwGetTime();
        deltaTime = currTime - prevTime;
        frames++;

        FPS = frames / deltaTime;
        ms = 1000.0 * deltaTime / frames;

        prevTime = currTime;
        frames = 0;
    }
}