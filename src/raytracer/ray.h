#pragma once

#include "vector_3d.hpp"

namespace ray_tracer {

struct Ray {
  // to value should be normalized
  Vector3D from, to;
};

}
