#include <cassert>
#include "scene.h"
#include "ray.h"
#include "color.hpp"

namespace ray_tracer {

Color Scene::Trace(Ray r) {
  auto spheres_intersection = spheres.FindIntersection(r);
  auto sky_intersection = sky.FindIntersection(r);
  assert(sky_intersection);

  if (spheres_intersection) {
    return spheres.GetColor(r, *spheres_intersection);
  }

  return sky.GetColor(r, *sky_intersection);
}

}
