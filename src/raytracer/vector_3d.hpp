#pragma once

#include "public.h"
#include <math.h>
#include <iostream>

namespace ray_tracer {

struct Vector3D {
  Vector3D() = default;
  Vector3D(double x, double y, double z) : x(x), y(y), z(z) {
  }
  double x = 0, y = 0, z = 0;
};

inline Vector3D operator+(Vector3D a, Vector3D b) {
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}

inline Vector3D operator-(Vector3D a, Vector3D b) {
  return {a.x - b.x, a.y - b.y, a.z - b.z};
}

inline double operator*(Vector3D a, Vector3D b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vector3D operator%(Vector3D a, Vector3D b) {
  return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

inline Vector3D operator*(Vector3D a, double to) {
  return {a.x * to, a.y * to, a.z * to};
}

inline Vector3D operator*(double to, Vector3D a) {
  return a * to;
}

inline Vector3D operator/(Vector3D a, double to) {
  return {a.x / to, a.y / to, a.z / to};
}

inline double abs2(Vector3D v) {
  return v * v;
}

inline double abs(Vector3D v) {
  return hypot(v.x, v.y, v.z);
}

std::ostream& operator<<(std::ostream& out, Vector3D v);

}
