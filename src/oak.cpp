
#include "Window/window.hpp"
#include <iostream>
#include <ostream>
#include <stdexcept>
int main() {

  try {
    Oak_Window *window = new Oak_Window;
    window->start();
  } catch (std::runtime_error e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
