//
//  Created by 狩野 亮 on 2020/03/29.
//  Copyright © 2020年 狩野 亮. All rights reserved.
//

#ifndef Main_h
#define Main_h

#include <vector>
#include <cmath>
#include <iostream>
#include <unistd.h>

#include <GL/glpng.h>

#include <loki/Typelist.h>
#include <loki/MultiMethods.h>

#include <mix/Actor.h>
#include <mix/Vector.h>

static int WIN_WIDTH   = 500;                       // ウィンドウの幅
static int WIN_HEIGHT  = 500;                       // ウィンドウの高さ

using Mix::Actor;

template<class E, E e>
class Image
{
private:
  class Info
  {
  private:
    const char* fnm_;
    unsigned int cx_, cy_;
    GLfloat cw_, ch_;
    GLfloat* src_;
    std::vector<GLfloat*> uv_;
    GLuint id_;
    pngInfo pinf_;
    
  public:
    ~Info()
    {
      delete[] src_;
      for(auto& p : uv_) delete[] p;
    }
    Info(const char* fnm, unsigned int cx, unsigned int cy) // TODO:cyの後ろにアニメーションパターン情報
      : fnm_(fnm), cx_(cx), cy_(cy)
    {
      id_ = pngBind(fnm, PNG_NOMIPMAP, PNG_ALPHA, &pinf_, GL_CLAMP, GL_NEAREST, GL_NEAREST);
      
      GLfloat w = pinf_.Width / cx_;
      GLfloat h = pinf_.Height / cy_;
      src_ = new GLfloat[8] { 0, 0, w, 0, w, h, 0, h };

      GLfloat u = static_cast<GLfloat>(1.0f / cx_);
      GLfloat v = static_cast<GLfloat>(1.0f / cy_);
      for( unsigned int j = 0; j < cy_; j++ )
        for( unsigned int i = 0; i < cx_; i++ )
          uv_.push_back(new GLfloat[8] {
            u * (i + 0), v * (j + 0),
            u * (i + 1), v * (j + 0),
            u * (i + 1), v * (j + 1),
            u * (i + 0), v * (j + 1),
          });
    }

  public:
    void Draw(const Mix::Vector2D& pos) const
    {
      glVertexPointer(2, GL_FLOAT, 0, src_);
      glTexCoordPointer(2, GL_FLOAT, 0, uv_[0]);

      // テクスチャの描画
      glEnable(GL_TEXTURE_2D);
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);

      glPushMatrix();
      glBindTexture(GL_TEXTURE_2D, id_);
      glTranslatef(pos.X(), pos.Y(), 0);
      glDrawArrays(GL_QUADS, 0, 4);
      glPopMatrix();

      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      glDisableClientState(GL_VERTEX_ARRAY);
      glDisable(GL_TEXTURE_2D);

    }

  };

public:
  void Draw(const Mix::Vector2D& pos) const
  {
    info_[e].Draw(pos);
  }

private:
  const Info info_[E::end_of_enum] = { // アニメーションパターン情報を追加しなければならない
    { "mariwo.png",   2, 1 },
    { "kuribe.png",   2, 1 },
    { "noronoro.png", 2, 1 },
    { "items.png",    8, 1 },
    { "object.png",   8, 1 }
  };

};

class NormalGravity
{
public:
  Mix::Vector2D Vector() const noexcept
  {
    return Mix::Vector2D(0.0f, 0.01f);
  }
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


// class CollideTimeAction
// {
// public:
//   bool IsCollide(
// };

template<class Image, class VectorType, class Gravity>
class GameObject
  : public Actor
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
    using I = Loki::SingletonHolder<Image>;
    I::Instance().Draw(pos_);
  }
  virtual void Update() override
  {
    // // 速度に重力加速度加算
    // using G = Loki::SingletonHolder<Gravity>;
    // vel_ += G::Instance().Vector();

    // // 縦と横を別に衝突検出するため一時変数へ
    // Position temp = pos_ + vel_;

    // if (!false) // 横判定：壁ブロックに当たっていなければ
    //   pos_ += temp.AsX();
    // else
    //   ; // TODO:衝突位置へpos_調整およびvel_.X(0.0f)で止まる
    // if (!false) // 縦判定：床ブロックに当たっていなければ
    //   pos_ += temp.AsY();
    // else
    // {
    //   ; // TODO:衝突位置へpos_調整およびvel_.Y(0.0f)で止まる
    //   if (vel_.Y() > 0) // TODO:Y方向へはvel_.Y()のによってはブロックを叩く
    //     ; // TODO:叩いたらアクション（ポリシーに実装）
    // }
  }
  
};

class HeadActor
  : public Actor
{
public:
  HeadActor()
  {
    // 深度テストの有効化
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0, 0.0, 1.0 / 4.0, 1.0);
    glOrtho(0.0, WIN_WIDTH, WIN_HEIGHT, 0.0, -1.0, 1.0);
    
  }
  void Draw() const override
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    //    glMatrixMode(GL_PROJECTION); // 3D
    glLoadIdentity();
    glOrtho(0.0, WIN_WIDTH, WIN_HEIGHT, 0.0, -1.0, 1.0);
    
  }
  void Update() override
  {
    static double beforeTime;
    double nowTime = glfwGetTime();
    beforeTime = nowTime;
  }
  
}; // class HeadActor

class TailActor
  : public Actor
{
public:
  void Draw() const override
  {
//    glutSwapBuffers();
  }
  void Update() override
  {
    
  }
  
};

using MainActor = GameObject<Image<ETex, mariwo>, Mix::Vector2D, NormalGravity>;

// class MainActor
//   : public Actor
// {
// private:
//   Texture tex_;
//   Mix::Sprite<2, 2> sp_;
//   GLfloat theta_;
// public:
//   MainActor() : tex_("image.png"), sp_(tex_), theta_(0)
//   {
    
//   }
//   void Draw() const override
//   {
//     //    sp_.Draw(tex_.GetHandle(), 150.0 + 100 * cos(theta_), 100.0 + 20 * sin(theta_), 0);
//     static int tmp = 0;
//     sp_.Draw(tex_.GetHandle(), 0, 0, (tmp++ / 60) % 4);
//   }
//   void Update() override
//   {
//     static const double PI = 4.0 * atan(1.0);           // 円周率の定義
//     theta_ += 1.0f * PI / 100.0f;  // 100分の1回転
    
//   }

// };

#endif /* Main_h */
