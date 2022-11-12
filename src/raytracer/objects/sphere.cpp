#include "sphere.h"

#include "../color.hpp"

namespace ray_tracer {

std::optional<Intersection> Sphere::FindIntersection(
    ray_tracer::Ray r) const {

  double proj_d = (center - r.from) * r.direction;
  if (proj_d < 0) {
    return std::nullopt;
  }

  double d = proj_d * proj_d - abs2(center - r.from) + radius * radius;

  if (d <= 0) {
    return std::nullopt;
  }

  return Intersection{
      .with = id,
      .distance = proj_d - sqrt(d),
  };
}

Color Sphere::GetColor(ray_tracer::Ray r) {
  abort();
}

Sphere::Sphere(ObjectId id, Vector3D center, double radius, Scene* scene)
  : id(id), center(center), radius(radius), scene(scene) {
}

}