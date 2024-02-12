#include "player.h"

Player::Player(const float SIZE)
	: Tile(SIZE) 
	, direction() 
	, SPEED(600.f) 
	, animations() {

	importAnimations();
	setTexture(animations["down_idle"][0]);
}

void Player::update(float deltaTime) {
	getInput();
	move(deltaTime);
}

void Player::getInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
		direction.x = -1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
		direction.x = 1;
	else direction.x = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
		direction.y = -1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
		direction.y = 1;
	else direction.y = 0;
}

void Player::move(float deltaTime){
	if (direction.x != 0.0f && direction.y != 0.0f)
		direction /= sqrt(2.0f);

	sf::Vector2f velocity(direction * SPEED * deltaTime);
	hitbox.move(velocity);
	rect.setPosition(hitbox.getPosition() - rect.getSize() / 2.0f);
}

void Player::importAnimations() {
	std::string rootPath = "graphics/player/";
	std::vector<std::string> directories{
		"down", "left", "right", "up",
		"down_idle", "left_idle", "right_idle", "up_idle"
	};
	
	std::vector<sf::Texture> textures;
	for (const auto &directory : directories) {
		for (const auto &entry : std::filesystem::directory_iterator(rootPath + directory)) {
			sf::Texture texture;
			texture.loadFromFile(entry.path().string());
			textures.push_back(texture);
		}
		animations[directory] = textures;
	}
}