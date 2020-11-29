#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "TileMap.h"
#include <string>
#include "CollisionMap.h"

using namespace sf;
using namespace std;

class LevelMap : public TileMap {
private:
	string TilesetPath;
	CollisionMap* collMap;
public:
	LevelMap() {}

	~LevelMap() {}

	LevelMap(string tilePath, CollisionMap* collmap) : TilesetPath(tilePath), collMap(collmap) {
		load(TilesetPath, Vector2u(32, 32), collMap->getPtr(), collMap->getCols(), collMap->getRows());
	}

	void update() {
		load(TilesetPath, Vector2u(32, 32), collMap->getPtr(), collMap->getCols(), collMap->getRows());
	}
};