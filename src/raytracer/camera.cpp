#include "camera.h"

#include "ray.h"

#include <assert.h>

namespace ray_tracer {

void AssertUnit(Vector3D v) {
  assert(abs2(v) < 1.1);
  assert(abs2(v) > 0.9);
}

Camera::Camera(
    ray_tracer::CameraConfig cfg,
    ray_tracer::Vector3D position,
    ray_tracer::Vector3D direction,
    Vector3D direction_up)
    : cfg_(std::move(cfg))
      , position_(std::move(position))
      , direction_(std::move(direction))
      , direction_up_(std::move(direction_up))
      , direction_right_(direction_up_ % direction_) {
  AssertUnit(direction_);
  AssertUnit(direction_up_);
  AssertUnit(direction_right_);
  assert(cfg_.width > 0);
  assert(cfg_.height > 0);
  assert(cfg_.width_angle > 0);
  assert(cfg_.height_angle > 0);
}

Ray Camera::GetRay(int x, int y) {
  assert(0 <= x && x < cfg_.width);
  assert(0 <= y && y < cfg_.height);

  double x_rel = static_cast<double>(x) / static_cast<double>(cfg_.width - 1);
  double y_rel = static_cast<double>(y) / static_cast<double>(cfg_.height - 1);
  x_rel = (x_rel * 2 - 1);
  y_rel = -(y_rel * 2 - 1);

  double x_angle = x_rel * cfg_.width_angle / 2;
  double y_angle = y_rel * cfg_.height_angle / 2;

  return {
    .from = position_,
    .direction = sin(y_angle) * direction_up_ +
          cos(y_angle) *
              (cos(x_angle) * direction_ +
               sin(x_angle) * direction_right_)
  };
}

}
