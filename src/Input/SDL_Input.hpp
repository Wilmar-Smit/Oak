#pragma once

#include "Input/Input.hpp"

union SDL_Event;
namespace oak {

class SDL_Input : public oak::Input {

  public:
    SDL_Input(SDL_Event);

  private:
    constexpr oak::Input_Type Convert_Type(SDL_Event);
};

} // namespace oak
