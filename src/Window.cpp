//
//  main.cpp
//

#include <cstdlib>
#include <iostream>

#define GLFW_INCLUDE_GLU  // GLUライブラリを使用するのに必要
#include <GLFW/glfw3.h>

#include "Window.h"

#include <list>

std::list<Actor*> lst;

static const char *WIN_TITLE = "OpenGL Course";     // ウィンドウのタイトル

void Init()
{
  lst.push_back(new HeadActor);
  lst.push_back(new MainActor);
  lst.push_back(new TailActor);
}
void Exit()
{
  for ( auto& p : lst ) delete p;
}



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
  
  Init();
  
  double FPS = 59.94; // <--- 一秒間に更新する回数(30 か 60)
  double currentTime, lastTime, elapsedTime;  // <---
  currentTime = lastTime = elapsedTime = 0.0; // <---
  glfwSetTime(0.0); // <--- タイマーを初期化する
  
  // メインループ
  while (glfwWindowShouldClose(window) == GL_FALSE)
  {
    currentTime = glfwGetTime();  // <---
    elapsedTime = currentTime - lastTime; // <---
    
    // [if 節]
    if (elapsedTime >= 1.0/FPS) {
      
      // 通常の描画
      // 描画
      for ( auto& p : lst ) p->Update();
      for ( auto& p : lst ) p->Draw();
      
      // 描画用バッファの切り替え
      glfwSwapBuffers(window);
      glfwPollEvents();

      lastTime = glfwGetTime(); // <---
      
    }
    
  }
  
  glfwTerminate();
  return 0;
  
}
