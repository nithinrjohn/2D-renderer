#pragma once

#include <vector>
#include <map>
#include <algorithm>

#include "window/window.h"

namespace engine {

    class Input {
        private:
            std::map<int, bool> keys;

            bool enabled = true;

            void SetKey(int key, bool value);

            static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

            static std::vector<Input*> inputs;
        public:
            Input(std::vector<int> keys, Window* window);
            ~Input();

            bool IsKeyPressed(int key);
            bool IsAnyKeyPressed();

            void Enable() { enabled = true; }
            void Disable() { enabled = false; }

            bool IsEnabled() { return enabled; }
    };

}