#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <loki/Singleton.h>
#include <mix/Vector.h> // 移動ポリシーへ改善の余地がある(この行消せる)

template<
  class BaseType,
  class ImageType,
  class VectorType,
  class GravityType
  >
class GameObject
  : public BaseType
{
  using Position = VectorType;
  using Velocity = VectorType;
  
  Position pos_;
  Velocity vel_;
  
public:
  explicit GameObject()
    : pos_(100.0f, 200.0f), vel_()
  {
    
  }
  virtual void Draw() const override
  {
    using I = Loki::SingletonHolder<ImageType>;
    I::Instance().Draw(pos_);
  }
  virtual void Update() override
  {
    // 速度に重力加速度加算
    using G = Loki::SingletonHolder<GravityType>;
    vel_ += G::Instance().Vector();

    // 縦と横を別に衝突検出するため一時変数へ
    Position temp = pos_ + vel_;

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
  
};

class NormalGravity
{
public:
  Mix::Vector2D Vector() const noexcept
  {
    return Mix::Vector2D(0.0f, 0.01f);
  }
};


#endif
