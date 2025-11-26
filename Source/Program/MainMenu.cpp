#include "MainMenu.h"

#include <filesystem>

void MainMenu::Init(MT::Renderer* renderer, UI* ui){
	this->ui = ui;
	this->renderer = renderer;
	CreateMain();
}

void MainMenu::LogicUpdate(){}

void MainMenu::FrameUpdate(){
	MainUpdate();
	StartUpdate();
	LoadUpdate();
	if (sceneSwitch) {
		SceneMan::SwitchResetScene("Game Scene", renderer, ui);
	}
}

void MainMenu::Input(SDL_Event& event){}

void MainMenu::Render(){}

void MainMenu::Clear(){
	ui->ClearAll();
}

void MainMenu::CreateMain() {
	type = 0;
	ClickBox* cb = ui->CreateClickBoxF("QuickStart", (Global::windowWidth / 2) - 100, 100, 200, 80, nullptr, "arial20px", "Quick Start");
	cb->SetColor(30, 30, 30);
	cb->SetBorder(2, 50, 50, 200);
	cb->SetRenderTextType(2);
	cb->SetHoverFilter(true, 255, 255, 255, 120, "hoverSound");
	cb->SetClickSound("click");

	cb = ui->CreateClickBoxF("Start", (Global::windowWidth / 2) - 100, 250, 200, 80, nullptr, "arial20px", "Start");
	cb->SetColor(30, 30, 30);
	cb->SetBorder(2, 50, 50, 200);
	cb->SetRenderTextType(2);
	cb->SetHoverFilter(true, 255, 255, 255, 120, "hoverSound");
	cb->SetClickSound("click");

	cb = ui->CreateClickBoxF("Load", (Global::windowWidth / 2) - 100, 400, 200, 80, nullptr, "arial20px", "Load");
	cb->SetColor(30, 30, 30);
	cb->SetBorder(2, 50, 50, 200);
	cb->SetRenderTextType(2);
	cb->SetHoverFilter(true, 255, 255, 255, 120, "hoverSound");
	cb->SetClickSound("click");

	cb = ui->CreateClickBoxF("Exit", (Global::windowWidth / 2) - 100, 550, 200, 80, nullptr, "arial20px", "Exit");
	cb->SetColor(30, 30, 30);
	cb->SetBorder(2, 50, 50, 200);
	cb->SetRenderTextType(2);
	cb->SetHoverFilter(true, 255, 255, 255, 120, "hoverSound");
	cb->SetClickSound("click");
}

void MainMenu::MainUpdate() {
	if (type != 0) { return; }
	if (ui->GetClickBox("QuickStart")->ConsumeStatus()) {
		sceneSwitch = true;
		return;
	}
	if (ui->GetClickBox("Start")->ConsumeStatus()) {
		ClearMain();
		CreateStart();
		return;
	}
	if (ui->GetClickBox("Load")->ConsumeStatus()) {
		ClearMain();
		CreateLoad();
		return;
	}
	if (ui->GetClickBox("Exit")->ConsumeStatus()) {
		Global::status = false;
	}
}

void MainMenu::ClearMain() {
	ui->DeleteClickBox("QuickStart");
	ui->DeleteClickBox("Start");
	ui->DeleteClickBox("Load");
	ui->DeleteClickBox("Exit");
}

void MainMenu::CreateStart() {
	Button *btn = ui->CreateButtonF("RowsInfo", 200, 100, 150, 100, nullptr, "arial20px","Rows");
	btn->SetColor(30, 30, 30);
	btn->SetBorder(2, 50, 50, 200);
	btn->SetRenderTextType(2);
	btn = ui->CreateButtonF("ColumnsInfo", Global::windowWidth - 350, 100, 150, 100, nullptr, "arial20px", "Columns");
	btn->SetColor(30, 30, 30);
	btn->SetBorder(2, 50, 50, 200);
	btn->SetRenderTextType(2);

	TextBox* tb = ui->CreateTextBoxF("RowsTb", 200, 300, 150, 100, nullptr, "arial20px", "");
	tb->SetColor(200, 200, 200);
	tb->SetBorder(2, 50, 50, 200);
	tb->SetRenderTextType(2);
	tb = ui->CreateTextBoxF("ColumnsTb", Global::windowWidth - 350, 300, 150, 100, nullptr, "arial20px", "");
	tb->SetColor(200, 200, 200);
	tb->SetBorder(2, 50, 50, 200);
	tb->SetRenderTextType(2);

	ClickBox* cb = ui->CreateClickBoxF("confirm", (Global::windowWidth / 2) - 75, Global::windowHeight - 200, 150, 100, nullptr, "arial20px", "Confirm");
	cb->SetColor(30, 30, 30);
	cb->SetBorder(2, 50, 50, 200);
	cb->SetRenderTextType(2);
	cb->SetHoverFilter(true, 255, 255, 255, 120, "hoverSound");
	cb->SetClickSound("click");

	cb = ui->CreateClickBoxF("back", 10, 10, 100, 40, nullptr, "arial12px", "Back");
	cb->SetColor(30, 30, 30);
	cb->SetBorder(2, 50, 50, 200);
	cb->SetRenderTextType(2);
	cb->SetHoverFilter(true, 255, 255, 255, 120, "hoverSound");
	cb->SetClickSound("click");

	type = 1;
}

