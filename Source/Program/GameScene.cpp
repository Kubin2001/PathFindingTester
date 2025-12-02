#include "GameScene.h"

#include <iostream>
#include <print>
#include <filesystem>
#include <fstream>
#include <chrono>

#include "Map.h"
#include "BreadthFirstSearch.h"
#include "BestFirstSearch.h"
#include "AStarZombia.h"

void CreateErrorBox(UI* ui, const std::string &text) {
	PopUpBox *pb =  ui->CreatePopUpBoxF("name" + std::to_string(rand()), 180, 10, 10, 200, 40, nullptr, "arial12px", text);
	pb->SetColor(30, 30, 30);
	pb->SetBorder(2, 40, 40, 200);
	pb->SetRenderTextType(2);
	SoundMan::PlaySound("hoverSound");
}

void GameScene::Init(MT::Renderer* renderer, UI* ui) {
	this->renderer = renderer;
	this->ui = ui;



	camera = new Camera(false);
	map = new Map(renderer,camera);
	if (SceneMan::IsData("LevelSize")) {
		Point p = SceneMan::GetData<Point>("LevelSize");
		map->Init(40, 16, p.x, p.y);
		SceneMan::ClearData("LevelSize");
	}
	else if (SceneMan::IsData("Level Name")) {
		if (!LoadLevel(SceneMan::GetData<std::string>("Level Name"))) {
			map->Init(40, 16, 5, 5);
		}
	}
	else {
		map->Init(40, 16, 5, 5);
	}
}

void GameScene::LogicUpdate() {
	const Uint8* state = SDL_GetKeyboardState(NULL);
	camera->UpdatePosition(state);
}

void GameScene::FrameUpdate() {

}

void GameScene::Input(SDL_Event& event) {
	camera->UpdateZoom(event);
	Point p = camera->GetMouseUntransform();
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			MapPos mp(p.x, p.y);
			map->SetTile(TexMan::GetTex("grass"), false, map->GetRegions()[mp.rows][mp.column].TileMap[mp.rowsTile][mp.columnTile]);
		}
		if (event.button.button == SDL_BUTTON_RIGHT) {
			MapPos mp(p.x, p.y);
			map->SetTile(TexMan::GetTex("stone"), false, map->GetRegions()[mp.rows][mp.column].TileMap[mp.rowsTile][mp.columnTile]);
		}
	}
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.scancode == SDL_SCANCODE_O) {
			SaveLevel();
		}
		if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
			SceneMan::SwitchResetScene("Main Menu", renderer, ui);
			return;
		}
		if (event.key.keysym.scancode == SDL_SCANCODE_C) {
			currentPath.clear();
		}

		if (event.key.keysym.scancode == SDL_SCANCODE_1) {
			start.CalcAll(p.x, p.y);
		}
		if (event.key.keysym.scancode == SDL_SCANCODE_2) {
			dest.CalcAll(p.x, p.y);
			auto startTime = std::chrono::high_resolution_clock::now();
			currentPath = BFS4(map, start, dest);

			auto endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsed = endTime - startTime;
			std::println("Czas wykonania : {} ms", elapsed.count());
			//for (const auto& it : currentPath) {
			//	std::println("ROW : {}  Column: {}", it.x, it.y);
			//}
		}

		if (event.key.keysym.scancode == SDL_SCANCODE_3) {
			dest.CalcAll(p.x, p.y);
			auto startTime = std::chrono::high_resolution_clock::now();
			currentPath = BestFS(map, start, dest);

			auto endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsed = endTime - startTime;
			std::println("Czas wykonania : {} ms", elapsed.count());
			//for (const auto& it : currentPath) {
			//	std::println("ROW : {}  Column: {}", it.x, it.y);
			//}
		}

		if (event.key.keysym.scancode == SDL_SCANCODE_4) {
			dest.CalcAll(p.x, p.y);
			auto startTime = std::chrono::high_resolution_clock::now();

			currentPath = BestFS2(map, start, dest);

			auto endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsed = endTime - startTime;
			std::println("Czas wykonania : {} ms", elapsed.count());
			//for (const auto& it : currentPath) {
			//	std::println("ROW : {}  Column: {}", it.x, it.y);
			//}
		}

		if (event.key.keysym.scancode == SDL_SCANCODE_5) {
			dest.CalcAll(p.x, p.y);
			auto startTime = std::chrono::high_resolution_clock::now();

			currentPath = ZombiaAStar(map, {start.absTileRows,start.absTileColumn}, { dest.absTileRows,dest.absTileColumn });

			auto endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsed = endTime - startTime;
			std::println("Czas wykonania : {} ms", elapsed.count());
			//for (const auto& it : currentPath) {
			//	std::println("ROW : {}  Column: {}", it.x, it.y);
			//}
		}
	}
}

