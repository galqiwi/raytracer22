#pragma once

#include "public.h"
#include "vector_3d.hpp"

namespace ray_tracer {

struct CameraConfig {
  int width;
  int height;
  double width_angle;
  double height_angle;
};

class Camera {
 public:
  Camera(CameraConfig cfg,
         Vector3D position,
         Vector3D direction,
         Vector3D direction_up);

  Ray GetRay(int x, int y);
 private:
  CameraConfig cfg_;
  Vector3D position_;
  Vector3D direction_;
  Vector3D direction_up_;
  Vector3D direction_right_;
};

}