#include "scene.h"
#include "ray.h"
#include "color.hpp"

namespace ray_tracer {

Color Scene::Trace(Ray r, ObjectId ignore) {
  Color blue =  {0, 0, 1};
  Color red = {1, 0, 0};
  auto t = (r.to.y + 1) / 2;
  return red * t + blue * (1 - t);
}

}
