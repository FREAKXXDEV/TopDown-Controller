#pragma once
#include <SFML/Graphics.hpp>

class Collider {
public:
	Collider(sf::RectangleShape &rect);
	void checkCollision(Collider other);

private:
	sf::RectangleShape &rect;
};