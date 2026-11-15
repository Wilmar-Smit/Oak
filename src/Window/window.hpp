#pragma once

namespace oak {

class abstract_Window {

  private:
  public:
    virtual void start() = 0;
    abstract_Window() {};

    virtual ~abstract_Window() {};
};
} // namespace oak
