#include <cassert>
#include "texture.h"

namespace ray_tracer {

Texture::Texture(int w, int h): w_(w), h_(h), data_(w * h, Color{1, 1, 0}) {
}

void Texture::Set(int x, int y, Color c) {
  assert(0 <= x && x < w_);
  assert(0 <= y && y < h_);
  auto idx = y * w_ + x;
  assert(idx < data_.size());
  data_[idx] = c;
}

Color Texture::Get(int x, int y) const {
  assert(0 <= x && x < w_);
  assert(0 <= y && y < h_);
  auto idx = y * w_ + x;
  assert(idx < data_.size());
  return data_[idx];
}

}