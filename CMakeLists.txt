cmake_minimum_required(VERSION 3.21)
project(testing VERSION 0.1.0 LANGUAGES C CXX)

# Project configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# Dependencies
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.20
)
#FetchContent_Declare(
#    SDL3_image
#    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
#    GIT_TAG release-3.2.4
#)
#FetchContent_Declare(
#    assimp
#    GIT_REPOSITORY https://github.com/assimp/assimp.git
#    GIT_TAG v6.0.2
#)


FetchContent_MakeAvailable(SDL3)

# Executable
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

# Set the output directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Copy DLLs on Windows
if(WIN32)
    foreach(dep SDL3::SDL3)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:${dep}>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endforeach()
endif()

# copy shaders folder to bin directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders
    ${CMAKE_BINARY_DIR}/bin/shaders
)
