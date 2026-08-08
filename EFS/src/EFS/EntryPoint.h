#pragma once
#include "Core\Application.h"
int main(int argc ,char** argv)
{
	EFS::log::Init();
	EFS::Application* App = new EFS::Application();
	App->Run();
	delete App;
}