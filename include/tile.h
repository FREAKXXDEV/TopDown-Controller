#pragma once
#include <SFML/Graphics.hpp>
#include <collider.h>

class Tile {
public:
	Tile(const float TILE_SIZE);
	void draw(sf::RenderWindow &window);

	void setPosition(float x, float y) {
		rect.setPosition(x, y); 
		hitbox.setPosition(getPosition()); 
	}
	void setTexture(sf::Texture &texture) { rect.setTexture(&texture); }

	sf::Vector2f getPosition() { return rect.getPosition() + rect.getSize() / 2.0f; }
	Collider getCollider() { return Collider(hitbox); }

protected:
	sf::RectangleShape rect;
	sf::RectangleShape hitbox;
};
