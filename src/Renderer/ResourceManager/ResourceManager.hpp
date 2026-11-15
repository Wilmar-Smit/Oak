#pragma once
#include "Resource.hpp"

namespace oak {

class ResourceManager {
  private:
    WGPU_Resources* resources = nullptr;

  public:
    explicit ResourceManager(WGPU_Resources*);
    ~ResourceManager();
    const WGPU_Resources* getResources();
};
} // namespace oak
