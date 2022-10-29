#include "vector_3d.hpp"

namespace ray_tracer {

std::ostream& operator<<(std::ostream& out, Vector3D v) {
  out << v.x << " " << v.y << " " << v.z;
  return out;
}

}
