#pragma once

#include <mix/Vector.h>

class NoPower {
public:
  Mix::Vector2D operator()() const noexcept {
    return Mix::Vector2D(0.0f, 0.0f);
  }
};


