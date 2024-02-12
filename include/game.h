#pragma once
#include <SFML/Graphics.hpp>
#include <settings.h>
#include <tile.h>
#include <player.h>
#include <algorithm>

class Game {
public:
	Game();
	void run();

private:
	void processEvents();
	void update(sf::Time time);
	void render();
	void setupLevel();
	void sortRenderingOrder();
	struct TilePositionComparator {
		bool operator()(Tile *tile1, Tile *tile2);
	};

private:
	sf::RenderWindow window;
	sf::View view;

	sf::Texture rockTexture;
	sf::Texture playerTexture;

	std::vector<Tile*> visibleObjects;
	std::vector<Tile*> collidableObjects;
	Player *player;
};
