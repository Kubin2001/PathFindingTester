#pragma once

#include <SDL.h>
#include <vector>
#include <unordered_map>
#include "Basics.h"
#include <memory>


// to remove looping dependency
class Camera;

// to remove looping dependency


class Tile : public GameObject{
	public:
		bool isPassable = true;
};

class Region : public GameObject {
	public:
		std::vector<std::vector<Tile>> TileMap;

		void Innit(size_t tileSize, size_t tilesPerRegion);

		void InnitEmpty(size_t tileSize, size_t tilesPerRegion);

		void RenderTiles(MT::Renderer* renderer, Camera* cam);
};


class Map {
	private:
		std::vector<std::vector<Region>> RegionMap;
		std::vector<Region*> FlatRegions;
		MT::Renderer* ren = nullptr;
		Camera* camera = nullptr;


	public:

		Map();

		Map(MT::Renderer* ren, Camera *camera);


		std::vector<std::vector<Region>>& GetRegions();
		std::vector<Region*>& GetFlatRegions();

		void Init(size_t tileSize, size_t tilesPerRegion, size_t regionMapWidth, size_t regionMapHeight);

		void InitEmpty(size_t tileSize, size_t tilesPerRegion, size_t regionMapWidth, size_t regionMapHeight);

		static void SetTile(MT::Texture *texture, bool passable, Tile &tile);

		static void DestroyTile(Tile& tile);

		void Render();

		//Funkcja która zwraca regiony wokó³ podanego ze sprawdzaniem granic mapy
		std::vector<Region*> GetNearbyRegions(int x, int y);

		std::vector<Point> GetNearbyRegionsIndexes(int x, int y);

		~Map();
};