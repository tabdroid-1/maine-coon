//
// Created by Tristan Zippert on 5/23/21.
//
#include "WindowsWindow.h"
#include "tbpch.h"

#include "TabbyEngine/Events/MouseEvent.h"
#include "TabbyEngine/Events/ApplicationEvent.h"
#include "TabbyEngine/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"


namespace TabbyEngine{
    static bool s_GLFWInitialized = false;
    static uint8_t  s_GLFW_Win_Count = 0;

    static void GLFWErrorCallback(int error, const char* desc){
        TABBY_CORE_ERROR("GLFW Error {{0}}: {1}", error, desc);
    }

    WindowsWindow::WindowsWindow(const WindowProps &props) {
        Init(props);
    }
    WindowsWindow::~WindowsWindow(){
        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps &props) {
        TABBY_PROFILE_FUNCTION();

        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        TABBY_CORE_INFO("Creating window {0} ({1} {2})", props.Title, props.Width, props.Height);

        if (!s_GLFWInitialized){
            int success = glfwInit();
            TABBY_ASSERT(success, "could not init GLFW");
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }
        {
            ++s_GLFW_Win_Count;
        }
        int actualScreenWidth, actualScreenHeight;

        m_Window = glfwCreateWindow((int)props.Width,(int)props.Height,m_Data.Title.c_str(), nullptr, nullptr);

        m_Context = GraphicsContext::Create(m_Window);
        m_Context->Init();

        glfwGetFramebufferSize(m_Window,&actualScreenWidth,&actualScreenHeight);

        glfwSetWindowUserPointer(m_Window,&m_Data);
        // Windows specific call
        SetVSync(true);

        //GLFW callbacks
        glfwSetWindowSizeCallback(m_Window,[](GLFWwindow* window, int width, int height){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            data.Width = width;
            data.Height = height;
            WindowResizeEvent event(width,height);
            data.EventCallback(event);

        });
        glfwSetWindowCloseCallback(m_Window,[](GLFWwindow* window){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });
        glfwSetKeyCallback(m_Window,[](GLFWwindow* window, int key, int scancode, int action, int mods){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key,0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key,1);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
            }
        });
        glfwSetCharCallback(m_Window,[](GLFWwindow* window, unsigned int keycode) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window,[](GLFWwindow* window, double xOffset, double yOffset){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset,(float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window,[](GLFWwindow* window, double xPos, double yPos){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float )xPos, (float)yPos);
            data.EventCallback(event);
        });
    }

    void WindowsWindow::Shutdown() {
        TABBY_PROFILE_FUNCTION();
        glfwDestroyWindow(m_Window);
        --s_GLFW_Win_Count;

        if(s_GLFW_Win_Count)
            glfwTerminate();
    }

    void WindowsWindow::OnUpdate() {
        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void WindowsWindow::SetVSync(bool enabled) {
        glfwSwapInterval((int)enabled);
        m_Data.VSync = enabled;
    }
    bool WindowsWindow::IsVsync() const {
        return m_Data.VSync;
    }
    
}