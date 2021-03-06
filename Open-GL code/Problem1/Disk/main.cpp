#include<iostream>
#include <math.h>
#include "shader.h"


#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
const GLint WIDTH = 600, HEIGHT = 600;


void framebuffer_size_callback (GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


int main(){
    
    
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
    
    float vertices[]={
        0.5f,0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        -0.5f,-0.5f,0.0f,
        -0.5f,0.5f,0.0f
    };

    unsigned int indices[] ={
        0,1,3, //tr1
        1,2,3 //tr2
    };
    
    ShaderProgram Shaeder;
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    
    unsigned int VBO;
    unsigned int EBO;

    
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    
    while( !glfwWindowShouldClose( window ))
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT);
        
        
        glUseProgram(Shaeder.program);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        
        
        glfwSwapBuffers( window);
        glfwPollEvents( );
    }
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
    glfwTerminate( );
    return 0;
}
