#pragma once

#include "public.h"
#include <memory>
#include <cstddef>

namespace net_bpm_image {

struct Color {
  double r, g, b;
};

struct INetBpmImage {
  virtual void Set(int x, int y, Color c) = 0;
  virtual Color Get(int x, int y) = 0;
  virtual int Width() const = 0;
  virtual int Height() const = 0;
  virtual void Save(const std::string filename) = 0;
};

INetBpmImagePtr MakePPMImage(size_t w, size_t h);

INetBpmImagePtr MakePPMImage(const char* filename);

}