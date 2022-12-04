#pragma once

#include "public.h"
#include "hittable.h"

#include "../vector_3d.hpp"

#include <optional>

namespace ray_tracer {

struct Sphere
  : public IHittable {
  ObjectId id;
  Vector3D center;
  double radius;
  Scene* scene;

  Sphere() = default;

  Sphere(ObjectId id, Vector3D center, double radius, Scene* scene);

  std::optional<Intersection> FindIntersection(Ray r) const override;
  Color GetColor(Ray r, Intersection intersection) const override;
};

}
