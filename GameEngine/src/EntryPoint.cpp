#include "gepch.h"

#include "Application.h"
#include "Logging/Log.h"

int main(int argc, char* argv)
{
	Log::Init();
	INFO("Started!");

	Application* app = new Application();
	app->Run();
	delete app;
}