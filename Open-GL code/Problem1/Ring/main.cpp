#include<iostream>
#include <math.h>
#define GLEW_STATIC
#include <GL/glew.h>

#include "shader.h"
#include <GLFW/glfw3.h>

// just change n for better approx circle
// change various attributes of ring
const int n=30;

float center[] = { 0.0f, 0.0f, 0.0f};

float r1= 0.6f;

float r2= 0.4f;



void DrawCircle(float vertices[2*3*n], float ori[3], float r,int a)
{
    for(int i=a;i<a+n;i++)
    {
        double a=3.14*2*i/n;
        float om[3]={0.0f,0.0f,0.0f};
        float x=r*cos(a);
        float y= r*sin(a);
        om[0]= x +ori[0];
        om[1]= y + ori[1];
        vertices[3*i]=om[0];
        vertices[3*i+1]=om[1];
        vertices[3*i+2]=om[2];
    }
    return;
}
const GLint WIDTH = 600, HEIGHT = 600;


//source code of vshaders and fshaders

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";


const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.1f, 0.6f, 1.0f);\n"
"}\n\0";

// for resizing window
void framebuffer_size_callback (GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


int main(){
    
    // setting up our window and initializing glew/glfw
    
    glfwInit();
    
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_TRUE );
    
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "LEARN OPENGL HEHE", NULL, NULL);
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window,&screenWidth, &screenHeight );
    
    if (window == NULL)
    {
        std::cout<<"Failed "<< std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent( window );
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cout<<"Failed "<< std::endl;
        return -1;
    }
    
    glViewport( 0,0,screenWidth,screenHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   
    //creating vertices for our circle

    
    float vertices[2*3*n];
    
    DrawCircle(vertices, center, r1,0);
    DrawCircle(vertices,center,r2,n);
    
    //creating indices for the triangles
    
    unsigned int indices[2*3*n];
    int t=0;
    for(int i=0;i<n;i++)
    {
        indices[6*i]=t;
        indices[6*i+1]=t+1;
        indices[6*i+2]=n+t;
        indices[6*i+3]=t+1;
        indices[6*i+4]=n+t;
        indices[6*i+5]=n+t+1;
        t++;
    }
    indices[6*n-1]=0;
    indices[6*n-2]=n-1;

    //creating vertex shaders and fragment shaders
    
    ShaderProgram Shaeder;
    
    //creating VAO,VBO,EBO
    
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    
    unsigned int VBO,EBO;
    
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    
    //enable to see only borders
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    
    while( !glfwWindowShouldClose( window ))
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT);
        
        glUseProgram(Shaeder.program);
        glDrawElements(GL_TRIANGLES, 6*n, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers( window);
        glfwPollEvents( );
    }

    //unbinding and deleting
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1,&EBO);
    
    glfwTerminate( );
    return 0;
}
