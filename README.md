# Pengine 3D

OpenGL pipeline code based on [learnopengl.com](https://learnopengl.com/), The Cherno's [YouTube](https://www.youtube.com/user/TheChernoProject) tutorial series, and [opengl-tutorial.org](https://www.opengl-tutorial.org/).

Uses [Tinyobjloader](https://github.com/tinyobjloader/tinyobjloader) for OBJ file loading and handling.

Uses [Eigen3](https://eigen.tuxfamily.org/index.php?title=Main_Page) in conjunction with GLM to handle math. Planning to eventually retire GLM completely.

### BUILD

Tested on Windows10 MSVC, Linux (OpenSUSE, Ubuntu) g++.

- Make a build folder at the root: `mkdir build && cd build`.
- Run cmake inside the build folder: `cmake ..`.
- Run `make` if on a Linux machine, otherwise on Windows, `msbuild PEngine.sln`.

### TODO 
- Working on integrating collision detection.  
- Replace GLM functions and implement MVP pipeline from scratch.
- Refactor scene design to decouple any direct uses to OpenGL commands.

### NOTE
Linux distros may have a problem linking due to the naming scheme of the glfw3 package. For example, in openSUSE Leap 15.3 (and I think this also happens on Ubuntu), while compiling the code you may get an error in the form of `cannot find -lglfw3`. This is because the glfw3 (yes 3) library file name is `libglfw.so`. To solve this issue, make a copy of the file and call it `libglfw3.so`. The library files can usually be found in `/usr/lib64/`. 
