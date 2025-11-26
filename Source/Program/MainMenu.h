#pragma once

#include "SceneManager.h"

class MainMenu :public Scene {
	private:
		int type = 0; // 0 g³ówne 1 tworzenie poziomu 2 wczytywanie poziomu
		bool sceneSwitch = false;

		std::vector<ClickBox*> levelsVector;

	public:
		void Init(MT::Renderer* renderer = nullptr, UI* ui = nullptr)override;

		void LogicUpdate()override;

		void FrameUpdate()override;

		void Input(SDL_Event& event)override;

		void Render()override;

		void Clear()override;

		void CreateMain();

		void MainUpdate();

		void ClearMain();

		void CreateStart();

		void StartUpdate();

		void ClearStart();

		void CreateLoad();

		void LoadUpdate();

		void ClearLoad();
};
