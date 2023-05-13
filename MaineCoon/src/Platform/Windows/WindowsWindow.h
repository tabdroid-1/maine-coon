//
// Created by Tristan Zippert on 5/23/21.
//
//
// Created by Tristan Zippert on 5/22/21.
//


#include "TabbyEngine/Core/Window.h"
#include "TabbyEngine/Renderer//GraphicsContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace TabbyEngine{
    class WindowsWindow: public Window{
    public:
        WindowsWindow(const WindowProps & props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override {return m_Data.Width; }
        inline unsigned int GetHeight() const override {return m_Data.Height; }

        //Window attributes

        inline void SetEventCallback(const EventCallbackfn& callback) override {m_Data.EventCallback = callback; }
        void  SetVSync(bool enabled) override;
        bool IsVsync() const override;

        virtual void* GetNativeWindow() const { return m_Window; }
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    private:
        GLFWwindow* m_Window;
        Scope<GraphicsContext> m_Context;

        struct WindowData{
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackfn EventCallback;
        };
        WindowData m_Data;
    };
}

