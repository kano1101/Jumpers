//
//  Main.cpp
//

#define GLFW_INCLUDE_GLU  // GLUライブラリを使用するのに必要
#include <GLFW/glfw3.h>

#include "Framework.h"

static const char *WIN_TITLE = "OpenGL Course";     // ウィンドウのタイトル
constexpr int WIN_WIDTH   = 500;                       // ウィンドウの幅
constexpr int WIN_HEIGHT  = 500;                       // ウィンドウの高さ

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

  // フレームワークの実行開始
  Framework<WIN_WIDTH,WIN_HEIGHT> framework(window);
  if(framework.Execute() == false) {
    glfwTerminate();
    return -1;
  }
  
  glfwTerminate();
  return 0;
  
}
