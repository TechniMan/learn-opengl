#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    const GLfloat MIN_PITCH = -60.0f, MAX_PITCH = 60.0f;
    const GLfloat MIN_FOV = 10.0f, MAX_FOV = 90.0f;
    const GLfloat SPEED = 2.5f;

    GLfloat m_yaw = -90.0f, m_pitch = 0.0f, m_fov = 60.0f;
    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 m_forward = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_right = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    void OffsetYaw(GLfloat yawOffset) noexcept;
    void OffsetPitch(GLfloat pitchOffset) noexcept;

public:
    void UpdateYawAndPitch(GLfloat yaw, GLfloat pitch) noexcept;
    void Translate(glm::vec3 axes, GLfloat deltaTime) noexcept;

    glm::vec3 GetPosition(void) const noexcept;
    glm::mat4 GetViewMatrix(void) const noexcept;
};

#endif //_CAMERA_HPP_
