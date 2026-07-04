#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "cli.h"
#include "framebuffer.h"
#include "math.h"
#include "mesh.h"

void draw_line(Framebuffer &framebuffer, Vec2Int p0, Vec2Int p1, Vec3 color) {
  int32_t dx = std::abs(p1.x - p0.x);
  int32_t dy = std::abs(p1.y - p0.y);
  int32_t sx = p0.x < p1.x ? 1 : -1;
  int32_t sy = p0.y < p1.y ? 1 : -1;
  int32_t err = dx - dy;
  while (true) {
    framebuffer.set_pixel(p0, color);
    if (p0.x == p1.x && p0.y == p1.y) break;
    int32_t e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      p0.x += sx;
    }
    if (e2 < dx) {
      err += dx;
      p0.y += sy;
    }
  }
}

int main(int argc, char **argv) {
  RenderConfig cfg = parse_args(argc, argv);

  try {
    Framebuffer framebuffer(cfg.width, cfg.height);
    Mesh mesh;
    mesh.load_from_obj(cfg.input);
    for (size_t i = 0; i < mesh.face_count(); ++i) {
      auto face = mesh.face(i);
      for (size_t j = 0; j < 3; ++j) {
        Vec3 v0 = mesh.vertex(face[j]).position;
        Vec3 v1 = mesh.vertex(face[(j + 1) % 3]).position;
        Vec2Int p0(
            static_cast<int32_t>(v0.x * cfg.width / 2 + cfg.width / 2),
            static_cast<int32_t>(-v0.y * cfg.height / 2 + cfg.height / 2));
        Vec2Int p1(
            static_cast<int32_t>(v1.x * cfg.width / 2 + cfg.width / 2),
            static_cast<int32_t>(-v1.y * cfg.height / 2 + cfg.height / 2));
        draw_line(framebuffer, p0, p1, Vec3(1.0f, 1.0f, 1.0f));
      }
    }

    if (!framebuffer.save(cfg.output)) {
      throw std::runtime_error("failed to write output: " + cfg.output);
    }
    std::cout << "Rendered " << cfg.input << " -> " << cfg.output << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
