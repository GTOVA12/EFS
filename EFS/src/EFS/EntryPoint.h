#pragma once
#include "Application.h"
int main(int argc ,char** argv)
{
	/*EFS::InitLog();*/
	EFS::Application* App = EFS::CreateApplication();
	App->Run();
	delete App;

}