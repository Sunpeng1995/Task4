#include "Camera.h"

using namespace glm;

Camera::Camera(int width, int height) : 
  Camera(width, height, vec3(0.0f, 0.0f, 3.0f)) {

}

Camera::Camera(int width, int height, vec3 initPos) :
  screen_width(width), screen_height(height),
  position(initPos), rotation(vec3(0, -90.0f, 0)),
  fov(45.0f), camera_speed(2.5f), sensitivity(0.05f)
{
  forward = vec3(0, 0, -1.0f);
  up = vec3(0, 1.0f, 0);
  right = normalize(cross(forward, up));
  can_change_direction = false;
}

void Camera::ChangePosition(CameraDirection dir, float deltaTime) {
  float speed = deltaTime * camera_speed;
  switch (dir)
  {
  case FORWARD:
    position += speed * forward;
    break;
  case BACK:
    position -= speed * forward;
    break;
  case LEFT:
    position -= speed * right;
    break;
  case RIGHT:
    position += speed * right;
    break;
  default:
    break;
  }
}

void Camera::ChangeDirection(float xoffset, float yoffset) {
  if (!can_change_direction) {
    return;
  }
  rotation.y += xoffset * sensitivity;
  rotation.x += yoffset * sensitivity;

  if (rotation.x > 89.0f) {
    rotation.x = 89.0f;
  }
  if (rotation.x < -89.0f) {
    rotation.x = -89.0f;
  }

  vec3 newFront;
  newFront.x = cos(radians(rotation.x)) * cos(radians(rotation.y));
  newFront.y = sin(radians(rotation.x));
  newFront.z = cos(radians(rotation.x)) * sin(radians(rotation.y));
  forward = normalize(newFront);
  right = normalize(cross(forward, up));
}

void Camera::ChangeZoom(float yoffset) {
  fov -= yoffset;
  if (fov <= 1.0f) {
    fov = 1.0f;
  }
  if (fov >= 60.0f) {
    fov = 60.0f;
  }
}