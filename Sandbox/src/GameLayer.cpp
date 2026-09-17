#include "pch.h"
#include "GameLayer.h"
#include "EFS/Events/EventDispatcher.h"
#include <imgui.h>
namespace EFS {
    static float red = 0;
    void GameLayer::OnAttach()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        
    }
    void GameLayer::OnDetach()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
    void GameLayer::OnEvent(Event& event)
    {
        EventDispatcher Dispatch(event);
        if (Dispatch.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& event) { return OnKeyPress(event); })) { return; }

    }

    void GameLayer::OnUpdate(float DeltaTime)
    {
        m_DeltaTime =  DeltaTime;
        if (m_Motion == Motion::Extending)
            m_PositionX += m_Speed * DeltaTime;
        else if (m_Motion == Motion::Retracting)
            m_PositionX -=m_Speed * DeltaTime;
        if (m_PositionX >= 0.5f)
        {
            m_PositionX = 0.5f;
            m_Motion = Motion::Stopped;
        }
        if (m_PositionX <=-0.5f)
        {
            m_PositionX = -0.5f;
            m_Motion = Motion::Stopped;
        }
        m_Shader.use();
        glBindVertexArray(VAO);
        m_Shader.SetFloat("red", red);
        m_Shader.SetFloat("u_PositionX", m_PositionX);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    bool GameLayer::OnKeyPress(KeyPressedEvent& event)
    {
        EFS_INFO("Player Moved type event {0}", event.GetKeyCode());
        return true;
    }

    void GameLayer::OnImGuiRender()
    {
        if (ImGui::Begin("Panneau de couleur"))
        {
            if (ImGui::Button("Sortir"))
                m_Motion = Motion::Extending;

            ImGui::SameLine();

            if (ImGui::Button("Rentrer"))
                m_Motion = Motion::Retracting;

            if (ImGui::Button("Stop"))
                m_Motion = Motion::Stopped;

            if (ImGui::Button("Reinitialiser"))
            {
                m_PositionX = -0.5f;
                m_Motion = Motion::Stopped;
            }
            //ImGui::SliderFloat("RedColor", &red, 0.0f, 1.0f);
            ImGui::Text("Temps par image : %.2f ms", m_DeltaTime * 1000.0f);
            ImGui::Text("Position X : %.3f", m_PositionX);
            ImGui::Text("Butee atteinte : %s",
                m_PositionX >= 0.5f ? "oui" : "non");
        }
        ImGui::End();
    }
}
