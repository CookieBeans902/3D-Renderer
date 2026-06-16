# 3D Renderer

A custom 3D renderer built in C++ using modern OpenGL. This project follows the foundational concepts from [LearnOpenGL.com](https://learnopengl.com/), providing a robust architecture for rendering 3D graphics, handling textures, and managing shaders.


## Features

Based on the "Getting Started" section of LearnOpenGL, this project currently implements:
* **Core Profile OpenGL:** Built using modern OpenGL practices (VAOs, VBOs, IBOs).
* **Shader Management:** Custom `Shader` class to parse, compile, and link vertex and fragment shaders dynamically.
* **Texturing:** Support for loading and applying multiple 2D textures (using `stb_image`).
* **Transformations:** Matrix math implementation for rotating, scaling, and translating objects in 3D space.
* **Coordinate Systems:** Full implementation of Model, View, and Projection matrices to simulate a realistic 3D world.
* **Camera System:** A navigable 3D camera to move around the scene.

## Architecture & Abstractions

Instead of writing raw OpenGL calls in a single file, the project abstracts OpenGL concepts into manageable C++ classes:
* `VertexArray` & `VertexBuffer`: Manages geometry data and memory layout.
* `IndexBuffer`: Efficient rendering using element buffer objects.
* `Shader`: Handles compilation and uniform variable uploads.
* `Texture`: Loads image files (JPG, PNG) and generates OpenGL texture objects.
* `Renderer`: Encapsulates the draw calls and screen clearing.

## Dependencies

The project uses the following libraries:
* **[GLFW](https://www.glfw.org/):** For creating windows, contexts, and handling input.
* **[GLEW](https://glew.sourceforge.net/):** OpenGL Extension Wrangler Library to load OpenGL functions.
* **[stb_image](https://github.com/nothings/stb):** A single-header image loading library used for textures.

## Getting Started

### Prerequisites
* A C++ compiler that supports **C++20**.
* **CMake** (version 3.8 or higher).
* OpenGL graphics drivers.

### Building the Project

This project uses CMake for its build system. The `CMakeLists.txt` automatically passes the root directory to the source code so shaders and textures are found regardless of where you run the executable.

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/cookiebeans902/3d-renderer.git](https://github.com/cookiebeans902/3d-renderer.git]
   cd 3d-renderer
   ```
2. **Generate build files using CMake:**
   ```bash
	  mkdir build
	  cd build
	  cmake ..
   ```
3. **Build the executable:**
   ```bash
	  cmake --build .
    ```
3. **Run the executable:**
   ```bash
	  ./Renderer
    ```

### Directory Structure

   ```
   3D-Renderer/
├── CMakeLists.txt         # Project build configuration
├── dependencies/          # Static libraries and includes (GLFW, GLEW)
├── res/                   # Application resources
│   ├── shaders/           # .shader files (e.g., basic.shader)
│   └── textures/          # Image files (e.g., container.jpg, random.png)
└── src/                   # C++ Source code
    ├── application.cpp    # Main application loop and window setup
    ├── renderer.cpp       # Rendering abstraction logic
    ├── external/          # Third-party source files (stb_image)
    └── ...                # Core component classes (Shader, Texture, Buffers)
```
## Gallery


<div align="center">
  <img src="docs/assets/screenshot_1.png" alt="Basic Setup & Textures" width="400"/>
  <img src="docs/assets/screenshot_2.png" alt="Transformations & Coordinate Systems" width="400"/>
  <br/>
  <img src="docs/assets/screenshot_3.png" alt="Camera Movement" width="600"/>
</div>


### Acknowledgments
**LearnOpenGL** - An incredible resource for learning computer graphics.

**The Cherno (OpenGL Series)** - Great architectural inspiration for abstracting OpenGL in C++.