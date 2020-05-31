#pragma once

#include "Actor.h"
#include "Main.h"

class MapGenerator
  : public Actor {
public:
  MapGenerator();
  virtual void Update() override;
  virtual void Draw() const override;
};

