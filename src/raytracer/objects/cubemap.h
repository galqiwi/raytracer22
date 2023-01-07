#pragma once

#include "public.h"
#include "hittable.h"

#include "../texture.h"

namespace ray_tracer {

struct CubemapTextures {
  Texture front, right, back, left, top, bottom;
};

struct Cubemap
    : public IHittable {
 public:
  Cubemap() = default; // TODO: delete
  Cubemap(ObjectId id, CubemapTextures textures);

  std::optional<Intersection> FindIntersection(Ray r) const override;
  Color GetColor(Ray r, Intersection intersection) const override;
 private:
  ObjectId id_;
  CubemapTextures textures_;
};

}

