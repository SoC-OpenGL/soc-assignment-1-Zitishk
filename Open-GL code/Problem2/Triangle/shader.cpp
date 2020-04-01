#include"shader.h"
#include <iostream>
#include <string>
ShaderProgram :: ShaderProgram(void)
{
    vShaderCode = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 acolor;\n"
    "out vec3 color;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   color = vec3(acolor);\n"
    "}\0";
    fShaderCode = "#version 330 core\n"
    "in vec3 color;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(color, 1.0f);\n"
    "}\n\0";
    
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1,&vShaderCode,NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader,512, NULL,infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader,1,&fShaderCode, NULL);
    glCompileShader(FragmentShader);
    
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(FragmentShader,512, NULL,infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    
    program=glCreateProgram();
    glAttachShader(program,vertexShader);
    glAttachShader(program,FragmentShader);
    glLinkProgram(program);
    //check
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(program, 512,NULL, infoLog);
        std::cout<<"ERROR in program::Linking failed\n"<< infoLog<< std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(FragmentShader);
    
};
