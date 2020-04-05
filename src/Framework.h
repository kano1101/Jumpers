#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_

#define GLFW_INCLUDE_GLU  // GLUライブラリを使用するのに必要
#include <GLFW/glfw3.h>
#include <GL/glpng.h>
#include <loki/Typelist.h>
#include <mix/Actor.h>
#include <mix/Vector.h>
#include <mix/CyclicAllocator.h>
#include <mix/UsingAllocatorCreator.h>
#include "GameObject.h"
#include "Image.h"

class MainActor;
using AllTList = Loki::TL::MakeTypelist<MainActor>::Result;
constexpr std::size_t InstanceMax = 256;
using Base = Mix::BaseAllocatable<Mix::Actor, AllTList, InstanceMax>;

class MainActor : public GameObject<Base, Image<ETex, mariwo>, Mix::Vector2D, NormalGravity> {};

template<class T>
using Allocator = Mix::CyclicAllocator<T>;
template<class T>
using Creator = Mix::CreateUsing<Allocator>::Creator<T>;

template<int WIN_WIDTH, int WIN_HEIGHT>
class Framework
{
 private:
  GLFWwindow* const window_;
  double fps_ = 59.94; // <--- 一秒間に更新する回数(30 か 60)
  double currentTime_, lastTime_, elapsedTime_;  // <---

 public:
  Framework(GLFWwindow* const window)
    : window_(window)
  {
    // 深度テストの有効化
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0, 0.0, 1.0 / 4.0, 1.0);
    glOrtho(0.0, WIN_WIDTH, WIN_HEIGHT, 0.0, -1.0, 1.0);
    
    currentTime_ = lastTime_ = elapsedTime_ = 0.0; // <---
    glfwSetTime(0.0); // <--- タイマーを初期化する

    Creator<MainActor>::Create();
    
  }
  bool Execute()
  {
    // メインループ
    while (glfwWindowShouldClose(window_) == GL_FALSE)
    {
      currentTime_ = glfwGetTime();  // <---
      elapsedTime_ = currentTime_ - lastTime_; // <---
      
      // [if 節]
      if (elapsedTime_ >= 1.0 / fps_) {

        // フレーム更新・描画処理
        Update();
        Draw();
        
        glfwPollEvents();
        lastTime_ = glfwGetTime(); // <---
        
      }
      
    }
    return true;
  
  }
  void Update()
  {
    Allocator<Base>::ForAll(
      [] (auto& e) { static_cast<Base*>(&e)->Update(); }
    );
  }
  void Draw()
  {
    // 描画用バッファのクリア
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    //    glMatrixMode(GL_PROJECTION); // 3D
    glLoadIdentity();
    glOrtho(0.0, WIN_WIDTH, WIN_HEIGHT, 0.0, -1.0, 1.0);

    // 描画処理
    Allocator<Base>::ForAll(
      [] (auto& e) { static_cast<Base*>(&e)->Draw(); }
    );
      
    // 描画用バッファの切り替え
    glfwSwapBuffers(window_);

  }

}; // class Framework

#endif
