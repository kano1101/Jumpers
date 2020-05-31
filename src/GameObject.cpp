#include <mix/Utility.h>
#include "GameObject.h"

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

template<class I, class P, class G>
GameObject<I, P, G>::GameObject(double x, double y, unsigned int id)
  : Mix::Sprite(DATA_[id].fpath_, DATA_[id].cx_, DATA_[id].cy_, pos_), pos_(x, y), vel_() {
}
template<class I, class P, class G>
void GameObject<I, P, G>::AddPowerToVelocity() {
  // 動力源から速度を加算
  vel_ += P()();
}
template<class I, class P, class G>
void GameObject<I, P, G>::AddGravityToVelocity() {
  // 速度に重力加速度加算
  vel_ += G()();
}
template<class I, class P, class G>
void GameObject<I, P, G>::ClampLimitToVelocity() {
  // 速度が大きくなりすぎないよう最大値リミットをかける
  const float VELOCITY_LIMIT = 1.50f;
  const Mix::Range<float> VELOCITY_RANGE{-VELOCITY_LIMIT, VELOCITY_LIMIT};
  float clampedX = VELOCITY_RANGE.Clamp(vel_.X());
  float clampedY = VELOCITY_RANGE.Clamp(vel_.Y());
  vel_.Reset(clampedX, clampedY);
}
template<class I, class P, class G>
void GameObject<I, P, G>::Update() {

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
template<class I, class P, class G>
void GameObject<I, P, G>::Draw() const {
  Mix::Sprite::Draw();
}


template class GameObject<Loki::Int2Type<0>, NoPower, NormalGravity>;
template class GameObject<Loki::Int2Type<1>, NoPower, NormalGravity>;
template class GameObject<Loki::Int2Type<2>, NoPower, NormalGravity>;
template class GameObject<Loki::Int2Type<3>, NoPower, NormalGravity>;
template class GameObject<Loki::Int2Type<4>, NoPower, NormalGravity>;
