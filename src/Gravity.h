#pragma once

#include <iostream>

#include <loki/Visitor.h>

#include <mix/Vector.h>

#include "Game.h"

/////////////////////////////////////////////////////////////////////
// ポリシークラス
using GravityVisitorInterface = Loki::CyclicVisitor<
  void,
  GameObjectList
  >;

class GravityVisitable {
public:
  virtual ~GravityVisitable() {}
  virtual void Accept(GravityVisitorInterface&) = 0;
};

class GravityVisitor
  : public GravityVisitorInterface {
public:
#ifndef NDEBUG
  inline static int n_ { 0 } ;
  GravityVisitor()   { std::cout << "GravityVisitor ctor Count = " <<  n_++ << std::endl; }
  ~GravityVisitor()  { std::cout << "GravityVisitor dtor Count = " <<  --n_ << std::endl; }
#endif
  
  template<class Mover>
  void Move(Mover& e, const Mix::Vector2D& g) {
    e.AddVelocity(g);
  }

  virtual void Visit(Mariwo& e)   { this->Move(e, Mix::Vector2D(0, 0.025f)); }
  virtual void Visit(Kuribe& e)   { this->Move(e, Mix::Vector2D(0, 0.025f)); }
  virtual void Visit(Noronoro& e) { this->Move(e, Mix::Vector2D(0, 0.025f)); }
  virtual void Visit(Item& e)     { this->Move(e, Mix::Vector2D(0, 0.025f)); }
  virtual void Visit(Block& e)    { (void)e; return; }
};

