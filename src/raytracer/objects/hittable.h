#pragma once

#include "../ray.h"

#include <optional>

namespace ray_tracer {

struct Intersection {
  ObjectId with;
  double distance;
};

std::optional<Intersection> GetCloserOne(std::optional<Intersection> first,
                                         std::optional<Intersection> second);

struct IHittable {
  virtual std::optional<Intersection> FindIntersection(Ray r) const = 0;
  virtual Color GetColor(Ray r, Intersection intersection) const = 0;
};

}
