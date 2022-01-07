//
//  Shader.hpp
//  gll
//
//  Created by lijingwei on 2021/12/15.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <../includes/glm/glm.hpp>
#include "Ref.hpp"
class Shader : public Ref
{
public:
    static Shader* Create(const char* vp, const char* fp);
    Shader();
    ~Shader();
    
    unsigned int getRandererID() const { return m_GLShaderProgram; }
    void Bind();
    
    bool setUniform1i(const char* name, const int& input);
    
    
    bool setUniform1f(const char* name, const float& input);
    bool setUniform2f(const char* name, const float& inputa, const float& inputb);
    bool setUniform3f(const char* name, const float& inputa, const float& inputb, const float& inputc);
    bool setUniform4f(const char* name, const float& inputa, const float& inputb, const float& inputc, const float& inputd);
    bool setUniformMat4f(const char* name, const glm::mat4& martix);
private:
    unsigned int CompileShader(unsigned int type, const char* source);
    bool CreateShaderProgram(const char* vertexShader, const char* fragmentShader);

    
    unsigned int m_GLShaderProgram;
};


#endif /* Shader_hpp */
