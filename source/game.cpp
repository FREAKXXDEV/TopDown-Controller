#include "game.h"

Game::Game()
	: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TopDown Controller", sf::Style::Close) 
	, view(sf::Vector2f(), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)) 
	, visibleObjects{} 
	, collidableObjects{}
	, player(new Player(TILE_SIZE)) {
	
	rockTexture.loadFromFile("graphics/tilesets/rock.png"); 
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
	for (int col = 0; col < COLUMNS; ++col) {
		for (int row = 0; row < ROWS; ++row) {
			float tileX = (float)row * TILE_SIZE;
			float tileY = (float)col * TILE_SIZE;

			if (map[col][row] == 'x') {
				Tile *rockTile = new Tile(TILE_SIZE);
				rockTile->setPosition(tileX, tileY);
				rockTile->setTexture(rockTexture);
				visibleObjects.push_back(rockTile);  
				collidableObjects.push_back(rockTile);  
			}
			else if (map[col][row] == 'p') {
				Player *playerObj = new Player(TILE_SIZE);
				playerObj->setPosition(tileX, tileY);
				visibleObjects.push_back(playerObj); 
				this->player = playerObj;
			}
		}
	}
}

void Game::sortRenderingOrder() {
	std::sort(visibleObjects.begin(), visibleObjects.end(), TilePositionComparator());
}

bool Game::TilePositionComparator::operator()(Tile *tile1, Tile *tile2) {
	return tile1->getPosition().y < tile2->getPosition().y;
}
