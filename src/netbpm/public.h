#pragma once

#include <memory>

namespace net_bpm_image {

struct Color;

struct INetBpmImage;
using INetBpmImagePtr = std::shared_ptr<INetBpmImage>;

}