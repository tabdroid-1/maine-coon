#include "MaineCoon/Renderer/Renderer.h"

namespace MaineCoon {

void Renderer::Init()
{
    MC_PROFILE_SCOPE();

    RenderCommand::Init();
}

void Renderer::Shutdown()
{
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
    RenderCommand::SetViewport(0, 0, width, height);
}

}
