#pragma once
#include <SFML/Graphics.hpp>
#include <settings.h>
#include <tile.h>
#include <player.h>
#include <algorithm>

class Game {
public:
	Game();
	void run(const float framesPerSecond);

private:
	void processEvents();
	void update(sf::Time time);
	void render();
	void setupLevel();

	struct TilePositionComparator {
		bool operator()(Tile *tile1, Tile *tile2) {
			return tile1->getPosition().y < tile2->getPosition().y;
		}
	};
	void sortRenderingOrder() {
		std::sort(visibleObjects.begin(), visibleObjects.end(), TilePositionComparator());
	}

private:
	sf::RenderWindow window;
	sf::View view;

	std::vector<Tile*> visibleObjects;
	std::vector<Tile*> collidableObjects;
	Player *player;
	
	sf::Texture rockTexture;
};
