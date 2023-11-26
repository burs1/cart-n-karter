# Add subdirectory
add_subdirectory(graphics)
add_subdirectory(gameplay)

# Add library
add_library(Modules null.cpp)

# Link libraries
target_link_libraries(
  Modules
  PUBLIC Graphics
  PUBLIC Gameplay
)
