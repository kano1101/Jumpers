#pragma once

#include <mix/Vector.h>

/////////////////////////////////////////////////////////////////////
// ポリシークラス
class NormalGravity {
public:
  Mix::Vector2D operator()() const noexcept {
    return Mix::Vector2D(0.0f, 0.01f);
  }
};

class NoGravity {
public:
  Mix::Vector2D operator()() const noexcept {
    return Mix::Vector2D(0.0f, 0.0f);
  }
};
