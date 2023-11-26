cmake_minimum_required(VERSION 3.27)

# Project info
project(cart-n-karter VERSION 1.0.0 LANGUAGES CXX)

# Settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

# Copy assets
file(COPY assets DESTINATION .)

# Add subdirectories
add_subdirectory(engine)

# Include directories
include_directories(engine)

# Add executable
add_executable(${PROJECT_NAME} main.cpp)

# Link libraries
target_link_libraries(
  ${PROJECT_NAME}
  Securus
)
