#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include "shader.h"

int main()
{
      glfwInit();
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
      // create window
      GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
      if (window == NULL)
      {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
      }
      glfwMakeContextCurrent(window);

      if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
      {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
      }
      glViewport(0, 0, 800, 600);
      
      Shader shader("src/vertex.glsl", "src/pixel.glsl");

      unsigned int VAO;
      glGenVertexArrays(1, &VAO);
      glBindVertexArray(VAO);

      // feed vertices
      float vertices[] = {
     0.5f, 0.5f, 0.0f,   // ÓÒÉÏ½Ç
     1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f,  // ÓÒÏÂ½Ç
    0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, // ×óÏÂ½Ç
    0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.0f,   // ×óÉÏ½Ç
    0.0f, 0.0f, 0.0f
      };
      unsigned int VBO;
      glGenBuffers(1, &VBO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
      // feed indices
      unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
      };
      unsigned int EBO;
      glGenBuffers(1, &EBO);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

      // configure vertex attribute
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
      glEnableVertexAttribArray(1);

      // draw
      shader.use();
      glBindVertexArray(VAO); // actually it's been done before
      glDrawArrays(GL_TRIANGLES, 0, 3);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

      glfwSwapBuffers(window);
      while (!glfwWindowShouldClose(window))
      {
            /*glDrawArrays(GL_TRIANGLES, 0, 3);
            glfwSwapBuffers(window);*/
            glfwPollEvents();
      }

      glfwTerminate();
      return 0;
}

