// This example will use SFML libraries to implement
// the game of Pong

// History: 4/16 - Started from the SFML tutorial code that draws
//                a circle in the window.

#include <SFML/Graphics.hpp> 

#include "MainMenu.h"

int main(void){
	const int windowWidth = 960;
	const int windowHeight = 540;
	//make a window
	sf::RenderWindow MENU(sf::VideoMode(windowWidth,windowHeight), "Main Menu", sf::Style::Default);
	MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);

	//photo to main menu background
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(windowWidth, windowHeight));
	sf::Texture mainBackground;
	mainBackground.loadFromFile("Textures/HideAndSeek.png");
	background.setTexture(&mainBackground);

	

	while (MENU.isOpen()) {
		sf::Event event;
		while (MENU.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				MENU.close();
			}
			
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::W) {
					mainMenu.MoveUp();
					break;
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::S) {
					mainMenu.MoveDown();
					break;
				}
			}
			if (event.key.code == sf::Keyboard::Return) {
				sf::RenderWindow Host(sf::VideoMode(windowWidth, windowHeight), "Host Menu");
				sf::RenderWindow Join(sf::VideoMode(windowWidth, windowHeight), "Join Menu");

				int x = mainMenu.MainMenuPressed();
				if (x == 0) {
					runGame(Host, Join, windowWidth,windowHeight);
					/*while (Host.isOpen()) {
						sf::Event aevent;
						while (Host.pollEvent(aevent)) {
							if (aevent.type == sf::Event::Closed) {
								Host.close();
							}
							
						}
						Join.close();
						Host.clear();
						Host.display();
					}*/
				}
				if (x == 1) {
					while (Join.isOpen()) {
						sf::Event aevent;
						while (Join.pollEvent(aevent)) {
							if (aevent.type == sf::Event::Closed) {
								Join.close();
							}

						}
						Host.close();
						Join.clear();
						Join.display();
					}
				}
				if (x == 2) {
					MENU.close();
					break;
				}
			}

		}
		MENU.clear();
		MENU.draw(background);
		mainMenu.draw(MENU);
		MENU.display();
	}

	return 0;
}