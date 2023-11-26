# Variables
set(SOURCE_FILES src/entity.cpp src/scene.cpp)
set(INCLUDE_DIRS . include ../graphics)

# Add library
add_library(Gameplay ${SOURCE_FILES})

# Include directories
target_include_directories(Gameplay PUBLIC ${INCLUDE_DIRS})

# Link libraries
target_link_libraries(
  Gameplay
  PUBLIC Graphics
)
