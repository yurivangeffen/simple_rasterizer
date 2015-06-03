#include <cstdio>
#include <GL/gl3w.h>
#include "rasterizer.h"
#include <iostream>

Rasterizer::Rasterizer()
{
    
}

Rasterizer::~Rasterizer()
{
}

void Rasterizer::CompileShaders()
{
  const GLchar* vertexSource =
  {
    "#version 400\n"\
    
    "layout(location=0) in vec4 position;\n"\
    "layout(location=1) in vec4 color;\n"\
    "out vec4 vsColor;\n"\
    
    "void main(void)\n"\
    "{\n"\
    "   gl_Position = position;\n"\
    "   vsColor = color;\n"\
    "}\n"
  };
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);
  CheckCompilation(vertexShader);
  
  const GLchar* fragmentSource =
  {
    "#version 400\n"\
    
   "in vec4 vsColor;\n"
    "out vec4 outColor;\n"\
    
    "void main()\n"\
    "{\n"\
    "   outColor = vsColor;\n"\
    "}\n"
  };
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);
  CheckCompilation(fragmentShader);
  
  // Link into a single program
  shaderProgram_ = glCreateProgram();
  glAttachShader(shaderProgram_, vertexShader);
  glAttachShader(shaderProgram_, fragmentShader);
  if(glGetError() != 0)
    fprintf(stderr, "Got an error...");

  
}

void Rasterizer::CheckCompilation(GLuint shaderSource)
{
  GLint status;
  glGetShaderiv(shaderSource, GL_COMPILE_STATUS, &status);
  if(status != GL_TRUE)
  {
    std::cout << "Shader compilation was unsuccesful!" << std::endl;
    char buffer[512];
    glGetShaderInfoLog(shaderSource, 512, NULL, buffer);
    std::cout << buffer << std::endl;
    return;
  }
  
  std::cout << "Shader compilation was succesful!" << std::endl;
}

bool Rasterizer::Init()
{
  
  
  vertices_ = {0.0f,  0.5f, // Vertex 1 (X, Y)
      0.5f, -0.5f, // Vertex 2 (X, Y)
        -0.5f, -0.5f};  // Vertex 3 (X, Y)
  
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  if(glGetError() != 0)
    fprintf(stderr, "Got an error...");
  
  GLuint vbo;
  glGenBuffers(1, &vbo);
  if(glGetError() != 0)
    fprintf(stderr, "Got an error...");
  
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), static_cast<void*>(&vertices_), GL_STATIC_DRAW);
  if(glGetError() != 0)
    fprintf(stderr, "Got an error...");
  
  CompileShaders();
  
  glLinkProgram(shaderProgram_);
  glValidateProgram(shaderProgram_);
  char buffer[512];
  glGetProgramInfoLog(shaderProgram_, 512, NULL, buffer);
  std::cout << buffer << std::endl;
  
  
  glUseProgram(shaderProgram_);
  if(glGetError() != 0)
    fprintf(stderr, "Got an error...");
  
  glBindFragDataLocation(shaderProgram_, 0, "out_Color");
  
  GLint posAttrib = glGetAttribLocation(shaderProgram_, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
  if(glGetError() != 0)
    fprintf(stderr, "Got an error...");


  
  return true;
}


bool Rasterizer::Rasterize()
{
    
  glDrawArrays(GL_TRIANGLES, 0, 3);
  
  if(glGetError() != 0)
      fprintf(stderr, "Got an error...");
  
  return true;
}