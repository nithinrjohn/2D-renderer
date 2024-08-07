#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera/camera.h"

#include "image/stb_image.h"
#include "graphics/sprite.h"

namespace engine {

    class Window {
        private:
            int width, height;
            std::string title;
            float color[4] = {0.0f, 0.0f, 0.0f, 1.0f};
            Sprite* background;
            
            GLFWwindow* window;

            Camera* camera;

            glm::vec2 unitSize;

            bool isResized = false;
        public: 
            Window() {}
            Window(int width, int height, std::string title);
            ~Window();

            void SetVsync(bool vsync);
            void SetWindowIcon(std::string path);

            void SetColor(int r = 58, int g = 58, int b = 58, int a = 255);
            void Clear();
            void Refresh();

            void OnKey(int key, int scancode, int action, int mods);
            void OnResize(int width, int height);

            bool IsResized() { return isResized; }
            void ResetResized() { isResized = false; }

            int GetWidth() { return width; }
            int GetHeight() { return height; }
            std::string GetTitle() { return title; }
            GLFWwindow* GetWindow() { return window; }
            Camera* GetCamera() { return camera; }
            glm::vec2 GetUnitSize() { return unitSize; }
            
            int IsRunning() { return !glfwWindowShouldClose(window); }

            void SetTitle(std::string title) { this->title = title; glfwSetWindowTitle(window, title.c_str());}
            void SetCamera(Camera* camera) { this->camera = camera; }

            void Close() { glfwSetWindowShouldClose(window, true); }
    };

}