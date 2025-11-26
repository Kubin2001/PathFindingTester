#pragma once

#include "SceneManager.h"

#include <memory>

#include "Camera.h"

class Map;

class GameScene :public Scene{
	private:
		Map* map = nullptr;
		Camera* camera = nullptr;

		MapPos start;
		MapPos dest;
		std::vector<Point> currentPath;

	public:
		void Init(MT::Renderer* renderer = nullptr, UI* ui = nullptr)override;

		void LogicUpdate()override;

		void FrameUpdate()override;

		void Input(SDL_Event& event)override;

		void Render()override;

		void Clear()override;

		void SaveLevel();

		bool LoadLevel(const std::string &name);
};