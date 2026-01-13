cmake_minimum_required(VERSION 3.16)
project(pacmanx LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Release optimization flags
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

# Collect source and header files
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Platform-specific configuration
if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=10.7 -Wno-deprecated-declarations")
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework GLUT"
        "-framework OpenGL"
    )
else()
    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        OpenGL::GL
        OpenGL::GLU
        GLUT::GLUT
    )
endif()

# Set output directory for build artifacts
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
