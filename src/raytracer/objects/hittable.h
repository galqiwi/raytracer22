#pragma once

#include "../ray.h"

#include <optional>

namespace ray_tracer {

struct Intersection {
  ObjectId with;
  double distance;
};

struct IHittable {
  virtual std::optional<Intersection> FindIntersection(Ray r) const = 0;
  virtual Color GetColor(Ray r) = 0;
};

}
