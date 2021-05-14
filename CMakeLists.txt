cmake_minimum_required(VERSION 3.0.0)
project(OpenGL-Experiments VERSION 0.1.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#specify C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

### libraries
# openGL
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    glfw
    glew
)

link_libraries(
    ${GLEW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    glfw
)

#source code management
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/common
        ${PROJECT_SOURCE_DIR}/src/FragmentShader
        ${PROJECT_SOURCE_DIR}/src/VertexShader
)

# file(GLOB all_SRCS
#         "${PROJECT_SOURCE_DIR}/include/*.h"
#         "${PROJECT_SOURCE_DIR}/include/*.hpp"
#         "${PROJECT_SOURCE_DIR}/src/*.cpp"
#         "${PROJECT_SOURCE_DIR}/src/*.c"
#         "${PROJECT_SOURCE_DIR}/src/common/*.cpp"
#         "${PROJECT_SOURCE_DIR}/src/common/*.c"

#         # "${PROJECT_SOURCE_DIR}/src/FragmentShader/*.glsl"
#         # "${PROJECT_SOURCE_DIR}/src/VertexShader/*.glsl"
#         )

# message( ${all_SRCS} )

add_executable(OpenGL-Experiments 
                src/main.cpp

                src/common/loadShader.cpp
                src/common/loadShader.hpp
                src/common/matrixlib.cpp
                src/common/matrixlib.hpp

                src/VertexShader/SimpleVertexShader.glsl
                src/FragmentShader/SimpleFragmentShader.glsl
)

function(trackResource target_dir target)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/${target_dir}/${target}
        ${CMAKE_CURRENT_BINARY_DIR}
        COPYONLY
        )
endfunction(do_test)

# from main.h.in converts the version here into the actual h file
configure_file(include/main.hpp.in main.hpp)
# configure_file(src/main.hpp.in main.hpp)

# expose the generated .h files to the code
target_include_directories(OpenGL-Experiments PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

# resources
trackResource(src/VertexShader SimpleVertexShader.glsl)
trackResource(src/FragmentShader SimpleFragmentShader.glsl)

### Tests
# define a function to simplify adding tests
function(do_test target arg result)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction(do_test)

do_test(OpenGL-Experiments 4 "4 is 2")
