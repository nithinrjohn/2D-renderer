#include "quad.h"

namespace engine {
    Shader* Quad::shader = nullptr;

    Quad::Quad(std::string texturePath, int sprites) : model(glm::mat4(1.0f)), sprites(sprites)
    {
        upperUV = (float)spriteIndex / (float)sprites;
        lowerUV = (float)(spriteIndex - 1) / (float)sprites;

        vertices[3] = upperUV;
        vertices[8] = upperUV;
        vertices[13] = lowerUV;
        vertices[18] = lowerUV;

        shader = new Shader("../../build/engine/shaders/vert.glsl", "../../build/engine/shaders/frag.glsl");

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // Texture attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        if(texturePath == "")
            return;

        // Texture
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); 
        unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

        if(data)
        {
            if(nrChannels == 3)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }
            else if(nrChannels == 4)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }
            else
            {
                std::cout << "Error: Unknown number of channels" << std::endl;
            }
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Error: Failed to load texture" << std::endl;
        }

        stbi_image_free(data);
    }

    Quad::~Quad()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteBuffers(1, &texture);
    }

    void Quad::Render(glm::vec4 color)
    {
        glBindTexture(GL_TEXTURE_2D, texture);

        shader->Activate();

        shader->SetMat4("model", model);
        shader->SetVec4("color", color);
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Quad::NextSprite()
    {
        spriteIndex += 1;
        if(spriteIndex > sprites)
        {
            spriteIndex = 1;
        }

        upperUV = (float)spriteIndex / (float)sprites;
        lowerUV = (float)(spriteIndex - 1) / (float)sprites;

        if(flipX)
        {
            float temp = upperUV;
            upperUV = lowerUV;
            lowerUV = temp;
        }

        vertices[3] = upperUV;
        vertices[8] = upperUV;
        vertices[13] = lowerUV;
        vertices[18] = lowerUV;

        vertices[4] = 1.0f;
        vertices[9] = 0.0f;
        vertices[14] = 0.0f;
        vertices[19] = 1.0f;
        

        if(flipY)
        {
            vertices[4] = 0.0f;
            vertices[9] = 1.0f;
            vertices[14] = 1.0f;
            vertices[19] = 0.0f;
        }

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }

    void Quad::SetSpriteIndex(int index)
    {
        spriteIndex = index;
        if(spriteIndex > sprites)
        {
            spriteIndex = 1;
        }

        upperUV = (float)spriteIndex / (float)sprites;
        lowerUV = (float)(spriteIndex - 1) / (float)sprites;

        if(flipX)
        {
            float temp = upperUV;
            upperUV = lowerUV;
            lowerUV = temp;
        }

        vertices[3] = upperUV;
        vertices[8] = upperUV;
        vertices[13] = lowerUV;
        vertices[18] = lowerUV;

        vertices[4] = 1.0f;
        vertices[9] = 0.0f;
        vertices[14] = 0.0f;
        vertices[19] = 1.0f;
        

        if(flipY)
        {
            vertices[4] = 0.0f;
            vertices[9] = 1.0f;
            vertices[14] = 1.0f;
            vertices[19] = 0.0f;
        }

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }
}