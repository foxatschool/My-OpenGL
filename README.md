Software Renderer (C++ / OpenGL)
Introduction

This project is a custom C++ software renderer built on top of OpenGL. It implements a programmable rendering pipeline with support for vertex and fragment shaders, multiple lighting models, and real-time post-processing effects. Designed as an educational and experimental graphics engine, the renderer showcases how modern GPU-style features can be emulated or extended in a custom environment.

The project uses SDL2 for window/context management and glm for math utilities.

Features

Custom Rendering Pipeline

Vertex processing, rasterization, and fragment shading.

Programmable shader stages.

Lighting Models

Gouraud shading (per-vertex lighting).

Phong shading (per-fragment lighting).

Post-Processing Effects

Configurable framebuffer passes.

Placeholder for bloom, grayscale, or custom filters.

OpenGL Integration

Hardware-accelerated display.

Optional debugging utilities.

Additional Capabilities

SDL2 input handling.

glm-based vector/matrix math.

Modular architecture for adding new shaders or pipeline stages.

Installation
Prerequisites

Ensure that the following dependencies are installed on your system:

C++17 or later

CMake (recommended)

OpenGL

SDL2

glm

Build Instructions
git clone https://github.com/yourusername/your-repo-name.git
cd your-repo-name
mkdir build && cd build
cmake ..
make

Running
./SoftwareRenderer

Usage
Command-Line Options (if applicable)
--width <value>       Set window width
--height <value>      Set window height
--shader <name>       Choose a shader program

In-App Controls

W/A/S/D — Move camera

Mouse — Look around

Esc — Exit

(Customize this section based on your actual controls.)

Technical Details
Rendering Pipeline

Vertex Shader Stage:

Applies model, view, and projection transforms.

Computes normals, view directions, and light vectors.

Rasterization:

Custom triangle rasterizer.

Perspective-correct interpolation.

Fragment Shader Stage:

Implements lighting equations.

Supports material parameters and configurable shading models.

Lighting

Gouraud: Lighting computed per vertex and interpolated.

Phong: Normals interpolated and lighting calculated per pixel.

Post-Processing

Rendered scenes are passed to a fullscreen quad for optional effects:

Custom fragment passes.

Easily extensible pipeline.

Attribution

This project uses the following open-source libraries:

SDL2
 — Windowing/input subsystem

glm
 — Mathematics library for graphics

Optionally: any models, textures, or sample assets used (add at your discretion)

Conclusion

This renderer demonstrates how a modern-style graphics pipeline can be built from scratch using C++ and lightweight library support. It is intended as a learning tool and a flexible base for experimenting with shader techniques, lighting models, and custom rendering logic.

Feel free to fork, contribute, or open issues for new features or improvements!
