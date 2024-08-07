#pragma once

#include <iostream>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "quad.h"

namespace engine 
{
    class Sprite 
    {
        private:
            std::string texturePath = "../res/textures/default.jpg";
            int sprites = 1;
            int spriteIndex = 1;

            Quad* quad;

            glm::vec2 position = glm::vec2(0.0f);
            float rotation = 0.0f;
            glm::vec2 size = glm::vec2(1.0f);
            glm::vec4 color = glm::vec4(1.0f);
        public:
            Sprite() : position(glm::vec2(0.0f)), rotation(0.0f), size(glm::vec2(1.0f)), color(glm::vec4(1.0f)) {}
            Sprite(glm::vec2 position, float rotation, glm::vec2 size);
            Sprite(glm::vec2 position, float rotation, glm::vec2 size, glm::vec4 color);

            Sprite(glm::vec2 position, float rotation, glm::vec2 size, glm::vec4 color, std::string texturePath);
            Sprite(glm::vec2 position, float rotation, glm::vec2 size, std::string texturePath);

            Sprite(glm::vec2 position, float rotation, glm::vec2 size, glm::vec4 color, std::string texturePath, int sprites);
            Sprite(glm::vec2 position, float rotation, glm::vec2 size, std::string texturePath, int sprites);

            ~Sprite();

            void Init();

            glm::vec2 GetPosition() { return position; }
            float GetRotation() { return rotation; }
            glm::vec2 GetSize() { return size; }
            glm::vec4 GetColor() { return color; }

            void SetPosition(glm::vec2 position);
            void SetRotation(float rotation);
            void SetSize(glm::vec2 size);
            void SetColor(glm::vec4 color);

            void Render() { quad->Render(color); }

            void NextSprite() { spriteIndex++; quad->NextSprite(); }

            void FlipX (bool flip) { quad->FlipX(flip); }
            void FlipY (bool flip) { quad->FlipY(flip); }

            bool GetFlipX() { return quad->GetFlipX(); }
            bool GetFlipY() { return quad->GetFlipY(); }

            void SetSpriteIndex(int index) { spriteIndex = index; quad->SetSpriteIndex(index); }
            int GetSpriteIndex() { return spriteIndex; }
    };
}