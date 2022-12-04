#include <vector>
#include "cubemap.h"

#include "../color.hpp"

namespace ray_tracer {

Cubemap::Cubemap(ObjectId id, CubemapTextures /*textures*/): id_(id) {
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

const auto kNCubeSizes = 6;

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
    Color blue =  {0, 0, 1};
    Color red = {1, 0, 0};

    std::vector<Color> colors = {
        {0.8, 0.2, 0.2},
        {0.2, 0.8, 0.2},
        {0.2, 0.2, 0.8},
        {0.8, 0.8, 0.2},
        {0.8, 0.2, 0.8},
        {0.2, 0.8, 0.8},
    };

    Color output_color;
    double max_product = 0;
    for (int i = 0; i < kNCubeSizes; ++i) {
      auto product = kCubemapSidePositions[i].to_direction * r.direction;
      if (max_product < product) {
        max_product = product;
        output_color = colors[i];
        auto t = r.direction * kCubemapSidePositions[i].top_direction;
        t = (t + 1) / 2;
        output_color = output_color * t;
      }
    }
    return output_color;
//    double t = (r.direction.y + 1) / 2;
//    return red * t + blue * (1 - t);
}

}
