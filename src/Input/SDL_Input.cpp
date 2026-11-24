#include "SDL_Input.hpp"
#include "Input/Input.hpp"
#include <SDL3/SDL.h>

namespace oak {

SDL_Input::SDL_Input(SDL_Event event) : Input(Convert_Type(event)) {}

constexpr oak::Input_Type SDL_Input::Convert_Type(SDL_Event event) {

    switch (event.type) {
    case SDL_EVENT_QUIT:
        return Input_Type::CLOSE;

    default:
        return Input_Type::NOP;
    }
}
} // namespace oak
