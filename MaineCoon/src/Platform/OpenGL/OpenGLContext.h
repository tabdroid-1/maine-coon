//
// Created by Tristan Zippert on 5/25/21.
//
#pragma once
#include "TabbyEngine/Renderer/GraphicsContext.h"


struct GLFWwindow;

namespace TabbyEngine{

    class OpenGLContext: public GraphicsContext{
    public:
        OpenGLContext(GLFWwindow* windowHandle);


        virtual void Init() override;
        virtual void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };
}