void MainMenu::StartUpdate(){
	if (type != 1) { return; }
	if (ui->GetClickBox("confirm")->ConsumeStatus()) {
		std::string textRows = ui->GetTextBox("RowsTb")->GetText();
		std::string columnRows = ui->GetTextBox("ColumnsTb")->GetText();
		int rowsInt = 0;
		int columnInt = 0;
		try {
			rowsInt = std::stoi(textRows);
			columnInt = std::stoi(columnRows);
			if (rowsInt < 1 || rowsInt > 20) {
				return;
			}
			if (columnInt < 1 || columnInt > 20) {
				return;
			}
		}
		catch (const std::exception& e) {
			return;
		}
		SceneMan::AddData<Point>("LevelSize", { rowsInt,columnInt });
		sceneSwitch = true;

		return;
	}
	if (ui->GetClickBox("back")->ConsumeStatus()) {
		ClearStart();
		CreateMain();
		return;
	}
}

void MainMenu::ClearStart() {
	ui->DeleteButton("RowsInfo");
	ui->DeleteButton("ColumnsInfo");
	ui->DeleteTextBox("RowsTb");
	ui->DeleteTextBox("ColumnsTb");
	ui->DeleteClickBox("confirm");
	ui->DeleteClickBox("back");
}

void MainMenu::CreateLoad() {
	Button *btn = ui->CreateButtonF("LoadInfo", (Global::windowWidth / 2) - 75, 100, 150, 100, nullptr, "arial20px", "Load Level");
	btn->SetColor(30, 30, 30);
	btn->SetBorder(2, 50, 50, 200);

	ClickBox *cb = ui->CreateClickBoxF("back", 10, 10, 100, 40, nullptr, "arial12px", "Back");
	cb->SetColor(30, 30, 30);
	cb->SetBorder(2, 50, 50, 200);
	cb->SetRenderTextType(2);
	cb->SetHoverFilter(true, 255, 255, 255, 120, "hoverSound");
	cb->SetClickSound("click");

	
	std::string path = "Levels";
	int counter = 1;
	int x = 10;
	int y = 200;
	if (std::filesystem::exists(path)) {
		for (auto& folder : std::filesystem::directory_iterator(path)) {
			if (folder.is_directory()) {
				cb = ui->CreateClickBoxF("Dir" + std::to_string(counter),x,y,80,80,nullptr,"arial12px",folder.path().stem().string());
				cb->SetColor(30, 30, 30);
				cb->SetBorder(2, 50, 50, 200);
				cb->SetRenderTextType(2);
				cb->SetHoverFilter(true, 255, 255, 255, 120, "hoverSound");
				cb->SetClickSound("click");
				x += 100;
				if (counter % 5 == 0) {
					x = 10;
					y += 100;
				}
				levelsVector.emplace_back(cb);
			}
			counter++;
		}
	}
	type = 2;
}

void MainMenu::LoadUpdate() {
	if (type != 2) { return; }
	for (auto& it : levelsVector) {
		if (it->ConsumeStatus()) {
			sceneSwitch = true;
			SceneMan::AddData<std::string>("Level Name", it->GetText());
			return;
		}
	}
	if (ui->GetClickBox("back")->ConsumeStatus()) {
		ClearLoad();
		CreateMain();
		return;
	}
}

void MainMenu::ClearLoad() {
	for (auto& it : levelsVector) {
		ui->DeleteClickBox(it->GetName());
	}
	levelsVector.clear();
	ui->DeleteClickBox("back");
	ui->DeleteButton("LoadInfo");
}