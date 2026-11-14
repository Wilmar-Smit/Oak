#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
class Oak_Window {

private:
  SDL_Window *window;

public:
  void start();
  Oak_Window();
  ~Oak_Window();
};
