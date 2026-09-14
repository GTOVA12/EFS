#pragma once
#include "EFS/Core/Layer.h"
namespace EFS {
	class EFSAPI ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnAttach() override;
		void OnDetach() override;
		void OnEvent(Event& event) override;
		void Begin();
		void End();
		void OnImGuiRender() override;
	};
}

