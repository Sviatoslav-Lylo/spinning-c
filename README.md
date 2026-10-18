# Spinning Donut and Trident

A small C project that renders two animated ASCII-style terminal graphics in real time: a rotating 3D donut and a spinning trident. Both are built with pure C, math-based projection, lighting, and ANSI terminal control.

![Spinning donut animation](spinning_donut.gif)

![Spinning trident animation](spinning_trident.gif)

## Features

- Real-time 3D ASCII rendering in the terminal
- Perspective projection and depth buffering
- Simple lighting/shading for surface brightness
- Smooth rotation animation without external libraries
- Two standalone demos: a classic donut and a 3D trident

## How the rendering works

Each frame, the programs sample 3D points on the shape, rotate them, project them onto a 2D character grid, and keep the nearest visible point at each grid cell. The donut is sampled parametrically as a torus; the trident starts with a 2D `#` mask and extrudes it through a small depth to make a solid shape.

Both shapes rotate around the **x-axis** by angle `A`, then around the **z-axis** by angle `B`. For a point `(x, y, z)`, the rotations are applied in sequence:

```text
After x rotation:                 After z rotation:
x1 = x                            x2 = x1 cos(B) - y1 sin(B)
y1 = y cos(A) - z sin(A)          y2 = x1 sin(B) + y1 cos(B)
z1 = y sin(A) + z cos(A)          z2 = z1
```

These are the standard 3D rotation matrices for the x- and z-axes. The same rotations are applied to surface normals so the lighting follows the shape. A dot product with the light direction determines each point's brightness, which is mapped to an ASCII character.

For projection, the renderer uses reciprocal depth `D = 1 / (z2 + cameraDist)` to scale the rotated x and y coordinates into terminal columns and rows. A z-buffer stores the largest `D` at each cell, keeping nearer samples in front. The angles `A` and `B` increase after each frame to animate the rotation.

## Project files

- `donut.c` — classic rotating donut animation
- `trident.c` — spinning trident animation
- `spinning_donut.gif` / `spinning_trident.gif` — recorded GIF demos

## Requirements

- A C compiler such as GCC, MinGW-w64, or MSYS2 on Windows
- `math.h` support (`-lm` linker flag on GCC/MinGW)
- A terminal that supports ANSI escape sequences

## Build instructions

From the project directory, compile the programs with:

```bash
gcc donut.c -lm -o donut.exe
gcc trident.c -lm -o trident.exe
```

If you are using MinGW, the same commands usually work directly from the terminal.

## Run the demos

```bash
./donut.exe
./trident.exe
```

On Windows, you can also run the generated `.exe` files directly from Command Prompt or PowerShell.

## Notes

These animations are intentionally lightweight and terminal-based. They use ASCII characters and runtime rendering rather than a graphical engine, which makes them easy to build and run on nearly any terminal.

## License

This project is provided as-is for educational and entertainment purposes.
