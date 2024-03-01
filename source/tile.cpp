#include "tile.h"

Tile::Tile(const float TILE_SIZE)
	: rect(sf::Vector2f(TILE_SIZE, TILE_SIZE))
	, hitbox(sf::Vector2f(TILE_SIZE, TILE_SIZE / 1.25f)) {

	hitbox.setOrigin(hitbox.getSize() / 2.0f);
}

void Tile::draw(sf::RenderWindow &window) {
	window.draw(rect);
}