#include <MaineCoon/Core/Application.h>
#include <MaineCoon/Core/EntryPoint.h>

#include <MaineCoon/Graphics/Image.h>

class ExampleLayer : public MaineCoon::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Hellasdasdaso");
		ImGui::Button("Button");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};

MaineCoon::Application* MaineCoon::CreateApplication(int argc, char** argv)
{
	MaineCoon::ApplicationSpecification spec;
	spec.Name = "MaineCoon Example";

	MaineCoon::Application* app = new MaineCoon::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}