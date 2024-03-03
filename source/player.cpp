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
	bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

	/*
	* the ^ operator only returns true if one of the two values provided is true
	* if none of them or both of them are true at the same time it returns false
	*/

	/*
	* the ? operator is a single line if else statement
	* if the given value before the ? is true then the the code next to the ? will be executed
	* the else condition is to be separated with a : which will execute if the given value is false
	*/

	if (!(left ^ right))
		direction.x = 0.f;
	else {
		direction.x = left ? -1.f : 1.f;
		status = left ? "left" : "right";
	}

	if (!(up ^ down))
		direction.y = 0.f;
	else if (up ^ down) {
		direction.y = up ? -1.f : 1.f; 
		status = up ? "up" : "down";
	}
}

void Player::move(float deltaTime){
	if (direction.x != 0.0f && direction.y != 0.0f) {
		/*
		* A² + B² = C²
		* Common Pythagoras Theorem W 
		*/

		float normalizedLength = sqrtf(powf(direction.x, 2) + powf(direction.y, 2));
		direction /= normalizedLength;
	}

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
