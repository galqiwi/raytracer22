#pragma once

#include <cstdint>
#include "public.h"

namespace ray_tracer {

using ObjectId = int64_t;
const ObjectId IgnoreNothing = -1;

class Scene {
 public:
  Color Trace(Ray r, ObjectId ignore = IgnoreNothing);
};

}