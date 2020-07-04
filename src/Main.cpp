//
//  Main.cpp
//

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLU  // GLUライブラリを使用するのに必要
#include <GLFW/glfw3.h>

#include <mix/FrameworkGL.h>
#include <mix/GraphicsGL.h>
#include <mix/InputGL.h>
#include "Main.h"
#include "Actor.h"
#include "GameObject.h"
#include "MapGenerator.h"

auto WIN_TITLE = "OpenGL Course";                      // ウィンドウのタイトル
constexpr int WIN_WIDTH   = 500;                       // ウィンドウの幅
constexpr int WIN_HEIGHT  = 500;                       // ウィンドウの高さ

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

  Mix::InputGLSetup(window);
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

  Creator<MapGenerator>::Create();
  Creator<Kuribe>::Create(256.0f, 32.0f);
  framework.Mainloop();
  
  glfwTerminate();
  return 0;
  
}
