file(GLOB_RECURSE OAK_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB_RECURSE OAK_PRIVATE_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

file(GLOB_RECURSE OAK_PUBLIC_HEADERS CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/include/*.hpp"
)

list(REMOVE_ITEM OAK_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/oak.cpp")

add_library(oak_lib STATIC
    ${OAK_SOURCES}
    ${OAK_PRIVATE_HEADERS}
    ${OAK_PUBLIC_HEADERS}
)

target_include_directories(oak_lib
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(oak_lib
    PUBLIC
        glm::glm
        spdlog::spdlog
    PRIVATE
        SDL3::SDL3
)

if(Dawn_FOUND)
  target_link_libraries(oak_lib PRIVATE dawn::webgpu_dawn)
else()
  target_link_libraries(oak_lib PRIVATE webgpu)
endif()

target_compile_options(oak_lib PRIVATE -Wall -Wextra -Wpedantic)

# Main executable built from src/oak.cpp
add_executable(oak "${CMAKE_CURRENT_SOURCE_DIR}/oak.cpp")

target_link_libraries(oak PRIVATE oak_lib)
target_include_directories(oak PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_options(oak PRIVATE -Wall -Wextra -Wpedantic)

if(NOT Dawn_FOUND)
  target_copy_webgpu_binaries(oak)
endif()
