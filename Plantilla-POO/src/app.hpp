#ifndef APP_CPP
#define APP_CPP

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw.h"
#include "imgui\imgui_impl_opengl3.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <stdlib.h>

#include "controls.hpp"
#include "imgui_win.hpp"
#include "utils.hpp"
#include "shape.h"
#include "shader.h"


class AppOpenGL
{
private:
    glm::mat4 projMat;
    glm::mat4 modelviewMat;
    glm::mat4 viewMat;

public:
    AppOpenGL() {}
    void init();
    void setup();
    void display();
    void cleanAll();
    bool shouldClose();
    GLFWwindow *window;
    int width, heigth;
    glm::vec3 camera;

    Shader sp{"src/vertex.glsl", "src/fragment.glsl"};
    
    Shape myShape;
};

void AppOpenGL::init()
{

    width = 800;
    heigth = 800;
    camera = glm::vec3(0, 0, 8.0);

    if (!glfwInit())
    {
        exit(1);
        std::cout << "GLFW Error" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(width, heigth, "Template-POO", NULL, NULL);
    glfwMakeContextCurrent(window);

    // glew init
    if (glewInit() != GLEW_OK)
    {
        exit(1);
        std::cout << "GLEW Error" << std::endl;
    }

    glfwSwapInterval(0);

    glfwSetCursorPosCallback(window, Controls::cursor_position_callback);
    glfwSetMouseButtonCallback(window, Controls::mouse_button_callback);
    glfwSetScrollCallback(window, Controls::scroll_callback);
    glfwSetKeyCallback(window, Controls::key_callback);
    glfwSetWindowSizeCallback(window, Controls::window_size_callback);

    // imgui init
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void AppOpenGL::setup()
{
    sp.compile();
    sp.bind();

    int w, h;
    glfwGetWindowSize(window, &w, &h);
    projMat = glm::perspective(1.0472f, (float)w / (float)h, 0.1f, 1000.0f);
    Controls::pMat = projMat;
   
    myShape.initData();

    viewMat = glm::translate(glm::mat4(1.0), glm::vec3(-camera.x, -camera.y, -camera.z));
}


void AppOpenGL::display()
{
    sp.bind();

    modelviewMat = viewMat;
    modelviewMat *= Controls::getTransf();

    sp.setUniformMat4fv("mv_matrix", modelviewMat);
    sp.setUniformMat4fv("proj_matrix", Controls::pMat);

    if (ImGuiWin::multicolor == false){
        sp.setUniform1i("multicolor", 0);
    }
    if (ImGuiWin::multicolor == true){
        sp.setUniform1i("multicolor", 1);
    } 

    Controls::velocidadMov = ImGuiWin::vel_mov;

    glClearColor(ImGuiWin::fondo.x,
                 ImGuiWin::fondo.y,
                 ImGuiWin::fondo.z,
                 ImGuiWin::fondo.w);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

    glEnable(GL_LINE_SMOOTH);
    glLineWidth(2.5); // "ancho" de lineas

    glm::vec3 color;

    color = glm::vec3(ImGuiWin::color_figura.x,
                      ImGuiWin::color_figura.y,
                      ImGuiWin::color_figura.z);

    sp.setUniform3fv("u_color", color);

    if (ImGuiWin::render_shape)
    {
        myShape.render();
    }

    ImGuiWin::renderMainWindow();
    ImGuiWin::endMainWindow();

    glfwPollEvents();
    glfwSwapBuffers(window);
}

void AppOpenGL::cleanAll()
{
    ImGuiWin::cleanAll();
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool AppOpenGL::shouldClose()
{
    return glfwWindowShouldClose(window);
}

#endif
