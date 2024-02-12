#pragma once
#include <tile.h>
#include <map>
#include <vector>
#include <filesystem>

class Player : public Tile {
public:
	Player(const float SIZE);
	void update(float deltaTime);

private:
	void getInput();
	void move(float deltaTime);
	void importAnimations();

private:
	sf::Vector2f direction;
	const float SPEED;

	std::map<std::string, std::vector<sf::Texture>> animations;
};
