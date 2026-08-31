#pragma once
#include "EFS/Core/Layer.h"
namespace EFS {
	class EFSAPI ImGuiLayer : public Layer
	{
	public:
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
	};
}

