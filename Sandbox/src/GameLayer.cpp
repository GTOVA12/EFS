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
        glGenBuffers(1, &CBO);
        glGenBuffers(1, &EBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, CBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, CBO);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);

        
    }
    void GameLayer::OnDetach()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &CBO);
        glDeleteBuffers(1, &EBO);
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

        float extension = m_PositionX + 0.5f;

        glm::mat4 rodModel(1.0f);
        rodModel = glm::translate(rodModel,
            glm::vec3(extension * 0.6f, 0.0f, 0.0f));
        rodModel = glm::scale(rodModel, glm::vec3(0.7f, 0.08f, 1.0f));
        m_Shader.setMat4("u_Model", rodModel);
        m_Shader.SetVec3("u_Color", glm::vec3(0.75f));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glm::mat4 bodyModel(1.0f);
        bodyModel = glm::translate(bodyModel, glm::vec3(-0.10f, 0.0f, 0.0f));
        bodyModel = glm::scale(bodyModel, glm::vec3(0.7f, 0.3f, 1.0f));

        m_Shader.setMat4("u_Model", bodyModel);
        m_Shader.SetVec3("u_Color", glm::vec3(0.15f));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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
