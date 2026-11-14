cmake_minimum_required(VERSION 3.25)

if(POLICY CMP0144)
  cmake_policy(SET CMP0144 NEW)
endif()

set(WEBGPU_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/.webgpu/install")

if(NOT EXISTS "${WEBGPU_ROOT}")
  message(FATAL_ERROR "Dawn WebGPU not found at ${WEBGPU_ROOT}. Run 'just dawn-build' first.")
endif()

list(APPEND CMAKE_PREFIX_PATH "${WEBGPU_ROOT}")

find_package(Dawn REQUIRED)

# Create a unified alias so we never have to guess target names in subdirectories
if(NOT TARGET webgpu::webgpu)
  if(TARGET Dawn::webgpu)
    add_library(webgpu::webgpu ALIAS Dawn::webgpu)
  elseif(TARGET webgpu_dawn)
    add_library(webgpu::webgpu ALIAS webgpu_dawn)
  elseif(TARGET dawn::webgpu_dawn)
    add_library(webgpu::webgpu ALIAS dawn::webgpu_dawn)
  endif()
endif()
