#pragma once

#include "vector_3d.hpp"

namespace ray_tracer {

struct Ray {
  // direction value should be normalized
  Vector3D from, direction;
  ObjectId source = CAMERA;
};

}
