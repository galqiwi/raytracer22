#pragma once

#include <cstdint>

namespace ray_tracer {

struct Vector3D;

struct Ray;

class Scene;

struct Color;

using ObjectId = int64_t;
const ObjectId CAMERA = -1;

}
