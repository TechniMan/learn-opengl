#include "Camera.hpp"

void Camera::OffsetYaw(GLfloat yawOffset) noexcept {
    m_yaw += yawOffset;
}

void Camera::OffsetPitch(GLfloat pitchOffset) noexcept {
    m_pitch += pitchOffset;
    if (m_pitch > MAX_PITCH) { m_pitch = MAX_PITCH; }
    else if (m_pitch < MIN_PITCH) { m_pitch = MIN_PITCH; }
}

void Camera::UpdateYawAndPitch(GLfloat yaw, GLfloat pitch) noexcept {
    OffsetYaw(yaw);
    OffsetPitch(pitch);

    m_forward.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
    m_forward.y = sin(glm::radians(m_pitch));
    m_forward.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
    m_forward   = glm::normalize(m_forward);

    m_right = glm::normalize(glm::cross(m_forward, m_up));
}

void Camera::Translate(glm::vec3 axes, GLfloat deltaTime) noexcept {
    const GLfloat speed = SPEED * deltaTime;
    //m_position += axes * speed;
    m_position += axes.x * m_right * speed;
    m_position += axes.y * m_up * speed;
    m_position += axes.z * m_forward * speed;
}

glm::mat4 Camera::GetViewMatrix(void) const noexcept {
    return glm::lookAt(m_position, m_position + m_forward, m_up);
}
