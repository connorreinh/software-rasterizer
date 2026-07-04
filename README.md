# Software Rasterizer

A simple software rasterizer that implements a simplified version of the OpenGL
rendering pipeline. It loads a triangle mesh from a Wavefront `.obj` file and
renders it to a PNG image.

## Building

Requires CMake (3.15+) and a C++17 compiler.

```sh
cmake -B build
cmake --build build
```

The executable is written to `build/rasterizer`.

## Usage

Run from the repository root so the default asset path resolves:

```sh
./build/rasterizer [options]
```

With no arguments it renders `assets/mesh.obj` to `output.png` at 1280×720.

### Options

| Flag                          | Default           | Description            |
| ----------------------------- | ----------------- | ---------------------- |
| `--input <path>`              | `assets/mesh.obj` | Input OBJ mesh         |
| `--output <path>`             | `output.png`      | Output PNG path        |
| `--width <n>`                 | `1280`            | Framebuffer width      |
| `--height <n>`                | `720`             | Framebuffer height     |
| `--camera-pos <x> <y> <z>`    | `0 1 5`           | Camera position        |
| `--camera-target <x> <y> <z>` | `0 0 0`           | Camera target          |
| `--fov <deg>`                 | `60`              | Vertical field of view |
| `-h`, `--help`                |                   | Show help and exit     |

> The camera flags (`--camera-pos`, `--camera-target`, `--fov`) are parsed and
> validated but do not yet affect the output; view and perspective support is in
> progress.

Example:

```sh
./build/rasterizer --input scene.obj --output out.png --width 1280 --height 720 \
                   --camera-pos 0 1 5 --camera-target 0 0 0 --fov 60
```
