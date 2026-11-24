#pragma once

#include "Input/Input.hpp"
#include <memory>
namespace oak {
enum class Input_Type;

class Iwindow {

  private:
  public:
    virtual void start() = 0;
    virtual std::unique_ptr<Input> PollEvents() = 0;
    Iwindow() {};

    virtual ~Iwindow() {};
};
} // namespace oak
