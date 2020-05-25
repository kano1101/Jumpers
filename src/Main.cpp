//
//  Main.cpp
//

#include <string>

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLU  // GLUライブラリを使用するのに必要
#include <GLFW/glfw3.h>

#include <mix/FrameworkGL.h>
#include <mix/Director.h>
#include <mix/Vector.h>
#include <mix/Sprite.h>

static const char *WIN_TITLE = "OpenGL Course";     // ウィンドウのタイトル
constexpr int WIN_WIDTH   = 500;                       // ウィンドウの幅
constexpr int WIN_HEIGHT  = 500;                       // ウィンドウの高さ

/////////////////////////////////////////////////////////////////////
// Actor
class Actor {
public:
  virtual ~Actor() {}
  virtual void Draw() const = 0;
  virtual void Update() {}
};


/////////////////////////////////////////////////////////////////////
// ポリシークラス
class NormalGravity {
public:
  Mix::Vector2D operator()() const noexcept {
    return Mix::Vector2D(0.0f, 0.01f);
  }
};


/////////////////////////////////////////////////////////////////////////
// GameObject定義
struct Data {
  const std::string fpath_;
  const unsigned int cx_;
  const unsigned int cy_;
};
static const Data DATA_[5] = { // アニメーションパターン情報を追加しなければならない
  { "mariwo.png"  , 1, 1, },
  { "kuribe.png"  , 1, 1, },
  { "noronoro.png", 1, 1, },
  { "items.png"   , 1, 1, },
  { "object.png"  , 1, 1, },
};

template<
  class Policy,
  class GravityType = NormalGravity
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
  GameObject(unsigned int id = 0, double x = 100.0, double y = 100.0)
    : Mix::Sprite(DATA_[id].fpath_, DATA_[id].cx_, DATA_[id].cy_, pos_), pos_(x, y), vel_() {
  }
  virtual void Update() override
  {
    // 速度に重力加速度加算
    vel_ += GravityType()();

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


/////////////////////////////////////////////////////////////////////////
// 具象アクター定義
using A = GameObject<Loki::Int2Type<0>>;
using B = GameObject<Loki::Int2Type<1>>;
using C = GameObject<Loki::Int2Type<2>>;

using TList = Loki::TL::MakeTypelist<A, B, C>::Result;

template<class T>
using Allocator = Mix::Director<TList>::Allocator<T>;
template<class T>
using Creator = Mix::CreateUsing<Allocator>::Creator<T>;

using Executor = Mix::Director<TList>::Executor<Actor>;


/////////////////////////////////////////////////////////////////////////
// エントリポイント
int main() {
  // OpenGLを初期化する
  if (glfwInit() == GL_FALSE) {
    fprintf(stderr, "Initialization failed!\n");
    return 1;
  }
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  // Windowの作成
  GLFWwindow *window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE,
                                        NULL, NULL);
  if (window == NULL) {
    fprintf(stderr, "Window creation failed!");
    glfwTerminate();
    return -1;
  }
  
  // OpenGLの描画対象にWindowを追加
  glfwMakeContextCurrent(window);

  Mix::GraphicsGL graphics(window, WIN_WIDTH, WIN_HEIGHT);
  Mix::MainWindowGL main(window);
  
  // フレームワークの実行開始
  Mix::Framework framework(
    main,
    [&] () {
      Executor::each([] (auto& actor) { actor.Update(); });
      graphics.Begin();
      Executor::each([] (auto& actor) { actor.Draw(); });
      graphics.End();
    });

  Creator<B>::Create();
  framework.Mainloop();
  
  glfwTerminate();
  return 0;
  
}
