#pragma once

#include <mix/Director.h>
#include "Game.h"

//////////////////////////////////////////////////////////////////
// 各具象アクターTで利用しやすいように整形
using ProjectManager = Mix::Director<AllActorList>;
 
template<class T>
using Allocator = ProjectManager::Allocator<T>;
template<class T>
using Creator = Mix::CreateUsing<Allocator>::Creator<T>;

class Actor;
using Executor = ProjectManager::Executor<Actor>;

