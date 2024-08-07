#pragma once

#include <GLFW/glfw3.h>

namespace engine
{
    class Timer
    {
        private:
            double prevTime = 0.0f;
            double currTime = 0.0f;
            double deltaTime = 0.0f;
            unsigned int frames = 0;
            double FPS = 0.0f;
            double ms = 0.0f;
            
        public:
            void Step();

            double GetFPS() { return FPS; }
            double GetMS() { return ms; }
            double GetDeltaTime() { return deltaTime; }
            double GetTime() { return currTime; }
    };
}