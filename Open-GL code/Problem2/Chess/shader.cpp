#include"shader.h"
#include <iostream>
#include <string>
ShaderProgram :: ShaderProgram(int a)
{
    vShaderCode = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    fShaderCode1 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n\0";
    
    fShaderCode2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
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
    
    if(a==1)
    {
        glShaderSource(FragmentShader,1,&fShaderCode1, NULL);
    }
    else if (a==2)
    {
        glShaderSource(FragmentShader,1,&fShaderCode2, NULL);
    }
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
