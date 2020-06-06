#pragma once

#include <loki/TypeManip.h>

#include <mix/Vector.h>
#include <mix/Sprite.h>
#include <mix/Utility.h>
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
  GameObject(double x = 100.0, double y = 100.0, unsigned int id = Id::value)
    : Mix::Sprite(DATA_[id].fpath_, DATA_[id].cx_, DATA_[id].cy_, pos_), pos_(x, y), vel_() {
  }
  void AddPowerToVelocity() {
    // 動力源から速度を加算
    vel_ += PowerSourcePolicy()();
  }
  void AddGravityToVelocity() {
    // 速度に重力加速度加算
    vel_ += GravityType()();
  }
  void ClampLimitToVelocity() {
    // 速度が大きくなりすぎないよう最大値リミットをかける
    const float VELOCITY_MAX_LIMIT = 1.50f;
    const Mix::Range<float> VELOCITY_RANGE{-VELOCITY_MAX_LIMIT, VELOCITY_MAX_LIMIT};
    float clampedX = VELOCITY_RANGE.Clamp(vel_.X());
    float clampedY = VELOCITY_RANGE.Clamp(vel_.Y());
    vel_.Reset(clampedX, clampedY);
  }
  virtual void Update() override {
    
    AddPowerToVelocity();
    AddGravityToVelocity();
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

