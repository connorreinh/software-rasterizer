#include "framebuffer.h"

#include <algorithm>
#include <cstdint>
#include <string>

#include "stb_image_write.h"

static inline uint8_t float_to_u8(float c) {
  return static_cast<uint8_t>(std::clamp(c * 255.0f, 0.0f, 255.0f));
}

bool Framebuffer::save(const std::string &filename) const {
  std::vector<uint8_t> out(width_ * height_ * 3);
  for (size_t i = 0; i < width_ * height_; ++i) {
    Vec3 color = colors_[i];
    out[i * 3 + 0] = float_to_u8(color.x);
    out[i * 3 + 1] = float_to_u8(color.y);
    out[i * 3 + 2] = float_to_u8(color.z);
  }
  return stbi_write_png(filename.c_str(), width_, height_, 3, out.data(),
                        width_ * 3);
}
