#pragma once
#include "Core\Application.h"
int main(int argc ,char** argv)
{
	EFS::log::Init();
	//EFS_Core_ERROR("TestColor");
	//EFS_ERROR("TestColods");
	//EFS::Application* App = EFS::CreateApplication();
	//App->Run();
	//delete App;

	EFS::Application* App = new EFS::Application();
	App->Run();
	delete App;
}