void GameScene::Render() {
	map->Render();
	for (auto it : currentPath) {
		MapPos mp;
		mp.absTileRows = it.x;
		mp.absTileColumn = it.y;
		mp.RecalculateFromAbs();
		MT::Rect rect = map->GetRegions()[mp.rows][mp.column].TileMap[mp.rowsTile][mp.columnTile].GetRectangle();
		MT::Rect tempRect = camera->Transform(rect);
		renderer->RenderCopy(tempRect, TexMan::GetTex("null"));
	}
}

void GameScene::Clear() {
	delete map;
	map = nullptr;
	ui->ClearAll();
}

void GameScene::SaveLevel() {
	std::string name;
	std::print("Enter level Name or C to cancel: ");
	std::cin >> name;
	if (name == "C") { return; }

	std::string mainDirectory = "Levels";
	std::string folderName = mainDirectory + "/" + name;
	if (!std::filesystem::exists(mainDirectory)) {
		std::filesystem::create_directory(mainDirectory);
	}
	if (std::filesystem::exists(folderName)) {
		CreateErrorBox(ui, "This level already exist aborting");
	}
	else {
		std::filesystem::create_directory(folderName);
	}

	std::ofstream mapSizeFile(folderName+ "/mapSize.txt");
	std::ofstream mapDataFile(folderName + "/mapData.txt");
	mapSizeFile << map->GetRegions().size()<<"\n";
	mapSizeFile << map->GetRegions()[0].size() << "\n";

	for (auto& region : map->GetFlatRegions()) {
		for (auto &tileRow : region->TileMap) {
			for (auto& tile : tileRow) {
				if (tile.isPassable) {
					mapDataFile << 1<<"\n";
				}
				else {
					mapDataFile << 0 << "\n";
				}
			}
		}
	}
}

bool GameScene::LoadLevel(const std::string& name) {

	std::string mainDirectory = "Levels";
	std::string folderName = mainDirectory + "/" + name;
	if (!std::filesystem::exists(mainDirectory)) {
		std::filesystem::create_directory(mainDirectory);
	}
	if (!std::filesystem::exists(folderName)) {
		return false;
	}

	std::ifstream mapSizeFile(folderName + "/mapSize.txt");
	if (!mapSizeFile.is_open()) {
		return false;
	}
	std::string line;
	int rows = 0;
	int column = 0;
	if (std::getline(mapSizeFile, line)) {
		rows = std::stoi(line);
	}
	if (std::getline(mapSizeFile, line)) {
		column = std::stoi(line);
	}
	if (rows == 0 || column == 0) {
		return false;
	}

	map->InitEmpty(40, 16, column, rows);
	std::ifstream mapDataFile(folderName + "/mapData.txt");
	for (auto& region : map->GetFlatRegions()) {
		for (auto& tileRow : region->TileMap) {
			for (auto& tile : tileRow) {
				if (std::getline(mapDataFile, line)) {
					int value = stoi(line);
					if (value == 1) {// passable
						tile.SetTexture(TexMan::GetTex("grass"));
						tile.isPassable = true;
					}
					else { // 0 unpassable
						tile.isPassable = false;
						tile.SetTexture(TexMan::GetTex("stone"));
					}
				}
				
			}
		}
	}
	return true;
}