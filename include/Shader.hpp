#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    GLuint m_id;

    Shader(const std::string& vShaderPath, const std::string& fShaderPath);
    void Use(void) const noexcept;
    void SetBool(const std::string& name, GLboolean value) const;
    void SetInt(const std::string& name, GLint value) const;
    void SetFloat(const std::string& name, GLfloat value) const;
    void SetUInt(const std::string& name, GLuint value) const;
};

#endif //_SHADER_HPP_
