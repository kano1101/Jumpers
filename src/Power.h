#pragma once

#include <cassert>

#include <loki/Visitor.h>

#include <mix/InputGL.h>
#include <mix/Vector.h>

#include "Game.h"

using PowerVisitorInterface = Loki::CyclicVisitor<
  void,
  Loki::TL::MakeTypelist<Kuribe, Block>::Result
  >;

class PowerVisitable {
public:
  virtual void Accept(PowerVisitorInterface&) = 0;
};

class PowerVisitor
  : public PowerVisitorInterface {
public:
  template<class Mover> void Move(Mover& e, const Mix::Vector2D& v) {
    e.ResetVelocity(v);
  }
  virtual void Visit(Kuribe& e) { Move(e, Mix::Vector2D(-0.25f, 0)); }
  virtual void Visit(Block& e) {
    Mix::Vector2D dir(0.0f, 0.0f);
    if ( Mix::InputGL::Instance().IsPress('A') ) dir.Move(-0.5f);
    if ( Mix::InputGL::Instance().IsPress('D') ) dir.Move(+0.5f);
    Move(e, dir);
  }
};

