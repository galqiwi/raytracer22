#pragma once

#include "public.h"

#include "hittable.h"

#include "../color.hpp"

#include <vector>

namespace ray_tracer {

template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

template <Derived<IHittable> T>
class ObjectSet
    : public IHittable {
 public:
  ObjectSet() = default;
  explicit ObjectSet(std::vector<T> objects) : objects_(std::move(objects)) {
  }

  std::optional<Intersection> FindIntersection(Ray r) const {
    std::optional<Intersection> output = std::nullopt;

    for (const auto& object: objects_) {
      if (object.id == r.source) {
        continue;
      }
      auto intersection = object.FindIntersection(r);
      if (!output) {
        output = intersection;
        continue;
      }
      if (!intersection) {
        continue;
      }
      if (intersection->distance < output->distance) {
        output = intersection;
      }
    }

    return output;
  }

  Color GetColor(Ray r, Intersection intersection) const {
    for (const auto& object: objects_) {
      if (object.id == intersection.with) {
        return object.GetColor(r, intersection);
      }
    }
    abort();
  }

 private:
  std::vector<T> objects_;
};

}