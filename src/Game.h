#pragma once

#include <loki/Typelist.h> // いる
#include <loki/TypeManip.h> // 一時的にいる
#include <loki/Visitor.h>
#include <loki/MultiMethods.h>

//#include <mix/Director.h>
//#include <mix/CollideRect.h>

#include <mix/Utility.h>

template<class I>
class GameObject;

using Mariwo   = GameObject<Loki::Int2Type<0>>;
using Kuribe   = GameObject<Loki::Int2Type<1>>;
using Noronoro = GameObject<Loki::Int2Type<2>>;
using Item     = GameObject<Loki::Int2Type<3>>;
using Block    = GameObject<Loki::Int2Type<4>>;
using GameObjectList = Loki::TL::MakeTypelist<Mariwo, Kuribe, Noronoro, Item, Block>::Result;

class MapGenerator;
using MapGeneratorList = Loki::TL::MakeTypelist<MapGenerator>::Result;

using AllActorList = Mix::TL::Connect<MapGeneratorList, GameObjectList>::Result;

///////////////////////////////////////////////////////////////////////////////
// TODO:以下、本当ならここに挿入すべきコードだろうか？別ファイルの気がする
// なぜならGameObjectのプライベートメンバにアクセスできないからだ
// class ActionBE {
// public:
//   void operator()(B& b, E& e) {
    
//   }
// };

// using ActionDispatcher = Loki::FunctorDispatcher<Actor>;

// namespace {
//   ActionDispatcher MakeActionDispatcher() {
//     ActionDispatcher d;
//     d.Add<B, E>(ActionBE());
//     return d;
//   }
// }

