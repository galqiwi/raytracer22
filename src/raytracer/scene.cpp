#include "scene.h"
#include "ray.h"
#include "color.hpp"

namespace ray_tracer {

Color Scene::Trace(Ray r) {
  Color blue =  {0, 0, 1};
  Color red = {1, 0, 0};
  auto intersection = spheres.FindIntersection(r);
  if (!intersection) {
    double t = (r.direction.y + 1) / 2;
    return red * t + blue * (1 - t);
//    return {0.5, 0.5, 0.5};
  }
  return spheres.GetColor(r, *intersection);



}

}
