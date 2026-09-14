#include "pch.h"
#include "GameLayer.h"
#include "EFS/Events/EventDispatcher.h"
#include <imgui.h>
namespace EFS {
    void GameLayer::OnEvent(Event& event)
    {
        EventDispatcher Dispatch(event);
        if (Dispatch.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& event) { return OnKeyPress(event); })) { return; }

    }

    bool GameLayer::OnKeyPress(KeyPressedEvent& event)
    {
        EFS_INFO("Player Moved type event {0}", event.GetKeyCode());
        return true;
    }

    void GameLayer::OnImGuiRender()
    {
        static int compteur2 = 0;
        ImGui::Begin("Mon deuxieme Panneau");
        ImGui::End();
    }
}
