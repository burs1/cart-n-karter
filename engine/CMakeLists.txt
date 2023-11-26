# Variables
set(SOURCE_FILES src/app.cpp)
set(INCLUDE_DIRS include)

# Add subdirectories
add_subdirectory(modules)

# Add library
add_library(Securus ${SOURCE_FILES})

# Include directories
target_include_directories(Securus PUBLIC ${INCLUDE_DIRS})

# Link libraries
target_link_libraries(
  Securus
  PUBLIC Modules
)
