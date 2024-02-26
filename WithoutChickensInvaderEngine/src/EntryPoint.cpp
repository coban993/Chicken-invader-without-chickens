#include "EntryPoint.h"
#include "framework\Application.h"

int main()
{
	wci::Application* app = GetApplication();
	app->Run();
	delete app;
}