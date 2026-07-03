#pragma once

#include <cstdint>
#include <limits>
#include <string>
#include <vector>

#include "math.h"
#include "stb_image_write.h"

class Framebuffer {
 public:
  Framebuffer(uint32_t width, uint32_t height)
      : width_(width),
        height_(height),
        colors_(width * height, Vec3(0.0f, 0.0f, 0.0f)),
        depth_(width * height, std::numeric_limits<float>::max()) {}

  void set_pixel(Vec2Int pos, Vec3 color) {
    if (pos.x < 0 || pos.x >= width_ || pos.y < 0 || pos.y >= height_) return;
    colors_[index(pos)] = color;
  }

  void save(const std::string &filename) const;

 private:
  uint32_t width_, height_;
  std::vector<Vec3> colors_;
  std::vector<float> depth_;

  uint32_t index(Vec2Int pos) const { return pos.y * width_ + pos.x; }
};
