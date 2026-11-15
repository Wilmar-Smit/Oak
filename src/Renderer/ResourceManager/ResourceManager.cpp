#include "ResourceManager.hpp"
namespace oak {

ResourceManager::ResourceManager(WGPU_Resources* resources) : resources(resources) {}
ResourceManager::~ResourceManager() {

    if (resources->surface)
    {    resources->surface.Unconfigure();}

    if (resources->device)
    {   resources->device.Destroy();}

    if (resources->instance)
    {    resources->instance.ProcessEvents();}

    resources->surface = nullptr;
    resources->queue = nullptr;
    resources->device = nullptr;
    resources->adapter = nullptr;
    resources->instance = nullptr;
    delete resources;
}

const WGPU_Resources* ResourceManager::getResources() { return this->resources; }
} // namespace oak
