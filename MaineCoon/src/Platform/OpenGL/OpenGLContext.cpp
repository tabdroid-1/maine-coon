//
// Created by Tristan Zippert on 5/25/21.
//
#include "tbpch.h"
#include "OpenGLContext.h"


#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace TabbyEngine{
    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
        :m_WindowHandle(windowHandle)
    {
        TABBY_CORE_ASSERT(m_WindowHandle, "Window is null");

    }
    void OpenGLContext::Init() {
        TABBY_PROFILE_FUNCTION();

        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        TABBY_CORE_ASSERT(status, "failed to init glad loader");

        TABBY_CORE_INFO("OpenGL info: ");
        TABBY_CORE_INFO("   Vendor: {0}", (void*)glGetString(GL_VENDOR));
        TABBY_CORE_INFO("   Renderer: {0}", (void*)glGetString(GL_RENDERER));
        TABBY_CORE_INFO("   Version: {0}", (void*)glGetString(GL_VERSION));
    }
    void OpenGLContext::SwapBuffers() {
        TABBY_PROFILE_FUNCTION();
        glfwSwapBuffers(m_WindowHandle);
    }
}
