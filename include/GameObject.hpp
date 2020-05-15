#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class GameObject {
private:
    GLuint m_shaderId;
    GLuint m_vaoId;
    std::vector<GLfloat> m_vertices;
    std::vector<GLuint> m_indices;
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
    bool m_useIndices = false;

public:
    GameObject(std::vector<GLfloat>& vertices);
    GameObject(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);

    void SetShader(GLuint& shaderId) noexcept;
    void SetPosition(glm::vec3& position) noexcept;
    void OffsetPosition(glm::vec3& posOffset) noexcept;
    void SetRotation(glm::vec3& rotation) noexcept;
    void OffsetRotation(glm::vec3& rotOffset) noexcept;
    void SetScale(glm::vec3& scale) noexcept;
    void OffsetScale(glm::vec3& sclOffset) noexcept;

    glm::mat4 GetTransform(void) const noexcept;
    void Render(void) const;
};

#endif //_GAMEOBJECT_HPP_