#include "OpenGLES3Context.h"
#include "GLES3.h"

#ifdef MC_PLATFORM_WEB
#define GLAD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#elif defined(MC_PLATFORM_ANDROID)
#include <SDL_egl.h>
#include <SDL_syswm.h>
#endif

#define GLAD_GLES2_IMPLEMENTATION
#include <gles3.h>

#include <SDL.h>

namespace MaineCoon {

OpenGLES3Context::OpenGLES3Context(SDL_Window* windowHandle)
    : m_WindowHandle(windowHandle)
{
    MC_CORE_ASSERT_TAGGED(windowHandle, "Window handle is null!");
}

void OpenGLES3Context::Init()
{
    MC_PROFILE_SCOPE();

    SDL_GLContext windowContext = SDL_GL_CreateContext(m_WindowHandle);
    SDL_GL_MakeCurrent(m_WindowHandle, windowContext);

    GladGLES2Context* context = (GladGLES2Context*)calloc(1, sizeof(GladGLES2Context));
    MC_CORE_ASSERT_TAGGED(context, "Failed to initialize GLES3 context!");

#if defined(MC_PLATFORM_ANDROID)
    int status = gladLoadGLES2Context(context, (GLADloadfunc)eglGetProcAddress);
#else
    int status = gladLoadGLES2Context(context, (GLADloadfunc)SDL_GL_GetProcAddress);
#endif

    MC_CORE_ASSERT_TAGGED(status, "Failed to initialize Glad!");

    GLES3::Init(context);

    MC_CORE_INFO("OpenGL Info:");
    MC_CORE_INFO("  Vendor: {0}", GLES3::GL()->GetString(GL_VENDOR));
    MC_CORE_INFO("  Renderer: {0}", GLES3::GL()->GetString(GL_RENDERER));
    MC_CORE_INFO("  Version: {0}", GLES3::GL()->GetString(GL_VERSION));

    std::string version = reinterpret_cast<const char*>(GLES3::GL()->GetString(GL_VERSION));
    size_t dotPosition = version.find('.');

    int major = std::stoi(version.substr(dotPosition - 1));
    int minor = std::stoi(version.substr(dotPosition + 1));

    MC_CORE_ASSERT_TAGGED(major >= 3, "MaineCoon requires at least OpenGL ES version 3.0!");
}

void OpenGLES3Context::SwapBuffers()
{
    MC_PROFILE_SCOPE();

    SDL_GL_SwapWindow(m_WindowHandle);
}

}
