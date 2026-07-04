#include "cli.h"

#include <array>
#include <cstdlib>

#include "CLI11.hpp"

RenderConfig parse_args(int argc, char **argv) {
  RenderConfig cfg;
  CLI::App app{"Software rasterizer"};

  app.add_option("--input", cfg.input, "Input OBJ mesh")
      ->check(CLI::ExistingFile);
  app.add_option("--output", cfg.output, "Output PNG path");
  app.add_option("--width", cfg.width, "Framebuffer width")
      ->check(CLI::PositiveNumber);
  app.add_option("--height", cfg.height, "Framebuffer height")
      ->check(CLI::PositiveNumber);

  // CLI11 binds each camera vector as a std::array<float, 3> of 3
  // space-separated values; we lift them into Vec3 after parsing.
  std::array<float, 3> cam_pos{0.0f, 1.0f, 5.0f};
  std::array<float, 3> cam_target{0.0f, 0.0f, 0.0f};
  app.add_option("--camera-pos", cam_pos, "Camera position: X Y Z");
  app.add_option("--camera-target", cam_target, "Camera target: X Y Z");
  app.add_option("--fov", cfg.fov, "Vertical field of view (deg)")
      ->check(CLI::Range(0.0, 180.0));

  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError &e) {
    // Handles --help (exit 0) and parse/validation errors (non-zero); prints
    // for us.
    std::exit(app.exit(e));
  }

  cfg.camera_pos = Vec3(cam_pos[0], cam_pos[1], cam_pos[2]);
  cfg.camera_target = Vec3(cam_target[0], cam_target[1], cam_target[2]);
  return cfg;
}
