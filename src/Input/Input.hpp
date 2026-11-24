#pragma once

namespace oak {
/**
 * An input Wrapper that I can use to map Window events to my own
 */

enum class Input_Type { CLOSE, NOP };

class Input {

  public:
    Input(Input_Type type);
    virtual ~Input() = default;

    const Input_Type type = Input_Type::NOP;
};
} // namespace oak
