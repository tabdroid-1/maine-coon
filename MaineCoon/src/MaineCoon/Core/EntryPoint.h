#pragma once

#include <MaineCoon/Core/Application.h>

#ifdef __APPLE__

extern MaineCoon::Application* MaineCoon::CreateApplication(int argc, char** argv);
bool g_ApplicationRunning = true;

namespace MaineCoon {

	int Main(int argc, char** argv)
	{
		while (g_ApplicationRunning)
		{
			MaineCoon::Application* app = MaineCoon::CreateApplication(argc, argv);
			app->Run();
			delete app;
		}

		return 0;
	}

}

int main(int argc, char** argv)
{
	return MaineCoon::Main(argc, argv);
}


#endif 