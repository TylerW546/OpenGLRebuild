#pragma once

namespace gl{
    class Window;
    enum class WindowType {
        static_window,
        stretch_window,
        scale_window,
        dynamic_window
    };
}

#include "Game.hpp"

#include "deps.h"

#include <map>

namespace gl {
    class Window {
        public:

        private:
        GLFWwindow* window_;
        WindowType type_;
        Game* game_;
        uint16_t winWidth_, winHeight_;
        float ratio_;
        glm::mat4 projection_; // Transforms point on game field to point on screen

        public:
        Window(Game* game, WindowType type, uint16_t windowWidth = 0,
                    uint16_t windowHeight = 0, const char* title = "",
                    void (*key_callback)(GLFWwindow*,int,int,int,int) = nullptr);

        private:

        void adjustProjection(); // Adjust projection for any changes in screen size
        void initializeProjection(); // Set projection to proper transform

        public:
        

        // Callbacks
        void framebuffer_size_callback(int width, int height);
        void key_callback(int key, int scancode, int action, int mode);

        const glm::mat4& projection() {return projection_;}
        
        void setDimensions(int width, int height);
        void processInput();
        void swapBuffers();
        bool shouldClose();
        void setWindowShouldClose(bool state);
    };

    
}