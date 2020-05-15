#include <glm/gtc/matrix_transform.hpp>
#include "GameObject.hpp"

GameObject::GameObject(std::vector<GLfloat>& vertices) {
    m_vertices = vertices;
    m_useIndices = false;
}

GameObject::GameObject(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices) {
    m_vertices = vertices;
    m_indices = indices;
    m_useIndices = true;
}

void GameObject::SetShader(GLuint& shaderId) noexcept {
    m_shaderId = shaderId;
}

void GameObject::SetPosition(glm::vec3& position) noexcept {
    m_position = position;
}

void GameObject::OffsetPosition(glm::vec3& posOffset) noexcept {
    m_position += posOffset;
}

void GameObject::SetRotation(glm::vec3& rotation) noexcept {
    m_rotation = rotation;
}

void GameObject::OffsetRotation(glm::vec3& rotOffset) noexcept {
    m_rotation += rotOffset;
}

void GameObject::SetScale(glm::vec3& scale) noexcept {
    m_scale = scale;
}

void GameObject::OffsetScale(glm::vec3& sclOffset) noexcept {
    m_scale += sclOffset;
}

glm::mat4 GameObject::GetTransform(void) const noexcept {
    glm::mat4 trans(1.0f);
    trans = glm::translate(trans, m_position);
    trans = glm::rotate(trans, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::rotate(trans, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    trans = glm::rotate(trans, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    trans = glm::scale(trans, m_scale);
    return trans;    
}

void GameObject::Render(void) const {
    //glUseProgram(m_shaderId); // disabled whilst shaders require special data sent in
    //glBindVertexArray(m_vaoId);
    if (m_useIndices) {
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
    }
    else {
        glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    }
}
