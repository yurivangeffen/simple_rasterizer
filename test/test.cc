#include <cstdio>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <rasterizer.h>

// --------------------------------------------------------------------------------------------------------------

int main(int argc, char ** argv)
{
    Rasterizer* rasterizer;
    GLFWwindow* window;
    
    // Initialize the library
    if (!glfwInit())
        return -1;
    
    // Setting openGL window hints to make sure we run the right version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "YurBot's Rasterizeur", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    // Make the window's context current
    glfwMakeContextCurrent(window);
    
    if (gl3wInit()) {
        fprintf(stderr, "Failed to initialize OpenGL\n");
        return -1;
    }
    if (!gl3wIsSupported(3, 2)) {
        fprintf(stderr, "OpenGL 3.2 not supported\n");
        return -1;
    }
    
    rasterizer = new Rasterizer();
    if(!rasterizer->Init()) {
        fprintf(stderr, "Unable to initialize rasterizer!");
        return -1;
    }
    
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        // Render here
        rasterizer->Rasterize();
        
        // Swap front and back buffers
        glfwSwapBuffers(window);
        
        // Poll for and process events
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    delete rasterizer;
    return 0;
}
