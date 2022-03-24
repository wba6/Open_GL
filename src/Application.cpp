#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "texture.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "tests/testClearColor.h"
#include "tests/testCreateSquare.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void framebuffer_size_callback(GLFWwindow *window, int width = 640, int height = 480) {
    glViewport(0, 0, width, height);
}

int main(void) {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    //sets to core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //window width and hight
    unsigned int width{960},height{540};
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    //sets vsync or monitor refresh rate
    glfwSwapInterval(1);
    //specifies the view of the window -https://learnopengl.com/Getting-started/Hello-Window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    /*inits glewInit*/
    if (glewInit() != GLEW_OK)
        std::cout << "Glew init failed" << std::endl;

    glViewport(0,0,width,height);
    std::cout << glGetString(GL_VERSION) << std::endl;
    {

        //enables blending for textures
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();
        test::TestClearColor color;
        test::TestCreateSquare square(&renderer);
        //test::TestClearColor test;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            renderer.clear();

            //OnUpdate(0.0f);
            color.OnRender();
            square.OnRender();
            ImGui_ImplGlfwGL3_NewFrame();
            color.OnImGuiRender();
            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    // Cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    glfwTerminate();
    return 0;
}
