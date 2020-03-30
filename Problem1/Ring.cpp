#include<iostream>
#include <math.h>
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

// just change n for better approx circle
const int n=30;
void DrawCircle(float vertices[3*n], float ori[3], float r)
{
    for(int i=0;i<n;i++)
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
    
    float vertices[3*n];
    float center[] = { 0.0f, 0.0f, 0.0f};
    float radius= 0.5f;
    DrawCircle(vertices, center, radius);


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
    
    int FragmentShader;
    
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader,1,&fragmentShaderSource, NULL);
    glCompileShader(FragmentShader);
    
    
    GLint success2;
    GLchar infoLog2[512];
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS,&success2);
    if(!success2)
    {
        glGetShaderInfoLog(FragmentShader,512, NULL,infoLog2);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog2 << std::endl;
    }
    
    int Shaeder;
    Shaeder=glCreateProgram();
    
    glAttachShader(Shaeder,vertexShader);
    glAttachShader(Shaeder,FragmentShader);
    glLinkProgram(Shaeder);
    //check
    
    glGetProgramiv(Shaeder, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(Shaeder, 512,NULL, infoLog);
        std::cout<<"ERROR in program::Linking failed\n"<< infoLog<< std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(FragmentShader);
    
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    
    unsigned int VBO;
    
    glGenBuffers(1,&VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while( !glfwWindowShouldClose( window ))
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT);
        
        glUseProgram(Shaeder);

        glDrawArrays(GL_LINE_LOOP, 0, n);
        glfwSwapBuffers( window);
        glfwPollEvents( );
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    glfwTerminate( );
    return 0;
}

