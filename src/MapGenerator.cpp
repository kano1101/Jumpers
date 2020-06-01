#include "MapGenerator.h"

#include "Main.h"
#include "GameObject.h"

MapGenerator::MapGenerator() {
  for ( unsigned int i = 0; i < 16; ++i ) {
    Creator<E>::Create(16.0f * i, 480.0f);
  }
}
void MapGenerator::Update() {
  Creator<MapGenerator>::Destroy(this);
}
void MapGenerator::Draw() const {}
