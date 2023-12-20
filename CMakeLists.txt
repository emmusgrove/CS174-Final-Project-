project(tinygl-cpp)
cmake_minimum_required(VERSION 3.14.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if (WIN32) # Include win64 platforms

  find_package(OpenGL REQUIRED)
  find_library(GLEW NAMES glew32s PATHS external/lib/x64)
  find_library(GLFW NAMES glfw3 PATHS external/lib)

  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_FLAGS 
     "/wd4018 /wd4244 /wd4305 
     /D_CRT_SECURE_NO_WARNINGS 
     /D_CRT_NONSTDC_NO_DEPRECATE 
     /D NOMINMAX /DGLEW_STATIC
     /EHsc")
  set(CMAKE_EXE_LINKER_FLAGS "/NODEFAULTLIB:\"MSVCRT\" /NODEFAULTLIB:\"LIBCMT\"")
  set(CORE ${GLEW} ${GLFW} opengl32.lib)
  include_directories(external/include)
  link_directories(external/lib)

elseif (APPLE)

  set(CMAKE_MACOSX_RPATH 1)
  set(CMAKE_CXX_FLAGS "-Wall -Wno-deprecated-declarations -Wno-reorder-ctor -Wno-unused-function -Wno-unused-variable -g -stdlib=libc++ -std=c++14")
  find_library(GL_LIB OpenGL)
  find_library(GLFW glfw)
  add_definitions(-DAPPLE)

  include_directories(/System/Library/Frameworks /usr/local/include)
  set(CORE ${GLFW} ${GL_LIB})

elseif (UNIX)

  set(CMAKE_CXX_FLAGS "-Wall -g -std=c++14 -Wno-comment -Wno-sign-compare -Wno-reorder -Wno-unused-function")
  FIND_PACKAGE(OpenGL REQUIRED) 
  FIND_PACKAGE(GLEW REQUIRED)

  set(LIBRARY_DIRS
    /usr/X11R6/lib
    /usr/local/lib
    )

  add_definitions(-DUNIX)
  set(CORE GLEW glfw GL X11)

endif()

message("CMAKE_HOME_DIRECTORY: ${CMAKE_HOME_DIRECTORY}")

include_directories(.)
add_executable(driver driver.cpp simulation.cpp simulation.h animal.cpp animal.h randutils.h randutils.cpp shapes.cpp shapes.h simplecanvas/simplecanvas.h simplecanvas/simplecanvas.cpp)
target_link_libraries(driver ${CORE})
