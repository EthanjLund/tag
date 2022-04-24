#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<sstream>

#define MAX_MAIN_MENU 3

class MainMenu {
public:
	MainMenu(float width, float height);

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int MainMenuPressed() {
		return MainMenuSelected;
	}

	~MainMenu();
private:
	int MainMenuSelected;
	sf::Font font;
	sf::Text mainMenu[MAX_MAIN_MENU];
};

void runGame(sf::RenderWindow& window, sf::RenderWindow& window2, int windowWidth, int windowHeight);