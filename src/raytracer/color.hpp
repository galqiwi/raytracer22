#pragma once

namespace ray_tracer {

struct Color {
  double r, g, b;
};

inline Color operator*(Color c, double to) {
  return {c.r * to, c.g * to, c.b * to};
}

inline Color operator*(double to, Color c) {
  return c * to;
}

inline Color operator+(Color c1, Color c2) {
  return {c1.r + c2.r, c1.g + c2.g, c1.b + c2.b};
}

inline Color operator/(Color c, double to) {
  return {c.r / to, c.g / to, c.b / to};
}

}
