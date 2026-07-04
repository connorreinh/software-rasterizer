#pragma once

#include <string>

#include "math.h"

struct RenderConfig {
  std::string input = "assets/mesh.obj";
  std::string output = "output.png";
  int width = 1280;
  int height = 720;
  Vec3 camera_pos = Vec3(0.0f, 1.0f, 5.0f);
  Vec3 camera_target = Vec3(0.0f, 0.0f, 0.0f);
  float fov = 60.0f;  // vertical field of view, in degrees
};

// Builds the CLI11 app, parses argv, and returns the filled config. On --help
// or a parse/validation error, prints via CLI11 and exits (0 / non-zero)
// directly.
RenderConfig parse_args(int argc, char **argv);
