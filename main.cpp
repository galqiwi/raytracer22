#include <iostream>

#include "src/netbpm/net_bpm_image.h"
#include "src/raytracer/vector_3d.hpp"
#include "src/raytracer/scene.h"
#include "src/raytracer/color.hpp"
#include "src/raytracer/camera.h"
#include "src/raytracer/ray.h"
#include "src/raytracer/objects/sphere.h"
#include "helpers.h"

int main() {
  int scale = 10;
  int w = 192 * scale, h = 108 * scale;

  ray_tracer::Scene scene;

  std::vector<ray_tracer::Sphere> spheres;
  spheres.push_back(ray_tracer::Sphere(0,ray_tracer::Vector3D{-1, 0, -10},1, &scene));
  spheres.push_back(ray_tracer::Sphere(1,ray_tracer::Vector3D{1, 0, -10},1, &scene));

  scene.spheres = ray_tracer::ObjectSet<ray_tracer::Sphere>(std::move(spheres));

  scene.sky = ray_tracer::Cubemap(2, ReadCubemapTexturesFromDir("cubemap"));

  ray_tracer::Camera camera(
      {
          .width = w,
          .height = h,
          .width_angle = 1 * 192. / 108.,
//          .width_angle = M_PI,
          .height_angle = 1,
      }
      , {0, 0, 0}, {0, 0, -1}, {0, 1, 0});

  std::cout << "loaded textures, rendering..." << std::endl;

  auto output = net_bpm_image::MakePPMImage(w, h);

  for (int x = 0; x < w; ++x) {
    for (int y = 0; y < h; ++y) {
      auto pixel_color = scene.Trace(camera.GetRay(x, y));
      output->Set(x, y, RenderColor(pixel_color));
    }
  }

  output->Save("output.ppm");
}
