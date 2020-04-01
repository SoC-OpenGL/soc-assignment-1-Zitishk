#include<iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include "shader.h"


void makevertices(float ver[])
{
    for (int j=0;j<9;j++)
    {
        for(int i=0;i<9;i++)
        {
            int ind=3*(i+(9*j));
            ver[ind]=-0.4f +0.1f*i;
            ver[ind+1]=-0.4f +0.1f*j;
            ver[ind+2]=0.0f;
        }
    }
}

void makeindices(unsigned int ind[],int k)
{
    int t=k;
    
    for(int j=0;j<8;j++)
    {
        for(int i=0;i<4;i++)
        {
            int ri=4*j+i;
            ind[6*ri]=t;
            ind[6*ri+1]=t+1;
            ind[6*ri+2]=9+t;
            ind[6*ri+3]=t+1;
            ind[6*ri+4]=t+9;
            ind[6*ri+5]=10+t;
            t+=2;
        }
        if((j+k)%2==0)
        {
            t+=2;
        }
    }
}



const GLint WIDTH = 800, HEIGHT = 600;

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
    
    
    
    float vertices[81*3];
    makevertices(vertices);
    
    unsigned int indicesofw[3*64];
    unsigned int indicesofb[3*64];
    makeindices(indicesofw,0);
    makeindices(indicesofb,1);
    
    
    /*
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    //check success
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader,512, NULL,infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    int FragmentShader1;
    FragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader1,1,&fragmentShaderSource1, NULL);
    glCompileShader(FragmentShader1);
    GLint success2;
    GLchar infoLog2[512];
    glGetShaderiv(FragmentShader1, GL_COMPILE_STATUS,&success2);
    if(!success2)
    {
        glGetShaderInfoLog(FragmentShader1,512, NULL,infoLog2);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog2 << std::endl;
    }
    int Shaeder;
    Shaeder=glCreateProgram();
    glAttachShader(Shaeder,vertexShader);
    glAttachShader(Shaeder,FragmentShader1);
    glLinkProgram(Shaeder);
    //check
    glGetProgramiv(Shaeder, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(Shaeder, 512,NULL, infoLog);
        std::cout<<"ERROR in program::Linking failed\n"<< infoLog<< std::endl;
    }
    glDeleteShader(vertexShader);
    
    glDeleteShader(FragmentShader1);
    
    
    int FragmentShader2;
    FragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader2,1,&fragmentShaderSource2, NULL);
    glCompileShader(FragmentShader2);
    
    glGetShaderiv(FragmentShader2, GL_COMPILE_STATUS,&success2);
    if(!success2)
    {
        glGetShaderInfoLog(FragmentShader2,512, NULL,infoLog2);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog2 << std::endl;
    }
    int shaeder2;
    shaeder2=glCreateProgram();
    glAttachShader(shaeder2,vertexShader);
    glAttachShader(shaeder2,FragmentShader2);
    glLinkProgram(shaeder2);
    //check
    glGetProgramiv(shaeder2, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaeder2, 512,NULL, infoLog);
        std::cout<<"ERROR in program::Linking failed\n"<< infoLog<< std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(FragmentShader2);
    */
    
    ShaderProgram Shaeder1(1);
    ShaderProgram Shaeder2(2);
    
    unsigned int VAO1;
    glGenVertexArrays(1,&VAO1);
    
    unsigned int VBO, EBO;
    
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    
    glBindVertexArray(VAO1);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesofw), indicesofw,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    
    unsigned int VAO2;
    glGenVertexArrays(1,&VAO2);
    
    unsigned int EBO2;
    
    glGenBuffers(1,&EBO2);
    
    glBindVertexArray(VAO2);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO2);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesofb), indicesofb,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    while( !glfwWindowShouldClose( window ))
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT);
        
        glBindVertexArray(VAO1);
        
        glUseProgram(Shaeder1.program);
        glDrawElements(GL_TRIANGLES,3*64,GL_UNSIGNED_INT,0);
        
        glBindVertexArray(0);
        glBindVertexArray(VAO2);
        
        glUseProgram(Shaeder2.program);
        glDrawElements(GL_TRIANGLES,3*64,GL_UNSIGNED_INT,0);
        
        glfwSwapBuffers( window);
        glfwPollEvents( );
    }
    
    glBindVertexArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    
    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &EBO2);
    
    glfwTerminate( );
    return 0;
}

