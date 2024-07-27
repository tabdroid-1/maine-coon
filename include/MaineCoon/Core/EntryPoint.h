#pragma once

#include <MaineCoon/Core/Application.h>

extern MaineCoon::Application* MaineCoon::CreateApplication(ApplicationCommandLineArgs args);

#if defined(MC_PLATFORM_ANDROID)

#define SDL_MAIN_HANDLED
#include "../../../vendor/SDL2/include/SDL_main.h"
int main(int argc, char** argv)
{
    MaineCoon::Log::Init();

    auto app = MaineCoon::CreateApplication({ argc, argv });

    app->Run();

    delete app;
}

int SDL_main(int argc, char* argv[])
{
    return main(argc, argv);
}

#elif defined(MC_PLATFORM_LINUX)
int main(int argc, char** argv)
{
    MaineCoon::Log::Init();

    auto app = MaineCoon::CreateApplication({ argc, argv });

    app->Run();

    delete app;
}

#elif defined(MC_PLATFORM_WINDOWS)

namespace MaineCoon {

int Main(int argc, char** argv)
{
    MaineCoon::Log::Init();

    auto app = MaineCoon::CreateApplication({ argc, argv });

    app->Run();

    delete app;

    return 0;
}

}

#ifdef MAINECOON_DIST

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    return MaineCoon::Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
    return MaineCoon::Main(argc, argv);
}

#endif

#elif defined(MC_PLATFORM_MACOS)
int main(int argc, char** argv)
{
    MaineCoon::Log::Init();

    auto app = MaineCoon::CreateApplication({ argc, argv });

    app->Run();

    delete app;
}

#elif defined(MC_PLATFORM_WEB)

#include <emscripten.h>

void run(void* data)
{
    auto app = (MaineCoon::Application*)data;
    app->Run();
}

int main(int argc, char** argv)
{
    MaineCoon::Log::Init();

    auto app = MaineCoon::CreateApplication({ argc, argv });

    emscripten_set_main_loop_arg((em_arg_callback_func)run, (void*)app, 0, 1);

    delete app;
}
#endif
