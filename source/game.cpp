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
		}
	}
}

void Game::update(sf::Time time) {
	float deltaTime = time.asSeconds();

	player->update(deltaTime);
	for (auto it = collidableObjects.begin(); it != collidableObjects.end(); ++it) {
		Collider playerCollider = player->getCollider();
		Collider tileCollider = (*it)->getCollider();
		playerCollider.checkCollision(tileCollider);
	}
		
	view.setCenter(player->getPosition());
	window.setView(view);

	sortRenderingOrder();
}

void Game::render() {
	window.clear();

	for (auto it = visibleObjects.begin(); it != visibleObjects.end(); ++it)
		(*it)->draw(window);
	window.display();
}

void Game::setupLevel() {
	for (int i = 0; i < COLUMNS; ++i) {
		for (int j = 0; j < ROWS; ++j) {
			float x = (float)j * TILE_SIZE;
			float y = (float)i * TILE_SIZE;

			if (map[i][j] == 'x') {
				Tile *tile = new Tile(TILE_SIZE);
				tile->setPosition(x, y);
				tile->setTexture(rockTexture);
				visibleObjects.push_back(tile);
				collidableObjects.push_back(tile);
			}
			else if (map[i][j] == 'p') {
				Player *player = new Player(TILE_SIZE);
				player->setPosition(x, y);
				visibleObjects.push_back(player);
				this->player = player;
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
