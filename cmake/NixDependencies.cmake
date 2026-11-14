find_package(SDL3 REQUIRED)
find_package(spdlog REQUIRED)
find_package(glm REQUIRED)

find_path(SDL3_INCLUDE_DIR NAMES SDL3/SDL.h REQUIRED)
find_path(SPDLOG_INCLUDE_DIR NAMES spdlog/spdlog.h REQUIRED)
find_path(GLM_INCLUDE_DIR NAMES glm/glm.hpp REQUIRED)

add_compile_options(
    "-I${SDL3_INCLUDE_DIR}"
    "-I${SPDLOG_INCLUDE_DIR}"
    "-I${GLM_INCLUDE_DIR}"
)