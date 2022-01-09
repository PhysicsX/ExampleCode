#include <iostream>
#include <fstream>
#include <string>
#include <GLES2/gl2.h>
#include <GLFW/glfw3.h>
#include <math.h>
#define GL_SILENCE_DEPRECATION 1

// vertex shader source
// g++ -pthread -o multipleVBO multipleVBO.cpp -lGLU -lGL -lXrandr -lXi -lX11 `pkg-config --static --libs glfw3` && ./multipleVBO 

const GLchar* vertex120 = R"END(
#version 120
attribute vec4 inPosition;
attribute vec4 inColor;
uniform mat4 matrix;
// pass color info to fragment shader with varying keyword.
// It will interpolate the color over the vertices
varying vec4 outColor;
void main()
{
    outColor = inColor;
    gl_Position = inPosition * matrix;
}
)END";

// fragment shader source

const GLchar* raster120 = R"END(
#version 120
varying vec4 outColor;
void main()
{
    gl_FragColor = outColor; //vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)END";

int main()
{
    // -------------- init
    
    GLFWwindow * window;
    
    if (!glfwInit()) {
        std::cout << "Init error";
        return -1;
    }
    
    window = glfwCreateWindow(600,600,"Hello",0,0);
    
    if (!window) {
        std::cout << "Window creation error";
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    std::cout << "Init :: checking OpenGL version:\n";
    const unsigned char * msg;
    msg = glGetString(GL_VERSION);
    std::cout << msg << "\n Shader language version: \n";
    msg = glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cout << msg << "\n";
    
    const char* source;
    GLint compilationStatus;
    
    // ------------- VERTEX SHADER
    
    source = vertex120;
    
    GLuint shaderVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaderVertex,1,&source,0);
    glCompileShader(shaderVertex);
    
    glGetShaderiv(shaderVertex, GL_COMPILE_STATUS, &compilationStatus);
    if (compilationStatus == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderVertex, sizeof(messages), 0, &messages[0]); std::cout << messages;
        exit(1);
    }
    
    // ---------- FRAGMENT SHADER
    
    source = raster120;
    
    GLuint shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shaderFragment,1,&source,0);
    glCompileShader(shaderFragment);
    
    glGetShaderiv(shaderFragment, GL_COMPILE_STATUS, &compilationStatus);
    if (compilationStatus == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderFragment, sizeof(messages), 0, &messages[0]); std::cout << messages;
        exit(1);
    }
    
    // ------------- SHADER PROGRAM
    
    GLint linkStatus;
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,shaderVertex);
    glAttachShader(shaderProgram,shaderFragment);
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&linkStatus);
    if (linkStatus == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(shaderProgram,sizeof(messages),0,&messages[0]);
        std::cout << messages;
        exit(1);
    }
    
    glUseProgram(shaderProgram);
    
    // ---------------- VBOs
    
    GLfloat colors[] = {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
        0, 1, 0,
        1, 0, 0,
        0, 0, 1
    };

    GLfloat vertices[] = {
        // First triangle
        -1.0f, -1.0f, 0.0f,  // Left 
        0.0f, 1.0f, 0.0f,  // Right
        0.0f, -1.0f, 0.0f,  // Top 
        // Second triangle
         0.0f, 1.0f, 0.0f,  // Left
         1.0f, -1.0f, 0.0f,  // Right
         0.0f, -1.0f, 0.0f   // Top 
    };
    
    GLuint positionsData;
    glGenBuffers(1, &positionsData);
    glBindBuffer(GL_ARRAY_BUFFER,positionsData);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    GLuint colorsData;
    glGenBuffers(1, &colorsData);
    glBindBuffer(GL_ARRAY_BUFFER, colorsData);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW); // memcpy() -> to GPU's vram buffer
    
    // ----------------- attributes
    GLuint attribPosition;
    GLuint attribColor;
    
    attribPosition = glGetAttribLocation(shaderProgram, "inPosition");
    glEnableVertexAttribArray(attribPosition);
    glBindBuffer(GL_ARRAY_BUFFER, positionsData);
    glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    attribColor = glGetAttribLocation(shaderProgram, "inColor");
    glEnableVertexAttribArray(attribColor);
    glBindBuffer(GL_ARRAY_BUFFER, colorsData);
    glVertexAttribPointer(attribColor, 3, GL_FLOAT, GL_FALSE, 0, 0);
    

    //uniforms
    GLuint attributeMatrix = glGetUniformLocation(shaderProgram, "matrix");
    float alpha = 0;

    // ----------------- render loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);

        float sa = 0.6 * sin(alpha);
        float ca = 0.6 * cos(alpha);
        alpha += 0.001;

        const GLfloat matrix[]={
            sa, -ca, 0, 0,
            ca,  sa, 0, 0,
            0,   0,  1, 0,
            0,   0,  0, 1
        };

        glUniformMatrix4fv(attributeMatrix, 1, GL_FALSE, matrix);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
}
