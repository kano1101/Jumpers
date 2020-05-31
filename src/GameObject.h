#pragma once

#include <loki/TypeManip.h>

#include <mix/Vector.h>
#include <mix/Sprite.h>
#include "Actor.h"
#include "Power.h"
#include "Gravity.h"

/////////////////////////////////////////////////////////////////////////
// GameObject定義
template<
  class Id,
  class PowerSourcePolicy,
  class GravityType
  >
class GameObject
  : public Actor
  , public Mix::Sprite {
private:
  using Position = Mix::Vector2D;
  using Velocity = Mix::Vector2D;
  
  Position pos_;
  Velocity vel_;

public:
  GameObject(double x = 100.0, double y = 100.0, unsigned int id = Id::value);
  void AddPowerToVelocity();
  void AddGravityToVelocity();
  void ClampLimitToVelocity();
  virtual void Update() override;
  virtual void Draw() const override;
};

