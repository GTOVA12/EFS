#pragma once
#include "Core.h"
namespace EFS 
{
	class EFSAPI Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};
	Application* CreateApplication();
}

