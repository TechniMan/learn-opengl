#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <glad/glad.h>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    void SetMatrix4(const std::string& name, glm::mat4 value) const;
    void SetUInt(const std::string& name, GLuint value) const;
    void SetVector3(const std::string& name, glm::vec3 value) const;
};

#endif //_SHADER_HPP_
