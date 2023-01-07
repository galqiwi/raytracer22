#pragma once

#include <filesystem>
#include "src/netbpm/net_bpm_image.h"
#include "src/raytracer/objects/cubemap.h"

inline net_bpm_image::Color RenderColor(ray_tracer::Color c) {
  return {c.r, c.g, c.b};
}

ray_tracer::CubemapTextures ReadCubemapTexturesFromDir(std::string dirname);