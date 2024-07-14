#include <MaineCoon.h>
#include <MaineCoon/Core/EntryPoint.h>
#include <MaineCoon/Core/Application.h>
#include <MaineCoon/Audio/AudioEngine.h>

class ExampleLayer : public MaineCoon::Layer {
public:
    ExampleLayer()
    {
        m_Texture = MaineCoon::AssetManager::Get()->LoadAssetSource("textures/Tabby.png");
        MaineCoon::Audio::Engine::SetPlayerMusic("music/sunflower-street.wav");
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Hellasdasdaso");
        if (ImGui::Button("Play/Pause")) {
            if (!MaineCoon::Audio::Engine::IsMusicPlaying())
                MaineCoon::Audio::Engine::PlayMusicPlayer();
            else
                MaineCoon::Audio::Engine::PauseMusicPlayer();
        }

        if (ImGui::Button("File Dialog Open")) {
            MC_INFO("{0}", MaineCoon::FileDialogs::OpenFile(".png"));
        }
        if (ImGui::Button("File Dialog Save")) {
            MC_INFO("{0}", MaineCoon::FileDialogs::SaveFile(".png"));
        }

        auto texture = MaineCoon::AssetManager::Get()->GetAsset<MaineCoon::Texture>(m_Texture);
        ImGui::Image((void*)texture->GetRendererID(), { (float)texture->GetWidth(), (float)texture->GetHeight() });
        ImGui::End();

        ImGui::ShowDemoWindow();
    }

private:
    MaineCoon::AssetHandle m_Texture;
};

class Sandbox : public MaineCoon::Application {
public:
    Sandbox(const MaineCoon::ApplicationSpecification& specification)
        : MaineCoon::Application(specification)
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {
    }
};

MaineCoon::Application* MaineCoon::CreateApplication(MaineCoon::ApplicationCommandLineArgs args)
{
    ApplicationSpecification spec;
    spec.Name = "A winfow";
    spec.WorkingDirectory = "assets";
    spec.CommandLineArgs = args;
    spec.maxFPS = 0.0f;

    Application* app = new Sandbox(spec);
    app->SetMenubarCallback([app]() {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Exit")) {
                app->Close();
            }
            ImGui::EndMenu();
        }
    });
    return app;
}
