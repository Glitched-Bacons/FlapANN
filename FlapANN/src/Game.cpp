#include "pch.h"
#include "Game.h"

const sf::Time Game::TIME_PER_FRAME = sf::seconds(1.f / 60.f);
const float Game::SCREEN_WIDTH = 1280;
const float Game::SCREEN_HEIGHT = 720;


Game::Game():
	mGameWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "FlapANN", sf::Style::Titlebar | sf::Style::Close)
{
	// Limit the framerate to 60 frames per second
	mGameWindow.setFramerateLimit(60);
	mGameWindow.setKeyRepeatEnabled(false);

	// load resources
	loadResources();
}

void Game::run()
{
	// It controls the flow of the game loop
	// So the game is not framerate-dependent
	// so it works the same no matter what
	// performance has the player

	sf::Clock clock;
	auto frameTimeElapsed = sf::Time::Zero;
	while (mGameWindow.isOpen())
	{
		frameTimeElapsed += clock.restart();
		while (frameTimeElapsed > TIME_PER_FRAME)
		{
			// Update world no more than 60 frames per seconds
			frameTimeElapsed -= TIME_PER_FRAME;
			processEvents();
			update(TIME_PER_FRAME);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mGameWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mGameWindow.close();
		
		// process event there
	}
}

void Game::update(sf::Time deltaTime)
{
	// update game there
}

void Game::render()
{
	// before drawing anything clean
	// the previous frame
	mGameWindow.clear();

	// display the game there
	// ...

	// display to the window
	mGameWindow.display();
}


void Game::loadResources()
{
	mFonts.storeResource(Fonts_ID::ArialNarrow, "resources/Fonts/arial_narrow.ttf");
}