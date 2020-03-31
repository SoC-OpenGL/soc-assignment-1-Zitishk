

#include<iostream>
#include <math.h>



#define GLEW_STATIC
#include <GL/glew.h>
#include "shader.h"
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// just change n for better approx circle
// change various attributes of ring
const int n=30;
float origin[2]={0.5f,0.5f};
float center[] = { 0.0f, 0.0f, 0.0f};

float r1= 0.6f;

float r2= 0.2f;
float r3= 0.3f;

float convertx(float a)
{
    float f=(a/1.4f)+0.5f;
    return f;
}
float converty(float a)
{
    float f=(a/1.2f)+0.5f;
    return f;
}

void DrawCircle(float vertices[], float ori[3], float r,int inn,int k)
{
    int vno=0;
    for(int i=inn;i<inn+n;i++)
    {
        double a=M_PI*vno/(n-1);
        float om[3]={0.0f,0.0f,0.0f};
        float x=r*cos(a);
        float y= k*r*sin(a);
        om[0]= x +ori[0];
        om[1]= y + ori[1];
        vertices[8*i]=om[0];
        vertices[8*i+1]=om[1];
        vertices[8*i+2]=om[2];
        vertices[8*i+3]=0.5f;
        vertices[8*i+4]=0.5f;
        vertices[8*i+5]=0.5f;
        vertices[8*i+6]=(om[0]/1.4f)+origin[0];
        vertices[8*i+7]=(om[1]/1.2f)+origin[1];
        
        vno++;
    }
    vertices[8*(n+inn)]=ori[0];
    vertices[8*(n+inn)+1]=ori[1];
    vertices[8*(n+inn)+2]=ori[2];
    vertices[8*(n+inn)+3]=0.5f;
    vertices[8*(n+inn)+4]=0.5f;
    vertices[8*(n+inn)+5]=0.5f;
    vertices[8*(n+inn)+6]=(ori[0]/1.4f)+origin[0];
    vertices[8*(n+inn)+7]=(ori[1]/1.2f)+origin[1];
    return;
}



void Indiceforcircle(unsigned int ind[],int start,int stofv)
{
    int t=stofv;
    for(int i=start;i<(n-1)+start;i++)
    {
        ind[3*i]=n+stofv;
        ind[(3*i)+1]=t;
        ind[(3*i)+2]=t+1;
        t++;
    }
}




const GLint WIDTH = 600, HEIGHT = 600;

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
    
     float vertices[8*n+8];
     
     DrawCircle(vertices, center, r1,0,1);
     
     //creating indices for the triangles
     
     unsigned int indice[3*(n-1)];
     Indiceforcircle(indice, 0,0);
    
    
    float vot[]={
        -0.6f,0.0f,0.0f, 1.0f, 0.0f, 0.0f,  convertx(-0.6f),converty(0.0f),
        -0.7f,-0.3f,0.0f, 1.0f, 0.0f, 0.0f,  convertx(-0.7f),converty(-0.3f),
        0.6f,0.0f,0.0f,   1.0f, 0.0f, 0.0f,  convertx(0.6f),converty(0.0f),
        0.7f,-0.3f,0.0f,  1.0f, 0.0f, 0.0f,  convertx(0.7f),converty(-0.3f)
    };
    unsigned int iot[]={
        0,1,2,
        1,2,3
    };
    
    
     float vof1[8*(3*n+3)];
     
     float cof1[]={-0.5f,-0.3f,0.0f};
     
     DrawCircle(vof1, cof1, r2,0,-1);
     
     float cof2[]={0.5f,-0.3f,0.0f};
     
     DrawCircle(vof1, cof2, r2,n+1,-1);
     
     float cof3[]={0.0f,-0.3f,0.0f};
     
     DrawCircle(vof1, cof3, r3,2*(n+1),-1);
     
     
     unsigned int iof[3*3*(n-1)];
     Indiceforcircle(iof, 0,0);
     Indiceforcircle(iof, (n-1),n+1);
     Indiceforcircle(iof, 2*(n-1),2*n+2);
     

    ShaderProgram Shaeder;
    
    //creating VAO,VBO,EBO
    
     unsigned int VAO1;
     glGenVertexArrays(1,&VAO1);
     
     unsigned int VBO1,EBO1;
     
     glGenBuffers(1,&VBO1);
     glGenBuffers(1,&EBO1);
     
     glBindVertexArray(VAO1);
     
     glBindBuffer(GL_ARRAY_BUFFER,VBO1);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO1);
     
    glBufferData(GL_ARRAY_BUFFER,sizeof(vof1),vof1,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(iof),iof,GL_STATIC_DRAW);
     
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
     
    unsigned int VAO2;
    glGenVertexArrays(1,&VAO2);
    
    unsigned int VBO2,EBO2;
    
    glGenBuffers(1,&VBO2);
    glGenBuffers(1,&EBO2);
    
    glBindVertexArray(VAO2);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO2);
    
    glBufferData(GL_ARRAY_BUFFER,sizeof(vot),vot,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(iot),iot,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    
     unsigned int VAO3;
     glGenVertexArrays(1,&VAO3);
     
     unsigned int VBO3,EBO3;
     
     glGenBuffers(1,&VBO3);
     glGenBuffers(1,&EBO3);
     
     glBindVertexArray(VAO3);
     
     glBindBuffer(GL_ARRAY_BUFFER,VBO3);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO3);
     
     glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indice),indice,GL_STATIC_DRAW);
     
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);
     
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    
    
    unsigned int texturing;
    glGenTextures(1, &texturing);
    glBindTexture(GL_TEXTURE_2D, texturing);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int pwidth, pheight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("/Users/Zitishk/Desktop/OpenGL/GLFW openGL/GLFW openGL/slime.jpg", &pwidth, &pheight, &nrChannels,0);
    
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pwidth, pheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else std:: cout<<"image failed"<<std::endl;
    
    stbi_image_free(data);
    
    //enable to see only borders
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    
    while( !glfwWindowShouldClose( window ))
    {
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT);
        
        glBindTexture(GL_TEXTURE_2D, texturing);
        glBindVertexArray(VAO1);
        
        glUseProgram(Shaeder.program);
        
        glDrawElements(GL_TRIANGLES, 9*(n-1), GL_UNSIGNED_INT, 0);
         
        glBindVertexArray(0);
        
        glBindVertexArray(VAO2);
        glBindTexture(GL_TEXTURE_2D, texturing);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
         
        glBindVertexArray(VAO3);
         
        glDrawElements(GL_TRIANGLES, 3*(n-1), GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers( window);
        glfwPollEvents( );
    }
    //unbinding and deleting
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    
    glDeleteVertexArrays(1, &VAO3);
    glDeleteVertexArrays(1, &VAO1);
    glDeleteVertexArrays(1, &VAO2);
    
    glDeleteBuffers(1, &VBO1);
    glDeleteBuffers(1,&EBO1);
    glDeleteBuffers(1, &VBO2);
    glDeleteBuffers(1,&EBO2);
    glDeleteBuffers(1, &VBO3);
    glDeleteBuffers(1,&EBO3);
    
    glfwTerminate( );
    return 0;
}
