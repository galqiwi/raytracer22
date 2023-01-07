#include <vector>
#include <assert.h>
#include <filesystem>

#include "cubemap.h"

#include "../color.hpp"

namespace ray_tracer {

Cubemap::Cubemap(ObjectId id, CubemapTextures textures): id_(id), textures_(textures) {
}

std::optional<Intersection> Cubemap::FindIntersection(Ray r) const {
    return Intersection{
       .with = id_,
       .distance = std::numeric_limits<double>::max(),
    };
};

struct CubemapSidePosition {
  Vector3D top_direction;
  Vector3D to_direction;
};

const auto kNCubeSides = 6;

// front, right, back, left, top, bottom
const auto kCubemapSidePositions = []() {
  std::vector<CubemapSidePosition> output;

  Vector3D top_direction = Vector3D{0, 1, 0};
  Vector3D to_direction = Vector3D{0, 0, -1};

  for (int i = 0; i < 4; i++) {
    output.push_back(CubemapSidePosition{
        .top_direction = top_direction,
        .to_direction = to_direction,
    });
    // rotating to_direction clockwise
    to_direction = to_direction % top_direction;
  }

  output.push_back(CubemapSidePosition{
      .top_direction = {0, 0, 1},
      .to_direction = {0, 1, 0},
  });

  output.push_back(CubemapSidePosition{
      .top_direction = {0, 0, -1},
      .to_direction = {0, -1, 0},
  });

  return output;
}();

Color Cubemap::GetColor(Ray r, Intersection intersection) const {
    double max_product = 0;
    int cubeSide = -1;
    for (int i = 0; i < kNCubeSides; ++i) {
      auto product = kCubemapSidePositions[i].to_direction * r.direction;
      if (max_product < product) {
        max_product = product;
        cubeSide = i;
      }
    }
    assert(cubeSide != -1);

    auto const& cubemapSidePosition = kCubemapSidePositions[cubeSide];

    const Texture* texture = nullptr;

    switch (cubeSide) {
      case 0:
        texture = &textures_.front;
        break;
      case 1:
        texture = &textures_.right;
        break;
      case 2:
        texture = &textures_.back;
        break;
      case 3:
        texture = &textures_.left;
        break;
      case 4:
        texture = &textures_.top;
        break;
      case 5:
        texture = &textures_.bottom;
        break;
      default:
        abort();
    }

    assert(texture != nullptr);

    // r.direction * cubemapSidePosition.top_direction is from -sqrt(2)/2 to sqrt(2)/2
    auto y = 0.5 - (r.direction * cubemapSidePosition.top_direction) / sqrt(2);
    auto x = 0.5 - (r.direction * (cubemapSidePosition.top_direction % cubemapSidePosition.to_direction)) / sqrt(2);

    int x_pixel = x * (texture->GetWidth() - 1);
    int y_pixel = y * (texture->GetHeight() - 1);
    x_pixel = std::max(0, x_pixel);
    y_pixel = std::max(0, y_pixel);
    x_pixel = std::min(texture->GetWidth() - 1, x_pixel);
    y_pixel = std::min(texture->GetHeight() - 1, y_pixel);

    return texture->Get(x_pixel, y_pixel);
}

}
