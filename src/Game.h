#pragma once

#include <loki/Typelist.h> // いる
#include <loki/TypeManip.h> // 一時的にいる

#include <mix/Director.h>

/////////////////////////////////////////////////////////////////////////
// 具象アクター(問題領域)定義

class MapGenerator;

class NoPower;
class NormalGravity;

template<class I, class P, class G>
class GameObject;
using A = GameObject<Loki::Int2Type<0>, NoPower, NormalGravity>;
using B = GameObject<Loki::Int2Type<1>, NoPower, NormalGravity>;
using C = GameObject<Loki::Int2Type<2>, NoPower, NormalGravity>;
using D = GameObject<Loki::Int2Type<3>, NoPower, NormalGravity>;
using E = GameObject<Loki::Int2Type<4>, NoPower, NormalGravity>;

using TList = Loki::TL::MakeTypelist<MapGenerator, A, B, C, D, E>::Result;

using ProjectManager = Mix::Director<TList>;

