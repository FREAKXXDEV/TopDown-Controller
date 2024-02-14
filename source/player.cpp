#include "player.h"

Player::Player(const float SIZE)
	: Tile(SIZE) 
	, direction() 
	, SPEED(400.f) 
	, animations()
	, status("down_idle")
	, frameIndex()
	, ANIMATION_SPEED(4.8f) {

	importAssets();
	rect.setTexture(&animations[status][(int)frameIndex]);
}

void Player::update(float deltaTime) {
	getInput();
	move(deltaTime);
	animate(deltaTime);
}

void Player::getInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		direction.x = -1;
		status = "left";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		direction.x = 1;
		status = "right";
	}
	else direction.x = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		direction.y = -1;
		status = "up";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		direction.y = 1;
		status = "down";
	}
	else direction.y = 0;
}

void Player::move(float deltaTime){
	if (direction.x != 0.0f && direction.y != 0.0f)
		direction /= sqrt(2.0f);

	sf::Vector2f velocity(direction * SPEED * deltaTime);
	hitbox.move(velocity);
	rect.setPosition(hitbox.getPosition() - rect.getSize() / 2.0f);
}

void Player::importAssets() {
	std::string rootDirectory = "graphics\\player\\";
	std::vector<std::string> subDirectories;
	for (const auto &entry : std::filesystem::directory_iterator(rootDirectory)) {
		if (entry.is_directory())
			subDirectories.push_back(entry.path().filename().string());
	}

	for (const auto &subDir : subDirectories) {
		std::vector<sf::Texture> textures;
		for (const auto &entry : std::filesystem::directory_iterator(rootDirectory + subDir)) {
			sf::Texture texture;
			texture.loadFromFile(entry.path().string());
			textures.push_back(texture);
		}

		animations[subDir] = textures;
	}
}

void Player::animate(float deltaTime) {
	if (direction.x == 0.0f && direction.y == 0.0f) {
		if (status.find("idle") == std::string::npos)
			status += "_idle";
	}

	frameIndex += ANIMATION_SPEED * deltaTime;
	if (frameIndex > animations[status].size())
		frameIndex = 0.0f;

	rect.setTexture(&animations[status][(int)frameIndex]);
}
