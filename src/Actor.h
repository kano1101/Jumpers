#pragma once

/////////////////////////////////////////////////////////////////////
// Actor
class Actor {
public:
  virtual ~Actor() {}
  virtual void Update() = 0;
  virtual void Draw() const = 0;
};


