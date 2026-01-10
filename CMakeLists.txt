cmake_minimum_required(VERSION 3.10)
project(PacManX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect all source files
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.hpp")

# Create executable
add_executable(pacmanx ${SOURCES} ${HEADERS})

# Platform-specific configuration
if(EMSCRIPTEN)
    message(STATUS "Building for WebAssembly with Emscripten")

    # Emscripten-specific flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -s USE_GLUT=1 -s LEGACY_GL_EMULATION=1")

    # Set output to HTML
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    # Emscripten linker flags
    set_target_properties(pacmanx PROPERTIES LINK_FLAGS "\
        -s USE_GLUT=1 \
        -s LEGACY_GL_EMULATION=1 \
        -s GL_UNSAFE_OPTS=0 \
        -s ASSERTIONS=1 \
        -s ALLOW_MEMORY_GROWTH=1 \
        -s TOTAL_MEMORY=134217728 \
        --preload-file ${CMAKE_SOURCE_DIR}/texture@/texture \
        -s EXPORTED_FUNCTIONS='[\"_main\"]' \
        -s EXPORTED_RUNTIME_METHODS='[\"ccall\",\"cwrap\"]' \
        -O3 \
    ")

    # Link OpenGL/GLUT (handled by Emscripten)
    target_link_libraries(pacmanx)

else()
    # Native build (Linux/Mac/Windows)
    if(APPLE)
        # macOS-specific configuration
        target_link_libraries(pacmanx "-framework GLUT" "-framework OpenGL")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
    else()
        # Linux/Windows configuration
        find_package(OpenGL REQUIRED)
        find_package(GLUT REQUIRED)

        include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
        target_link_libraries(pacmanx ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} GL GLU glut pthread)
    endif()

    # Optimization for release builds
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()
