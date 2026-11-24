#pragma once

#include "Window/window.hpp"
namespace oak {

class Headless_Window : public oak::abstract_Window {

  private:
  public:
    void start() override;
    Headless_Window();

    ~Headless_Window() override;
};
} // namespace oak
