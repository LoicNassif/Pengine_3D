cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(OpenGLExample)

macro(configure_msvc_runtime)
  if(MSVC)

    # Default to dynamically-linked runtime.
    if("${MSVC_RUNTIME}" STREQUAL "")
      set(MSVC_RUNTIME "dynamic")
    endif()

    # Set compiler options.
    set(variables
      CMAKE_C_FLAGS_DEBUG
      CMAKE_C_FLAGS_MINSIZEREL
      CMAKE_C_FLAGS_RELEASE
      CMAKE_C_FLAGS_RELWITHDEBINFO
      CMAKE_CXX_FLAGS_DEBUG
      CMAKE_CXX_FLAGS_MINSIZEREL
      CMAKE_CXX_FLAGS_RELEASE
      CMAKE_CXX_FLAGS_RELWITHDEBINFO
    )
    if(${MSVC_RUNTIME} STREQUAL "static")
      message(STATUS
        "MSVC -> forcing use of statically-linked runtime."
      )
      foreach(variable ${variables})
        if(${variable} MATCHES "/MD")
          string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
        endif()
      endforeach()
    else()
      message(STATUS
        "MSVC -> forcing use of dynamically-linked runtime."
      )
      foreach(variable ${variables})
        if(${variable} MATCHES "/MT")
          string(REGEX REPLACE "/MT" "/MD" ${variable} "${${variable}}")
        endif()
      endforeach()
    endif()
  endif()
endmacro()

configure_msvc_runtime()
set(variables
  CMAKE_C_FLAGS_DEBUG
  CMAKE_C_FLAGS_MINSIZEREL
  CMAKE_C_FLAGS_RELEASE
  CMAKE_C_FLAGS_RELWITHDEBINFO
  CMAKE_CXX_FLAGS_DEBUG
  CMAKE_CXX_FLAGS_MINSIZEREL
  CMAKE_CXX_FLAGS_RELEASE
  CMAKE_CXX_FLAGS_RELWITHDEBINFO
)
message(STATUS "Initial build flags:")
foreach(variable ${variables})
  message(STATUS "  '${variable}': ${${variable}}")
endforeach()
message(STATUS "")

# Add source files
file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/*.c
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/tests/*.c
    ${CMAKE_SOURCE_DIR}/src/tests/*.cpp
    ${CMAKE_SOURCE_DIR}/thirdparty/imgui/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_SOURCE_DIR}/src/*.h
    ${CMAKE_SOURCE_DIR}/src/*.hpp
    ${CMAKE_SOURCE_DIR}/src/tests/*.h
    ${CMAKE_SOURCE_DIR}/src/tests/*.hpp
    ${CMAKE_SOURCE_DIR}/thirdparty/imgui/*.hpp)

# Add .lib files
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Configure assets header file
configure_file(src/helpers/RootDir.h.in src/helpers/RootDir.h)
include_directories(${CMAKE_BINARY_DIR}/src)

# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# OpenGL
find_package(OpenGL REQUIRED)

# GLM
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

# GLFW
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

# STB_IMAGE
add_library(STB_IMAGE "thirdparty/stb_image.cpp")

# GLAD
add_library(GLAD "thirdparty/glad.c")

# Put all libs into a variable
set(LIBS glfw3 ${OPENGL_LIBRARIES} STB_IMAGE GLAD ${OPENGL_gl_LIBRARY} ${CMAKE_DL_LIBS})

# Define the include DIRs
include_directories(
    ${OPENGL_INCLUDE_DIRS}
    "${CMAKE_SOURCE_DIR}/thirdparty/imgui"
    "${CMAKE_SOURCE_DIR}/thirdparty/glm"
    "${CMAKE_SOURCE_DIR}/thirdparty/Eigen3/include/eigen3"
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/include"
)
link_directories(${OPENGL_LIBRARY_DIRS})

# Define the link libs
target_link_libraries(${PROJECT_NAME} ${LIBS})