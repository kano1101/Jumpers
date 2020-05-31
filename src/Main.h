#pragma once

#include "Game.h"

//////////////////////////////////////////////////////////////////
// 各具象アクターTで利用しやすいように整形
class Actor;

template<class T>
using Allocator = ProjectManager::Allocator<T>;
template<class T>
using Creator = Mix::CreateUsing<Allocator>::Creator<T>;

using Executor = ProjectManager::Executor<Actor>;

