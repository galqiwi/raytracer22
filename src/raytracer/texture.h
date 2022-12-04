#pragma once

#include <vector>

#include "public.h"
#include "color.hpp"

namespace ray_tracer {

class Texture {
 public:
  Texture() = default;
  Texture(int w, int h);

  void Set(int x, int y, Color c);
  Color Get(int x, int y) const;
 private:
  int w_, h_;
  std::vector<Color> data_;
};
}