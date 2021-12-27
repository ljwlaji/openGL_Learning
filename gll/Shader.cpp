//
//  Shader.cpp
//  gll
//
//  Created by lijingwei on 2021/12/15.
//

#include "Shader.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>
#include "Renderer.hpp"

Shader* Shader::Create(const char* vp, const char* fp)
{
    Shader* shader = nullptr;
    do
    {
        std::ifstream vertx(vp, std::ios::in | std::ios::binary);
        if (!vertx || !vertx.is_open())
            break;
        std::ifstream frag(fp, std::ios::in | std::ios::binary);
        if (!frag || !frag.is_open())
            break;
        
        vertx.seekg(0, std::ios::end);
        long long length = vertx.tellg();
        vertx.seekg(0, std::ios::beg);
        char* vbuffer = (char*)alloca(length);
        vertx.read(vbuffer, length);
        vertx.close();
        
        frag.seekg(0, std::ios::end);
        length = frag.tellg();
        frag.seekg(0, std::ios::beg);
        char* fbuffer = (char*)alloca(length);
        frag.read(fbuffer, length);
        frag.close();
        
        shader = new(std::nothrow)Shader();
        shader->CreateShaderProgram(vbuffer, fbuffer);
    }
    while(0);
    
    return shader;
}

Shader::Shader() : m_GLShaderProgram(0)
{

}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_GLShaderProgram));
    m_GLShaderProgram = 0;
}


void Shader::Bind()
{
    glUseProgram(m_GLShaderProgram);
}

unsigned int Shader::CompileShader(unsigned int type, const char* source)
{
    unsigned int id = glCreateShader(type);
    // id glCreateShader的句柄 Specifies the handle of the shader object whose source code is to be replaced.
    // count 这边传入的src是一个 char** 类型的数组指针，我们在这边需要指定这个数组内有多少个char*指针 这边只有一个 所以传入1 Specifies the number of elements in the string and length arrays.
    // char**指针的地址 Specifies an array of pointers to strings containing the source code to be loaded into the shader.
    // length 这边char**指针内的char*数量大于1的话可以在这版传入一个数组，这个数组包含每个char*的长度 Specifies an array of string lengths.
    GLCall(glShaderSource(id, 1, &source, nullptr));
    GLCall(glCompileShader(id));
    
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        //some thing wrong
        int lenth;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenth);
        char* message = (char*)alloca(lenth * sizeof(char));
        glGetShaderInfoLog(id, lenth, &lenth, message);
        std::cout << "Shader Compile" << (type == GL_FRAGMENT_SHADER ? "Fragment" : "Vertex") << "Failed" << source << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

bool Shader::CreateShaderProgram(const char* vertexShader, const char* fragmentShader)
{
    m_GLShaderProgram = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    if (!vs || !fs) return false;
    GLCall(glAttachShader(m_GLShaderProgram, vs));
    GLCall(glAttachShader(m_GLShaderProgram, fs));
    
    GLCall(glLinkProgram(m_GLShaderProgram));
    
    GLCall(glValidateProgram(m_GLShaderProgram));
    
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    return true;
}

bool Shader::setUniform1f(const char* name, const float& input)
{
    int location = glGetUniformLocation(m_GLShaderProgram, name);
    if (location == -1)
        return false;
    GLCall(glUniform1f(location, input));
    return true;
}

bool Shader::setUniform2f(const char* name, const float& inputa, const float& inputb)
{
    int location = glGetUniformLocation(m_GLShaderProgram, name);
    if (location == -1)
        return false;
    GLCall(glUniform2f(location, inputa, inputb));
    return true;
}

bool Shader::setUniform3f(const char* name, const float& inputa, const float& inputb, const float& inputc)
{
    int location = glGetUniformLocation(m_GLShaderProgram, name);
    if (location == -1)
        return false;
    GLCall(glUniform3f(location, inputa, inputb, inputc));
    return true;
}

bool Shader::setUniform4f(const char* name, const float& inputa, const float& inputb, const float& inputc, const float& inputd)
{
    int location = glGetUniformLocation(m_GLShaderProgram, name);
    if (location == -1)
        return false;
    GLCall(glUniform4f(location, inputa, inputb, inputc, inputd));
    return true;
}
