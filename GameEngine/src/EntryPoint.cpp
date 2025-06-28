#include "gepch.h"

#include "Application.h"
#include "Logging/Log.h"

int main(int argc, char* argv)
{
	Log::Init();

	INFO("Started!");

	Application* app = new Application();
	app->run();
	delete app;
	
	return 0;
}