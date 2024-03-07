#include "game.h"

Game::Game()
	: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TopDown Controller", sf::Style::Close) 
	, view(sf::Vector2f(), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)) 
	, visibleObjects{} 
	, collidableObjects{}
	, player(new Player(TILE_SIZE)) {
	
	rockTexture.loadFromFile("graphics/objects/rock.png"); 
	setupLevel();
}

void Game::run(const float framesPerSecond) {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time TimePerFrame = sf::seconds(1.f / framesPerSecond);
	while (window.isOpen())
	{
		processEvents();
		bool canRender = false;
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			canRender = true;
			update(TimePerFrame);
		}
		if (canRender)
			render();
	}
}

void Game::processEvents() {
	sf::Event evnt;
	while (window.pollEvent(evnt)) {
		switch (evnt.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if (evnt.key.code == sf::Keyboard::Escape)
				window.close();
			break;
		}
	}
}

void Game::update(sf::Time time) {
	float deltaTime = time.asSeconds();

	player->update(deltaTime);
	for (const auto& obj : collidableObjects) {
		Collider&& playerCollider = std::move(player->getCollider());
		Collider&& tileCollider = std::move(obj->getCollider());
		playerCollider.checkCollision(tileCollider);
	}

	view.setCenter(player->getPosition());
	window.setView(view);

	sortRenderingOrder();
}

void Game::render() {
	window.clear();
	for (const auto& object : visibleObjects) 
		object->draw(window);
	window.display();
}

void Game::setupLevel() {
	for (size_t row = 0; row < map.size(); ++row) {
		for (size_t col = 0; col < map[row].size(); ++col) {
			float tileX = (float)col * TILE_SIZE;
			float tileY = (float)row * TILE_SIZE;

			if (map[col][row] == 'X') {
				Tile *rockTile = new Tile(TILE_SIZE);
				rockTile->setPosition(tileX, tileY);
				rockTile->setTexture(rockTexture);
				visibleObjects.push_back(rockTile);
				collidableObjects.push_back(rockTile);
			}
			else if (map[col][row] == 'P') {
				Player *playerObj = new Player(TILE_SIZE);
				playerObj->setPosition(tileX, tileY);
				visibleObjects.push_back(playerObj);
				this->player = playerObj;
			}
		}
	}
}
