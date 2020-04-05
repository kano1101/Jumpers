#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <mix/Vector.h>
#include <mix/Sprite.h>

template<class E, E e>
class Image
{
public:
  void Draw(const Mix::Vector2D& pos) const
  {
    info_[e].Draw(pos);
  }

private:
  const Mix::Sprite2D info_[E::end_of_enum] = { // アニメーションパターン情報を追加しなければならない
    { "mariwo.png",   2, 1 },
    { "kuribe.png",   2, 1 },
    { "noronoro.png", 2, 1 },
    { "items.png",    8, 1 },
    { "object.png",   8, 1 }
  };

};

enum ETex
{
  mariwo,
  kuribe,
  noronoro,
  items,
  objects,
  end_of_enum
};

#endif
