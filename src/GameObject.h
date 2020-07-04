#pragma once

#include <loki/TypeManip.h>
#include <loki/Singleton.h>

#include <mix/Vector.h>
#include <mix/Sprite.h>
#include <mix/CollideRect.h>
#include <mix/Hatch.h>
//#include <mix/Utility.h>

#include "Actor.h"
#include "Power.h"
#include "Gravity.h"

namespace {
  struct Data {
    const std::string fpath_;
    const unsigned int cx_;
    const unsigned int cy_;
  };
  static const Data DATA_[5] = { // アニメーションパターン情報を追加しなければならない
    { "mariwo.png"  , 2, 1, },
    { "kuribe.png"  , 2, 1, },
    { "noronoro.png", 2, 1, },
    { "items.png"   , 8, 1, },
    { "object.png"  , 8, 1, },
  };
}

template<class T>
class ActionTo {
  T& elem_;
public:
  ActionTo(T& elem) : elem_(elem) {}
  virtual void Reset(const Mix::Vector2D& velocity) { elem_.Reset(velocity); }
  virtual void Move (const Mix::Vector2D& force)    { elem_.Move (force);    }
};

/////////////////////////////////////////////////////////////////////////
// GameObject定義
template<
  class Id
  >
class GameObject
  : public Actor
  , public Mix::Sprite
  , public Mix::CollideRect<Mix::Vector2D*>
  , public PowerVisitable
  , public GravityVisitable {
private:
  using VectorType = Mix::Vector2D;
  using Position = Mix::Vector2D;
  using Velocity = Mix::Vector2D;
  
  Position pos_;
  Velocity vel_;

public:
  LOKI_DEFINE_CYCLIC_VISITABLE(PowerVisitorInterface);
  LOKI_DEFINE_CYCLIC_VISITABLE(GravityVisitorInterface);

  GameObject(double x = 100.0, double y = 100.0, unsigned int id = Id::value)
    : Mix::Sprite(DATA_[id].fpath_, DATA_[id].cx_, DATA_[id].cy_, pos_)
    , Mix::CollideRect<Mix::Vector2D*>(&pos_, VectorType{ 0, 0 }, VectorType{ 16, 16 })
    , pos_(x, y)
    , vel_() {
  }
  
  void ResetVelocity(const Mix::Vector2D& velocity) {
    // 速度をリセット
    vel_.Reset(velocity.X(), velocity.Y());
  }
  void AddVelocity(const Mix::Vector2D& force) {
    // 速度に力を加算
    vel_.Move(force.X(), force.Y());
  }

  void ClampLimitToVelocity(double limit = 5.0f) {
    // 速度が大きくなりすぎないよう最大値リミットをかける
    const Mix::Range<double> VELOCITY_RANGE{-limit, limit};
    double clampedX = VELOCITY_RANGE.Clamp(vel_.X());
    double clampedY = VELOCITY_RANGE.Clamp(vel_.Y());
    vel_.Reset(clampedX, clampedY);
  }
  // void CollisionBehaivior() {
  //   Mix::HatchDispatcher d = Mix::MakeHatchDispatcher();
    
  // }
  
  virtual void Update() override {

    // 積み並べ織り成すVisitorら
    
    Accept(Loki::SingletonHolder<PowerVisitor>::Instance());
    Accept(Loki::SingletonHolder<GravityVisitor>::Instance());
    
    ClampLimitToVelocity();

    // 縦と横を別に衝突検出するため一時変数へ
    Position temp = pos_ + vel_;
    (void)temp;

    if (!false) // 横判定：壁ブロックに当たっていなければ
      pos_ += vel_.AsX();
    else
      ; // TODO:衝突位置へpos_調整およびvel_.X(0.0f)で止まる
    if (!false) // 縦判定：床ブロックに当たっていなければ
      pos_ += vel_.AsY();
    else
    {
      ; // TODO:衝突位置へpos_調整およびvel_.Y(0.0f)で止まる
      if (vel_.Y() > 0) // TODO:Y方向へはvel_.Y()のによってはブロックを叩く
        ; // TODO:叩いたらアクション（ポリシーに実装）
    }
  }

  virtual void Draw() const override {
    Mix::Sprite::Draw();
  }

};

