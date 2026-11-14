include(FetchContent)

set(WEBGPU_BACKEND "DAWN" CACHE STRING "" FORCE)
set(WEBGPU_BUILD_FROM_SOURCE OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    webgpu
    GIT_REPOSITORY https://github.com/eliemichel/WebGPU-distribution.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(webgpu)