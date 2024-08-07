#pragma once

#include <iostream>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "image/stb_image.h"

#include "shader.h"

namespace engine
{
    class Quad
    {
        private:
            int sprites = 1;
            int spriteIndex = 1;

            float upperUV = (float)spriteIndex / (float)sprites;
            float lowerUV = (float)(spriteIndex - 1) / (float)sprites;

            GLfloat vertices[20] = {
                // positions         // UVs
                0.5f,  0.5f, 0.0f,   upperUV, 1.0f,   // top right
                0.5f, -0.5f, 0.0f,   upperUV, 0.0f,   // bottom right
                -0.5f, -0.5f, 0.0f,  lowerUV, 0.0f,      // bottom left
                -0.5f,  0.5f, 0.0f,  lowerUV, 1.0f       // top left 
            };

            GLuint indices[6] = {  // note that we start from 0!
                0, 1, 3,  // first Triangle
                1, 2, 3   // second Triangle
            };

            GLuint VBO, VAO, EBO;

            GLuint texture;

            bool flipX = false;
            bool flipY = false;

            glm::vec2 scale = glm::vec2(1.0f);
        public:
            Quad(std::string texturePath, int sprites);
            ~Quad();

            glm::mat4 model;

            void Render(glm::vec4 color);

            static Shader* shader;

            void NextSprite();

            void FlipX(bool flip) { flipX = flip; }
            void FlipY(bool flip) { flipY = flip; }

            bool GetFlipX() { return flipX; }
            bool GetFlipY() { return flipY; }

            void SetSpriteIndex(int index);
    };
}