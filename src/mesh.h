#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include "math.h"

class Mesh {
 public:
  struct Vertex {
    Vec3 position;
    Vec3 normal;
    Vec2 uv;

    Vertex(Vec3 position, Vec3 normal, Vec2 uv)
        : position(position), normal(normal), uv(uv) {}
  };

  Mesh() = default;

  size_t vertex_count() const { return vertices_.size(); }

  Vertex vertex(size_t index) const { return vertices_[index]; }

  size_t face_count() const { return faces_.size(); }

  std::array<size_t, 3> face(size_t index) const { return faces_[index]; }

  void load_from_obj(const std::string &filename);

 private:
  std::vector<Vertex> vertices_;
  std::vector<std::array<size_t, 3>> faces_;
};
