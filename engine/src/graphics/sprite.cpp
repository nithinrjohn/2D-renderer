#include "sprite.h"

namespace engine
{
    Sprite::Sprite(glm::vec2 position, float rotation, glm::vec2 size) : position(position), rotation(rotation), size(size)
    {
        quad = new Quad(texturePath, sprites);
        Init();
    }

    Sprite::Sprite(glm::vec2 position, float rotation, glm::vec2 size, glm::vec4 color) : position(position), rotation(rotation), size(size), color(color)
    {
        quad = new Quad(texturePath, sprites);
        Init();
    }

    Sprite::Sprite(glm::vec2 position, float rotation, glm::vec2 size, glm::vec4 color, std::string texturePath) : position(position), rotation(rotation), size(size), color(color), texturePath(texturePath)
    {
        quad = new Quad(texturePath, sprites);
        Init();
    }

    Sprite::Sprite(glm::vec2 position, float rotation, glm::vec2 size, std::string texturePath) : position(position), rotation(rotation), size(size), texturePath(texturePath)
    {
        quad = new Quad(texturePath, sprites);
        Init();
    }

    Sprite::Sprite(glm::vec2 position, float rotation, glm::vec2 size, glm::vec4 color, std::string texturePath, int sprites) : position(position), rotation(rotation), size(size), color(color), texturePath(texturePath), sprites(sprites)
    {
        quad = new Quad(texturePath, sprites);
        Init();
    }

    Sprite::Sprite(glm::vec2 position, float rotation, glm::vec2 size, std::string texturePath, int sprites) : position(position), rotation(rotation), size(size), texturePath(texturePath), sprites(sprites)
    {
        quad = new Quad(texturePath, sprites);
        Init();
    }
    
    void Sprite::Init()
    {
        quad->model = glm::translate(quad->model, glm::vec3(position, 0.0f));

        quad->model = glm::translate(quad->model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
        quad->model = glm::rotate(quad->model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        quad->model = glm::translate(quad->model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

        quad->model = glm::scale(quad->model, glm::vec3(size, 1.0f));
    }

    Sprite::~Sprite()
    {
    }

    void Sprite::SetPosition(glm::vec2 position)
    {
        glm::vec2 deltaPos = position - this->position;
        this->position = position;

        deltaPos /= size;

        quad->model = glm::translate(quad->model, glm::vec3(deltaPos, 0.0f));
    }

    void Sprite::SetRotation(float rotation)
    {
        float deltaRot = rotation - this->rotation;
        this->rotation = rotation;
        // Rotate around the center of the sprite
        //quad->model = glm::translate(quad->model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
        //quad->model = glm::rotate(quad->model, glm::radians(deltaRot), glm::vec3(0.0f, 0.0f, 1.0f));
        //quad->model = glm::translate(quad->model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

        quad->model = glm::rotate(quad->model, glm::radians(deltaRot), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    void Sprite::SetSize(glm::vec2 size)
    {
        if(size.x <= 0 || size.y <= 0)
            return;
        
        glm::vec2 deltaSize = size / this->size;

        this->size = size;
        quad->model = glm::scale(quad->model, glm::vec3(deltaSize, 1.0f));
    }

    void Sprite::SetColor(glm::vec4 color)
    {
        if(color == this->color)
            return;

        this->color = color / 255.0f;
    }
}