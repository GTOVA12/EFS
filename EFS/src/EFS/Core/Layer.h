#pragma once
#include "Core.h"
#include "EFS/Events/Event.h"
namespace EFS {

	class EFSAPI Layer
	{
	protected:
		std::string m_DebugName;
	public:
		Layer(const std::string& Name = "Layer") :m_DebugName(Name) {};
		virtual ~Layer() = default;
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender(){}

		inline const std::string& GetName() const { return m_DebugName; }

	};
}

