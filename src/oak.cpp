
#include "Window/window.hpp"
#include <iostream>
#include <ostream>
#include <stdexcept>
int main() {

  Oak_Window *window = nullptr;
  try {
    window = new Oak_Window;
    window->start();
  } catch (std::runtime_error e) {
    std::cerr << e.what() << std::endl;
  }

  if (window) {
    delete window;
  }

  return 0;
}
