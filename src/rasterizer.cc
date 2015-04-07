#include <cstdio>
#include <GL/gl3w.h>
#include "rasterizer.h"

Rasterizer::Rasterizer()
{
    
}

Rasterizer::~Rasterizer()
{
    delete vertices_;
}

bool Rasterizer::Init()
{
    vertices_ = new float[6]{
        0.0f,  0.5f, // Vertex 1 (X, Y)
        0.5f, -0.5f, // Vertex 2 (X, Y)
        -0.5f, -0.5f  // Vertex 3 (X, Y)
    };
    
    const GLchar* vertexSource =
    {
        "#version 400\n"\
        
        "layout(location=0) in vec4 in_Position;\n"\
        "layout(location=1) in vec4 in_Color;\n"\
        "out vec4 ex_Color;\n"\
        
        "void main(void)\n"\
        "{\n"\
        "   gl_Position = in_Position;\n"\
        "   ex_Color = in_Color;\n"\
        "}\n"
    };
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    
    const GLchar* fragmentSource =
    {
        "#version 400\n"\
        
        "in vec4 ex_Color;\n"\
        "out vec4 out_Color;\n"\
        
        "void main(void)\n"\
        "{\n"\
        "   out_Color = ex_Color;\n"\
        "}\n"
    };
    GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    
    shaderProgram_ = glCreateProgram();
    glAttachShader(shaderProgram_, vertexShader);
    glAttachShader(shaderProgram_, fragmentShader);
    
    glBindFragDataLocation(shaderProgram_, 0, "outColor");
    glLinkProgram(shaderProgram_);
    glUseProgram(shaderProgram_);
    
    GLint posAttrib = glGetAttribLocation(shaderProgram_, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_STREAM_DRAW);
    
    return true;
}

bool Rasterizer::Rasterize()
{
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    if(glGetError() != 0)
        fprintf(stderr, "Got an error...");
    
    return true;
}