# Pengine 3D

OpenGL pipeline code based on [learnopengl.com](https://learnopengl.com/), The Cherno's [YouTube](https://www.youtube.com/user/TheChernoProject) tutorial series, and [opengl-tutorial.org](https://www.opengl-tutorial.org/).

Uses [Tinyobjloader](https://github.com/tinyobjloader/tinyobjloader) for OBJ file loading and handling.

Uses [Eigen3](https://eigen.tuxfamily.org/index.php?title=Main_Page) in conjunction with GLM to handle math. Planning to eventually retire GLM completely.


### TODO 
- Working on integrating collision detection.  
- Replace GLM functions and implement MVP pipeline from scratch.
- Refactor scene design to decouple any direct uses to OpenGL commands.