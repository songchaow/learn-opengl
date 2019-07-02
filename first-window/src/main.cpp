#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>

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
      
      // vertex shader
      unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
      std::ifstream vshader_src("src/vertex.glsl");
      std::string shader_text;
      shader_text = std::string(std::istreambuf_iterator<char>(vshader_src), std::istreambuf_iterator<char>());
      const char* array_start = shader_text.c_str();;
      glShaderSource(vertexShader, 1, &array_start, NULL);
      glCompileShader(vertexShader);
      // check
      int  success;
      char infoLog[512];
      glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
      if (!success)
      {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
      }

      // fragment shader
      unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
      std::ifstream fshader_src("src/pixel.glsl");

      shader_text = std::string(std::istreambuf_iterator<char>(fshader_src), std::istreambuf_iterator<char>());
      array_start = shader_text.c_str();
      glShaderSource(fragmentShader, 1, &array_start, NULL);
      glCompileShader(fragmentShader);

      glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
      if (!success)
      {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
      }

      // link to shader program
      unsigned int program = glCreateProgram();
      glAttachShader(program, vertexShader);
      glAttachShader(program, fragmentShader);
      glLinkProgram(program);

      glGetProgramiv(program, GL_LINK_STATUS, &success);
      if (!success) {
            glGetProgramInfoLog(program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
      }

      unsigned int VAO, VAO2;
      glGenVertexArrays(1, &VAO);
      glGenVertexArrays(1, &VAO2);
      glBindVertexArray(VAO);

      // feed vertices
      float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.9f,  0.9f, 0.0f
      };
      float vertices2[] = {
    -0.3f, -0.2f, 0.0f,
     0.6f, -0.6f, 0.0f,
     0.1f,  0.3f, 0.0f,
     0.1f,  0.6f, 0.0f,
     0.6f, -0.6f, 0.0f,
     0.8f,  0.8f, 0.0f
      };
      unsigned int VBO, VBO2;
      glGenBuffers(1, &VBO);
      glGenBuffers(1, &VBO2);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      // configure vertex attribute
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);

      // draw
      glUseProgram(program);
      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 6);
      glfwSwapBuffers(window);
      // draw2
      glBindVertexArray(VAO2);
      glBindBuffer(GL_ARRAY_BUFFER, VBO2);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);
      glDrawArrays(GL_TRIANGLES, 0, 6);
      glfwSwapBuffers(window);
      // switch VBO
      glBindVertexArray(VAO);
      
      glDrawArrays(GL_TRIANGLES, 0, 6);
      glfwSwapBuffers(window);
      while (!glfwWindowShouldClose(window))
      {
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glfwSwapBuffers(window);
            glfwPollEvents();
      }

      glfwTerminate();
      return 0;
}

