cmake_minimum_required(VERSION 3.25)

if(POLICY CMP0144)
  cmake_policy(SET CMP0144 NEW)
endif()

set(WEBGPU_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/.webgpu/install")

if(NOT EXISTS "${WEBGPU_ROOT}")
  message(FATAL_ERROR "Dawn WebGPU not found at ${WEBGPU_ROOT}. Run 'just dawn-build' first.")
endif()

list(APPEND CMAKE_PREFIX_PATH "${WEBGPU_ROOT}")

find_package(Dawn QUIET)

find_library(DAWN_LIBRARY
    NAMES webgpu_dawn webgpu
    PATHS "${WEBGPU_ROOT}/lib64" "${WEBGPU_ROOT}/lib"
    NO_DEFAULT_PATH
)

if(NOT TARGET webgpu::webgpu)
  add_library(webgpu::webgpu STATIC IMPORTED)
  set_target_properties(webgpu::webgpu PROPERTIES
        IMPORTED_LOCATION "${DAWN_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${WEBGPU_ROOT}/include"
    )
else()
  set_target_properties(webgpu::webgpu PROPERTIES
        INTERFACE_LINK_LIBRARIES ""
    )
endif()

foreach(alt_target webgpu WebGPU::webgpu dawn::webgpu Dawn::webgpu webgpu_dawn)
  if(NOT TARGET ${alt_target})
    if(alt_target MATCHES "::")
      add_library(${alt_target} ALIAS webgpu::webgpu)
    else()
      add_library(${alt_target} STATIC IMPORTED)
      set_target_properties(${alt_target} PROPERTIES
                IMPORTED_LOCATION "${DAWN_LIBRARY}"
                INTERFACE_INCLUDE_DIRECTORIES "${WEBGPU_ROOT}/include"
                INTERFACE_LINK_LIBRARIES ""
            )
    endif()
  else()
    set_target_properties(${alt_target} PROPERTIES
            INTERFACE_LINK_LIBRARIES ""
        )
  endif()
endforeach()

include(FetchContent)

FetchContent_Declare(
    sdl3webgpu
    GIT_REPOSITORY https://github.com/eliemichel/sdl3webgpu.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(sdl3webgpu)

if(TARGET sdl3webgpu)
  target_include_directories(sdl3webgpu PRIVATE "${WEBGPU_ROOT}/include")
  target_link_libraries(sdl3webgpu PRIVATE webgpu::webgpu)
endif()
