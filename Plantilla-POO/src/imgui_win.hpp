#ifndef IMGUIWIN_HPP
#define IMGUIWIN_HPP

#include <Windows.h>

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw.h"
#include "imgui\imgui_impl_opengl3.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <string>

namespace ImGuiWin
{
    ImVec4 fondo = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImVec4 color_figura = ImVec4(0.2f, 0.85f, 0.2f, 1.00f);

    bool multicolor = false;
    bool render_shape = false;
    float vel_mov = 0.4;

    void renderMainWindow()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        ImGui::Begin("ImGui-Window");     
                /* COLOR EDIT */
            ImGui::TextColored(ImVec4(1,1,0,1), "Color");
            ImGui::Indent();
                ImGui::ColorEdit3("Color Fondo", (float *)&fondo);         
                ImGui::ColorEdit3("Color Shape", (float *)&color_figura); 
                ImGui::Checkbox("Modo Multicolor", &multicolor); 
            ImGui::Unindent();

                /* SHAPES */
            ImGui::TextColored(ImVec4(1,1,0,1), "Shape");
            ImGui::Indent();
                ImGui::Checkbox("Pintar", &render_shape);
            ImGui::Unindent();

            ImGui::TextColored(ImVec4(1,1,0,1), "Velocidad");
            ImGui::Indent();
                ImGui::SliderFloat("Vel. mov.", &vel_mov, 0.1, 10);
            ImGui::Unindent();

            if (ImGui::CollapsingHeader("Controles")){
                ImGui::Separator();
                ImGui::BulletText("WASD para mover el objeto");
                ImGui::BulletText("Arrastre con el mouse para rotaciones");
                ImGui::BulletText("Presione R para deshacer todas las transformaciones");
                ImGui::Separator();
            }
            
            ImGui::Text("Rendimiento %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::End();

    }

    void endMainWindow()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void cleanAll()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

}

#endif