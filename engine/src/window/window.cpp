#include "window.h"

namespace engine {

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        Window* win = (Window*)glfwGetWindowUserPointer(window);
        win->OnResize(width, height);
    }

    Window::Window(int width, int height, std::string title) : width(width), height(height), title(title)
    {
        const char* c_title = title.c_str();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Initialize GLFW
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW" << std::endl;
        }

        // Create a windowed mode window and its OpenGL context
        window = glfwCreateWindow(width, height, c_title, NULL, NULL);
        if (!window)
        {
            std::cerr << "Failed to create window" << std::endl;
            glfwTerminate();
        }

        // Make the window's context current
        glfwMakeContextCurrent(window);

        // Set the window resize callback
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // Set the user pointer
        glfwSetWindowUserPointer(window, this);

        // Initialize GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD" << std::endl;
        }

        camera = new Camera(width, height);

        unitSize = { width / camera->GetPixelSize(), height / camera->GetPixelSize() };

        SetColor();
    }

    Window::~Window()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::SetVsync(bool vsync)
    {
        glfwSwapInterval(vsync ? 1 : 0);
    }

    void Window::SetWindowIcon(std::string path)
    {
        GLFWimage images[1];
        unsigned char* data = stbi_load(path.c_str(), &images[0].width, &images[0].height, 0, 4);
        
        images[0].pixels = data;
        glfwSetWindowIcon(window, 1, images);

        stbi_image_free(data);
    }

    void Window::SetColor(int r, int g, int b, int a)
    {
        color[0] = r / 255.0f;
        color[1] = g / 255.0f;
        color[2] = b / 255.0f;
        color[3] = a / 255.0f;
    }

    void Window::Clear()
    {
        glClearColor(color[0], color[1], color[2], color[3]);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::Refresh()
    {
        camera->Update();

        glfwSwapBuffers(window);
        glfwPollEvents();

        Clear();
    }

    void Window::OnResize(int width, int height)
    {
        isResized = true;
        
        this->width = width;
        this->height = height;

        camera->OnResize(width, height);

        unitSize = { width / camera->GetPixelSize(), height / camera->GetPixelSize() };

        glfwSwapBuffers(window);
        glViewport(0, 0, width, height);
    }
}