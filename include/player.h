#pragma once
#include <tile.h>

class Player : public Tile {
public:
	Player(const float SIZE);
	void update(float deltaTime);

private:
	void getInput();
	void move(float deltaTime);

private:
	sf::Vector2f direction;
	const float SPEED;
};
