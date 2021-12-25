#include <iostream>
#include <GLFW/glfw3.h>
#include <math.h>

// sudo apt-get install libglfw3
// sudo apt-get install libglfw3-dev
// check related dependencies with pkg-config --static --libs glfw3.
// g++ -pthread -o circle circleGlfw.cpp -lglfw -lGLU -lGL -lXrandr -lXi -lX11 -lrt -ldl
// or
// g++ -pthread -o circle circleGlfw.cpp -lGLU -lGL -lXrandr -lXi -lX11 `pkg-config --static --libs glfw3`

const int steps = 100;
const float angle = 3.1415926 * 2.f / steps;

int main() {
    GLFWwindow * window;
    
    if (!glfwInit()) {
        std::cout << "Init error";
        return -1;
    }
    
    window = glfwCreateWindow(800,600,"Circle",0,0);
    if (!window) {
        std::cout << "Window creation error";
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    float xPos = 0; 
    float yPos = 0; 
    float radius = 1.0f;
    
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0,1.0,1.0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        float prevX = xPos;
        float prevY = yPos - radius;
        
        for (int i=0;i<=1;i++) {
            float newX = radius * sin(angle*i);
            float newY = -radius * cos(angle*i);
            
            glBegin(GL_TRIANGLES);
            glColor3f(0,0.5f,0);
            glVertex3f(0.0f,0.0f,0.0f);
            glVertex3f(prevX,prevY,0.0f);
            glVertex3f(newX,newY,0.0f);
            glEnd();
            
            prevX = newX;
            prevY = newY;
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}
