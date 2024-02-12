#pragma once
#include <tile.h>
#include <filesystem>
#include <iostream>

class Player : public Tile {
public:
	Player(const float SIZE);
	void update(float deltaTime);

private:
	void getInput();
	void move(float deltaTime);
	void importAssets();
	void animate(float deltaTime);

private:
	sf::Vector2f direction;
	const float SPEED;

	std::string status;
	float frameIndex;
	const float ANIMATION_SPEED;
	std::map<std::string, std::vector<sf::Texture>> animations;
};
