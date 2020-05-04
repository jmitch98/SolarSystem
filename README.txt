Name: James Mitchell

A 3D solar system viewer and planet comparison application written in OpenGL

========== Build Instructions ==========

The code was written in a Fedora Linux environment, but compiles
and works in a Ubuntu 18.04 VirtualBox environment (same as the AutoGrader).

The application relies on the following dependencies:

1. SDL2 - For window viewing (sudo apt install libsdl2-dev)
2. GLEW - GL extension wrangler library for safe loading of OpenGL
  (sudo apt install libglew-dev)
3. Assimp - For Model loading (sudo apt install libassimp-dev)
4. OpenGL Mathematics - For matrix math and compatibility with OpenGL shaders
  (header only; shipped with source)
5. STB_IMAGE - For texture loading (header only; shipped with source)

To build, run the makefile in the root directory of the source code.

Note on shaders: The shaders use shader model 3.00 es (same as the slides).
They appear to work in the 18.04 VM, but if there are problems, please let me know.

========== Usage ==========

* To move pivot the camera around the center of the scene, right-click
and move the mouse

* To zoom in and out of the scene, use the mouse wheel

* To switch to the planet comparison mode, hit the TAB key

* To switch out the planet next to Earth, use the number keys

* To lower the simulation speed, hit the comma or "<" key

* To raise the simuatlion speed, hit the period or ">" key