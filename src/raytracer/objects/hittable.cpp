#include "hittable.h"

namespace ray_tracer {

std::optional<Intersection> GetCloserOne(std::optional<Intersection> first,
                                         std::optional<Intersection> second) {
  if (!first && !second) {
    return std::nullopt;
  }

  if (!first) {
    return second;
  }

  if (!second) {
    return first;
  }

  if (first->distance < second->distance) {
    return first;
  } else {
    return second;
  }
}

}