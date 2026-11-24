#pragma once

#include "Input/Input.hpp"
#include "Renderer/ResourceManager/ResourceManager.hpp"
#include <expected>
#include <memory>
#include <string>
namespace oak {
enum class Input_Type;
class ResourceManager;

class Iwindow {

  private:
  public:
    virtual std::expected<bool, std::string> init_window() = 0;
    virtual std::expected<std::unique_ptr<ResourceManager>, std::string> init_resources() = 0;
    virtual void stop() = 0;
    virtual void start() = 0;
    virtual std::unique_ptr<Input> PollEvents() = 0;

    Iwindow() {};

    virtual ~Iwindow() {};
};
} // namespace oak
