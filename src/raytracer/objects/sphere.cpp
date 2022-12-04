#include "sphere.h"
#include "../color.hpp"

#include "../scene.h"

#include <cassert>

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

Color Sphere::GetColor(ray_tracer::Ray r, Intersection intersection) const {
  double distance = intersection.distance;

  auto hit = r.from + distance * r.direction;

  auto norm = (hit - center) / radius;

  assert(r.direction * norm <= 1e-3);

  auto reflection_direction = r.direction - (2 * (r.direction * norm)) * norm;

  assert(abs2(reflection_direction) < 1.05);
  assert(abs2(reflection_direction) > 0.95);

  Ray reflection = {
      .from = hit,
      .direction = reflection_direction,
      .source = id,
  };

  assert(scene);
  auto reflection_color = scene->Trace(reflection);

  return reflection_color * 1.0;// + Color{0.5, 0.5, 0.5};
}

Sphere::Sphere(ObjectId id, Vector3D center, double radius, Scene* scene)
  : id(id), center(center), radius(radius), scene(scene) {
}

}
