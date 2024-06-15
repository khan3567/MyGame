#include <SFML/Graphics.hpp>
#include <iostream>
#include "view.h"
#include "Persons.h"
#include "map.h"
#include <sstream>



int main() {
	sf::RenderWindow window(sf::VideoMode(900, 600), "game"); // объект окна: размер и заголовок; параметр sf::Style::Fullscreen - для открытия на вессь экран
	view.reset(sf::FloatRect(0, 0, 800, 600));


	// Шрифт Sonic
	sf::Font SonicFont;
	SonicFont.loadFromFile("../assets/fonts/SonicШрифт.TTF");

	// Шрифт Смайлы
	sf::Font SmilesFont;
	SmilesFont.loadFromFile("../assets/fonts/SmilesШрифт.TTF");

	// Шрифт Смайлы
	sf::Font BloodFont;
	BloodFont.loadFromFile("../assets/fonts/Blood.TTF");

	// текст жизни
	sf::Text text_health("", SmilesFont, 30);
	text_health.setOutlineColor(sf::Color::White);
	text_health.setFillColor(sf::Color(0, 91, 237));
	text_health.setStyle(sf::Text::Bold);

	// текст монеты
	sf::Text text_coins("", SonicFont, 27);
	text_coins.setOutlineColor(sf::Color::White);
	text_coins.setFillColor(sf::Color::White);
	text_coins.setStyle(sf::Text::Regular);

	// текст победа
	sf::Text text_win("", SonicFont, 250);
	text_win.setOutlineColor(sf::Color::White);
	text_win.setFillColor(sf::Color(0, 91, 237));
	text_win.setStyle(sf::Text::Bold);

	// текст поражение
	sf::Text text_loss("", BloodFont, 220);
	text_loss.setOutlineColor(sf::Color::White);
	text_loss.setFillColor(sf::Color(152, 0, 2));
	text_loss.setStyle(sf::Text::Bold);





	// создание главного героя и его анимаций
	PLAYER mainPlayer(150, 600, 53, 72, 0, 0, 3);
	sf::Texture sonic_texture;
	sonic_texture.loadFromFile("../assets/images/sonic.png");
	mainPlayer.animman.create("walk", sonic_texture, 15, 276, 73, 68, 5, 0.008, 85);
	mainPlayer.animman.create("jump", sonic_texture, 314, 548, 62, 62, 4, 0.015, 70);
	mainPlayer.animman.create("duck", sonic_texture, 215, 630, 70, 80, 1, 0.005);
	mainPlayer.animman.create("stay", sonic_texture, 9, 1, 51, 78, 7, 0.003, 71);
	mainPlayer.animman.create("dead", sonic_texture, 360, 80, 70, 80, 1, 0.005);

	
	// карта
	sf::Image map_image;//объект изображения для карты
	map_image.loadFromFile("../assets/images/map.png");//загружаем файл для карты
	sf::Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	sf::Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом


	// враги
	std::vector<Mashroom> listEnemies;
	std::vector<Turtle> listTurtles;
	
	Mashroom mashroom1(400, 500, 33, 70, 0.01, 0.01, 1);
	listEnemies.push_back(mashroom1);

	Mashroom mashroom2(670, 70, 33, 70, 0.01, 0.01, 1);
	listEnemies.push_back(mashroom2);

	Mashroom mashroom3(1154, 400, 33, 70, 0.01, 0.01, 1);
	listEnemies.push_back(mashroom3);

	Mashroom mashroom4(2273, 400, 33, 70, 0.01, 0.01, 1);
	listEnemies.push_back(mashroom4);

	Mashroom mashroom5(3700, 440, 33, 70, 0.01, 0.01, 1);
	listEnemies.push_back(mashroom5);

	Mashroom mashroom6(3950, 100, 33, 70, 0.01, 0.01, 1);
	listEnemies.push_back(mashroom6);

	Mashroom mashroom7(3850, 100, 33, 70, 0.01, 0.01, 1);
	listEnemies.push_back(mashroom7);

	Turtle turtle1(300, 100, 33, 70, 0.01, 0.01, 1);
	listTurtles.push_back(turtle1);

	Turtle turtle2(800, 600, 33, 70, 0.01, 0.01, 1);
	listTurtles.push_back(turtle2);

	Turtle turtle3(3155, 460, 33, 70, 0.01, 0.01, 1);
	listTurtles.push_back(turtle3);
	
	Turtle turtle4(3072, 460, 33, 70, 0.01, 0.01, 1);
	listTurtles.push_back(turtle4);

	
	sf::Clock clock;

	while (window.isOpen()) {

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 700;



		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close(); // закрытие окна
		}

		mainPlayer.animman.set("stay");

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			mainPlayer.key["L"] = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			mainPlayer.key["R"] = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			mainPlayer.key["Up"] = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			mainPlayer.key["Down"] = true;
		}



		

		if (mainPlayer.isAlive) {
			for (int i = 0; i < listEnemies.size(); i++) {

				listEnemies[i].update(time);

				if (mainPlayer.currentFrameRect.intersects(listEnemies[i].currentFrameRect) and (listEnemies[i].isAlive)) {

					if (mainPlayer.dy > 0) {
						listEnemies[i].isAlive = false;
						listEnemies[i].dy = -0.3;
						mainPlayer.hit = true;
					}
					else {
						if (!mainPlayer.shield) {
							mainPlayer.gothit = true;
						}
					}


				}

			}
		}
		
		if (mainPlayer.isAlive) {
			for (int i = 0; i < listTurtles.size(); i++) {

				if ((time > 5) and (time < 5.1) and (listTurtles[i].dy == 0)) {
					listTurtles[i].dy = -0.3;
				}

				listTurtles[i].update(time);

				if (mainPlayer.currentFrameRect.intersects(listTurtles[i].currentFrameRect) and (listTurtles[i].isAlive)) {

					if (mainPlayer.dy > 0) {
						listTurtles[i].isAlive = false;
						listTurtles[i].dy = -0.3;
						mainPlayer.hit = true;
					}
					else {
						if (!mainPlayer.shield) {
							mainPlayer.gothit = true;
						}
					}


				}

			}
		}

		mainPlayer.update(time);
		

		getpleyercoordforview(mainPlayer.x, mainPlayer.y);

		window.setView(view);

		window.clear(sf::Color(100, 200, 200));



		// рисовка карты
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == '0') s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));
				if (TileMap[i][j] == 'b') s_map.setTextureRect(sf::IntRect(64, 0, 32, 32));
				if (TileMap[i][j] == 'c') s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == 'f') s_map.setTextureRect(sf::IntRect(128, 0, 32, 32));
				if (TileMap[i][j] == 'F') s_map.setTextureRect(sf::IntRect(96, 0, 32, 32));

				
				if (TileMap[i][j] == ' ') continue;

				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);
			}



		
		for (Mashroom mashroom1 : listEnemies) {
			mashroom1.animman.draw(window, mashroom1.x, mashroom1.y);
		}

		for (Turtle turtle1 : listTurtles) {
			turtle1.animman.draw(window, turtle1.x, turtle1.y);
		}
		

		mainPlayer.animman.draw(window, mainPlayer.x, mainPlayer.y);

		
		std::string health_string;
		for (int i = 0; i < mainPlayer.health; i++) {
			health_string += "b";
		}
		

		// жизни 
		text_health.setString(health_string);
		text_health.setPosition((mainPlayer.x - 15), mainPlayer.y - 40);
		window.draw(text_health);


		// монеты
		std::ostringstream playerCoinsString;
		playerCoinsString << mainPlayer.crystals;
		text_coins.setString(playerCoinsString.str() + "$");
		text_coins.setPosition(view.getCenter().x - 370, view.getCenter().y - 280);
		window.draw(text_coins);


		// победа
		if (mainPlayer.win) {
			std::ostringstream playerWinString;
			playerWinString << " You \nwin!!!";
			text_win.setString(playerWinString.str());
			text_win.setPosition(view.getCenter().x - 340, view.getCenter().y - 300);
			window.draw(text_win);
		}

		// поражение
		if (!mainPlayer.isAlive) {
			std::ostringstream playerLossString;
			playerLossString << "You are\n   dead";
			text_loss.setString(playerLossString.str());
			text_loss.setPosition(view.getCenter().x - 340, view.getCenter().y - 300);
			window.draw(text_loss);
		}

		window.display();


	}

}


