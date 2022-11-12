#pragma once

#include "public.h"

#include "objects/sphere.h"
#include "objects/object_set.hpp"

#include <cstdint>

namespace ray_tracer {

class Scene {
 public:
  Color Trace(Ray r);

  ObjectSet<Sphere> spheres;
};

}
