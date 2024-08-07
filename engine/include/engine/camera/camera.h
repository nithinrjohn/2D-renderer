#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/quad.h"

namespace engine
{
    class Camera
    {
        private:
            float width;
            float height;
            float pixelsPerUnit = 128.0f;
            float zoomPercent = 1.0f;
            
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);
        public:
            Camera(float width, float height);
            Camera(float width, float height, float pixelsPerUnit);

            float GetWidth() { return width; }
            float GetHeight() { return height; }
            float GetPixelSize() { return pixelsPerUnit; }
            float GetZoom() { return zoomPercent; }

            glm::mat4 GetView() { return view; }
            glm::mat4 GetProjection() { return projection; }

            void SetWidth(float width) { this->width = width; }
            void SetHeight(float height) { this->height = height; }
            void SetPixelSize(float pixelsPerUnit) { this->pixelsPerUnit = pixelsPerUnit;}

            void SetView(glm::mat4 view) { this->view = view; }
            void SetProjection(glm::mat4 projection) { this->projection = projection; }

            void OnResize(float width, float height);
            void Update();

            void SetZoom(float percent) { zoomPercent = percent; OnResize(width, height);}
            void ResetZoom() { zoomPercent = 1.0f; }
    };
}