#pragma once

#include "Window/window.hpp"
class Headless_Window : Window {

  private:
  public:
    void start() override;
    Headless_Window();

    ~Headless_Window() override;
};
