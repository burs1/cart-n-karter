# Variables
set(SOURCE_FILES src/window.cpp src/sprite.cpp)
set(INCLUDE_DIRS . include)

# Find packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Add library
add_library(Graphics ${SOURCE_FILES})

# Include directories
target_include_directories(Graphics PUBLIC ${INCLUDE_DIRS})

# Link libraries
target_link_libraries(
  Graphics
  PUBLIC SDL2::SDL2
  PUBLIC SDL2_image::SDL2_image
)
