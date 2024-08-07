#include "camera.h"

namespace engine
{
    //Creates a camera with a pixels per unit of 64
    Camera::Camera(float width, float height)
    {
        OnResize(width, height);
    }

    Camera::Camera(float width, float height, float pixelsPerUnit) : pixelsPerUnit(pixelsPerUnit)
    {
        OnResize(width, height);
    }

    void Camera::OnResize(float width, float height)
    {
        this->width = width;
        this->height = height;

        projection = glm::ortho(-width/2.0f, width/2.0f, -height/2.0f, height/2.0f);
        projection = glm::scale(projection, glm::vec3(pixelsPerUnit * zoomPercent, pixelsPerUnit * zoomPercent, 1.0f));
    }

    void Camera::Update()
    {
        Quad::shader->SetMat4("view", view);
        Quad::shader->SetMat4("projection", projection);
    }
}