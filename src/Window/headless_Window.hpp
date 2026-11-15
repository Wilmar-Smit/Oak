#pragma once

#include "Window/window.hpp"
class Headless_Window : Window {

  private:
  public:
    virtual void start();
    Headless_Window();

    virtual ~Headless_Window();
};
