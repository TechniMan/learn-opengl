#include "../include/Shader.hpp"

Shader::Shader(const std::string& vShaderPath, const std::string& fShaderPath) {
    std::string vShaderSource;
    std::ifstream vShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::string fShaderSource;
    std::ifstream fShaderFile;
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    std::string curShader = "VERTEX";
    try {
        std::stringstream vShaderStream, fShaderStream;
        vShaderFile.open(vShaderPath);
        vShaderStream << vShaderFile.rdbuf();
        vShaderFile.close();
        vShaderSource = vShaderStream.str();
        curShader = "FRAGMENT";
        fShaderFile.open(fShaderPath);
        fShaderStream << fShaderFile.rdbuf();
        fShaderFile.close();
        fShaderSource = fShaderStream.str();
    }
    catch (std::ifstream::failure ex) {
        std::cout << "ERROR::" << curShader << "_SHADER::CANT_READ_FILE" << std::endl;
    }

    const char* vShaderCode = vShaderSource.c_str();
    const char* fShaderCode = fShaderSource.c_str();

    GLuint vShaderId, fShaderId;
    GLint success;
    GLchar infoLog[512];

    vShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShaderId, 1, &vShaderCode, nullptr);
    glCompileShader(vShaderId);
    glGetShaderiv(vShaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShaderId, 512, nullptr, infoLog);
        std::cout << "ERROR::VERTEX_SHADER::COMPILATION FAILED" << std::endl;
        std::cout << infoLog << std::endl;
        throw;
    }

    fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShaderId, 1, &fShaderCode, nullptr);
    glCompileShader(fShaderId);
    glGetShaderiv(fShaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fShaderId, 512, nullptr, infoLog);
        std::cout << "ERROR::FRAGMENT_SHADER::COMPILATION FAILED" << std::endl;
        std::cout << infoLog << std::endl;
        throw;
    }

    m_id = glCreateProgram();
    glAttachShader(m_id, vShaderId);
    glAttachShader(m_id, fShaderId);
    glLinkProgram(m_id);
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINK FAILED" << std::endl;
        std::cout << infoLog << std::endl;
        throw;
    }

    glDeleteShader(vShaderId);
    glDeleteShader(fShaderId);
}

void Shader::Use(void) const noexcept {
    glUseProgram(m_id);
}

void Shader::SetBool(const std::string& name, GLboolean value) const {
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (GLint)value);
}

void Shader::SetFloat(const std::string& name, GLfloat value) const {
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::SetInt(const std::string& name, GLint value) const {
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::SetMatrix4(const std::string& name, glm::mat4 value) const {
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUInt(const std::string& name, GLuint value) const {
    glUniform1ui(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::SetVector3(const std::string& name, glm::vec3 value) const {
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y, value.z);
}
