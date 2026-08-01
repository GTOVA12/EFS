#include "EFS.h"

class Sandbox : public EFS::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}

};
EFS::Application* EFS::CreateApplication()
{
	return new Sandbox;
}