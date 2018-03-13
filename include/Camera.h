#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

enum CameraDirection {
  FORWARD,
  BACK,
  LEFT,
  RIGHT
};

enum CameraType {
  ORTHO,
  PERSPECTIVE
};

class Camera {
public:
  Camera(int width, int height);
  Camera(int width, int height, glm::vec3 init_position);

  inline glm::mat4 GetViewMatrix() {
    return glm::lookAt(position, position + forward, up);
  }

  inline glm::mat4 GetProjectionMatrix() {
    return glm::perspective(glm::radians(fov), (float)screen_width / screen_height, 0.1f, 100.0f);
  }

  inline void UpdateScreenSize(float width, float height) {
    this->screen_width = width;
    this->screen_height = height;
  }

  void ChangePosition(CameraDirection dir, float deltaTime);
  void ChangeDirection(float xoffset, float yoffset);
  void ChangeZoom(float yoffset);

  void EnableChangeDirection() {
    can_change_direction = true;
  }
  void DisableChangeDirection() {
    can_change_direction = false;
  }

  inline glm::vec3 GetPosition() {
    return position;
  }

  inline glm::vec3 GetFront() {
    return forward;
  }

  inline int GetScreenWidth() {
    return screen_width;
  }
  inline int GetScreenHeight() {
    return screen_height;
  }

private:
  glm::vec3 position, rotation, scale;
  glm::vec3 forward, up, right;
  int screen_width, screen_height;
  float fov;
  float camera_speed, sensitivity;
  
  bool can_change_direction;
};


#endif // !__CAMERA_H__