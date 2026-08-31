#pragma once
#include "Core\Application.h"
int main(int argc ,char** argv)
{
	EFS::log::Init();
	EFS::Application* App =	EFS::CreateApplication();
	App->Run();
	delete App;
}