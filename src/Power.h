#pragma once

#include <cassert>

#include <mix/InputGL.h>
#include <mix/Vector.h>

class NoPower {
public:
  Mix::Vector2D operator()() const noexcept {
    return Mix::Vector2D(0.0f, 0.0f);
  }
};

class ManualInputPower {
public:
  ManualInputPower() {
    // int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
    // assert( present != GLFW_TRUE );
  }
  Mix::Vector2D operator()() const noexcept {
    // int count;
    // const float* joyAxesX = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
    // if ( count == 0 ) return Mix::Vector2D(0.0f, 0.0f);
    // return Mix::Vector2D( joyAxesX[0], 0.0f);
    Mix::Vector2D dir(0.0f, 0.0f);
    if ( Mix::InputGL::Instance().IsPress('A') ) dir.Move(-0.05f);
    if ( Mix::InputGL::Instance().IsPress('D') ) dir.Move(+0.05f);
    return dir;
  }
};

