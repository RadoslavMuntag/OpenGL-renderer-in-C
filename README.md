# OpenGL Renderer (C)

This repository contains a minimal OpenGL renderer written in C.  
It demonstrates the fundamentals of modern OpenGL rendering, including shader management, vertex buffering, and real-time drawing.

## Features

- Written in pure C with minimal dependencies  
- Basic shader compilation and linking  
- Vertex buffer and index buffer management  
- Simple render loop with real-time frame updates  
- Easily extendable for learning or prototyping

## Requirements

- OpenGL 3.3+  
- GLFW or SDL2 (for context and input)  
- CMake (for building)

## Building

```bash
git clone https://github.com/<your-username>/<your-repo>.git
cd <your-repo>
mkdir build && cd build
cmake ..
make
