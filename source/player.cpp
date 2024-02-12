#include "player.h"

Player::Player(const float SIZE)
	: Tile(SIZE) 
	, direction() 
	, SPEED(600.f) {

}

void Player::update(float deltaTime) {
	getInput();
	move(deltaTime);
}

void Player::getInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction.x = -1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction.x = 1;
	else direction.x = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y = -1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y = 1;
	else direction.y = 0;
}

void Player::move(float deltaTime) {
	if (direction.x != 0.0f && direction.y != 0.0f)
		direction /= sqrt(2.0f);

	sf::Vector2f velocity(direction * SPEED * deltaTime);
	hitbox.move(velocity);
	rect.setPosition(hitbox.getPosition() - rect.getSize() / 2.0f);
}