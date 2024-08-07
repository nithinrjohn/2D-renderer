#include "input/input.h"

namespace engine {

    std::vector<Input*> Input::inputs;

    Input::Input(std::vector<int> keys, Window* window)
    {
        for(int key : keys)
        {
            this->keys[key] = false;
        }

        inputs.push_back(this);

        glfwSetKeyCallback(window->GetWindow(), KeyCallback);
    }

    Input::~Input()
    {
        inputs.erase(std::remove(inputs.begin(), inputs.end(), this), inputs.end());
    }

    void Input::SetKey(int key, bool value)
    {
        if(keys.find(key) != keys.end())
        {
            keys[key] = value;
        }
    }

    bool Input::IsKeyPressed(int key)
    {
        if(enabled)
        {
            if(keys.find(key) != keys.end())
            {
                return keys[key];
            }
        }

        return false;
    }

    bool Input::IsAnyKeyPressed()
    {
        if(enabled)
        {
            for(auto const& [key, value] : keys)
            {
                if(value)
                {
                    return true;
                }
            }
        }

        return false;
    }

    void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        for(Input* input : inputs)
        {
            if(action == GLFW_PRESS)
            {
                input->SetKey(key, true);
            }
            else if(action == GLFW_RELEASE)
            {
                input->SetKey(key, false);
            }
        }
    }

}