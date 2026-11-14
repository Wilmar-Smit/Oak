file(GLOB_RECURSE OAK_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB_RECURSE OAK_PRIVATE_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

file(GLOB_RECURSE OAK_PUBLIC_HEADERS CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/include/*.hpp"
)

add_library(oak STATIC
    ${OAK_SOURCES}
    ${OAK_PRIVATE_HEADERS}
    ${OAK_PUBLIC_HEADERS}
)

target_include_directories(oak
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(oak
    PUBLIC
        glm::glm
        spdlog::spdlog
    PRIVATE
        SDL3::SDL3
)

if(Dawn_FOUND)
    target_link_libraries(oak PRIVATE dawn::webgpu_dawn)
else()
    target_link_libraries(oak PRIVATE webgpu)
endif()

target_compile_options(oak PRIVATE -Wall -Wextra -Wpedantic)
