#include "collider.h"

Collider::Collider(sf::RectangleShape &rect) : rect(rect) {

}

void Collider::checkCollision(Collider other) {
	sf::Vector2f thisPosition = rect.getPosition();
	sf::Vector2f thisHalfSize = rect.getSize() / 2.0f;

	sf::Vector2f otherPosition = other.rect.getPosition();
	sf::Vector2f otherHalfSize = other.rect.getSize() / 2.0f;

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float overlapX = abs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
	float overlapY = abs(deltaY) - (thisHalfSize.y + otherHalfSize.y);

	if (overlapX < 0.0f && overlapY < 0.0f) {
		if (overlapX > overlapY) {
			if (deltaX < 0.0f) rect.move(-overlapX, 0.0f);
			else rect.move(overlapX, 0.0f);
			return;
		}

		if (deltaY < 0.0f) rect.move(0.0f, -overlapY);
		else rect.move(0.0f, overlapY);
		return;
	}
}