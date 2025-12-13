cmake_minimum_required(VERSION 3.10)
project(PlatformerGame)
set(PROJECT_VERSION "0.1.0-pre-alpha")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

# Includes and libs directories
include_directories(${CMAKE_SOURCE_DIR}/src/include)

# Source files (src + root)
file(GLOB SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# Create executable named "game"
add_executable(game ${SRC_FILES})

# Linking for MinGW + SDL3
target_link_libraries(game PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    -mwindows
)

# Auto-copy DLLs to build folder for quick testing
add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/pack_dlls/SDL3.dll"
    "${CMAKE_SOURCE_DIR}/pack_dlls/libwinpthread-1.dll"
    "${CMAKE_SOURCE_DIR}/pack_dlls/SDL3_image.dll"
    $<TARGET_FILE_DIR:game>
)

# Installation configuration (files for the final folder)
install(TARGETS game DESTINATION .)
install(FILES "${CMAKE_SOURCE_DIR}/pack_dlls/SDL3.dll" DESTINATION .)
install(FILES "${CMAKE_SOURCE_DIR}/pack_dlls/libwinpthread-1.dll" DESTINATION .)
install(FILES "${CMAKE_SOURCE_DIR}/pack_dlls/SDL3_image.dll" DESTINATION .)

# Auto-generate .ZIP package
set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}-v${PROJECT_VERSION}")
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-v${PROJECT_VERSION}")
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_SOURCE_DIR})
include(CPack)