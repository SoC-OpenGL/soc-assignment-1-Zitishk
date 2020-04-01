#ifndef shader_h
#define shader_h

#include<iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

struct ShaderProgram
{
    int vertexShader;
    GLint success;
    GLchar infoLog[512];
    int FragmentShader;
    int program;
    const char* vShaderCode;
    const char * fShaderCode1;
    const char * fShaderCode2;

    ShaderProgram(int a);
};

#endif /* shader_h */
