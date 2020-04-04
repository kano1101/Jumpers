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

#include <mix/Actor.h>
#include <mix/Texture.h>

static int WIN_WIDTH   = 500;                       // ウィンドウの幅
static int WIN_HEIGHT  = 500;                       // ウィンドウの高さ

using Mix::Actor;
using Mix::Texture;

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

class MainActor
  : public Actor
{
private:
  Texture tex_;
  Mix::Sprite<2, 2> sp_;
  GLfloat theta_;
public:
  MainActor() : tex_("image.png"), sp_(tex_), theta_(0)
  {
    
  }
  void Draw() const override
  {
    //    sp_.Draw(tex_.GetHandle(), 150.0 + 100 * cos(theta_), 100.0 + 20 * sin(theta_), 0);
    static int tmp = 0;
    sp_.Draw(tex_.GetHandle(), 0, 0, (tmp++ / 60) % 4);
  }
  void Update() override
  {
    static const double PI = 4.0 * atan(1.0);           // 円周率の定義
    theta_ += 1.0f * PI / 100.0f;  // 100分の1回転
    
  }

};

#endif /* Main_h */
