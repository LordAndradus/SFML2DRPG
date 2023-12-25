#include "Game.h"

//Initializer
void Game::initGameWindow()
{
	ifstream ifs("Config/Window.ini");

	if (!ifs.is_open())
	{
		filesystem::create_directory("Config");

		ofstream ofs("Config/Window.ini");

		if (ofs.is_open())
		{
			ofs << "2D RPG" << endl;
			ofs << 1920 << " " << 1080 << endl;
			ofs << 144 << endl;
			ofs << false << endl;

			ifs.open("Config/Window.ini");
		}
		else
		{
			printf("File could not be created.\n");
		}
	}

	string title = "None";
	sf::VideoMode window_bounds(1920, 1080);
	unsigned framerate_limit = 144;
	bool vertical_sync_enabled = false;

	if (ifs.is_open())
	{
		getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
	}

	printf("%s\n", title.c_str());
	printf("Window Size: (%d, %d)\n", window_bounds.width, window_bounds.height);
	printf("Framerate limit: %d\n", framerate_limit);
	printf("Vertical sync? %d\n", vertical_sync_enabled);

	this->window = new sf::RenderWindow(window_bounds, title);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
	this->states.push(new GameState(this->window));
}

//Construtor/Destructor
Game::Game()
{
	this->initGameWindow();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::endApplication()
{
	printf("Ending application.\n");
}

//Game Loop
void Game::updateDt()
{
	//Measures how long it takes for one frame to be generated using dt
	this->dt = this->dtClock.restart().asSeconds();

	//system("cls");
	//printf("%f\n", this->dt);
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed) this->window->close();
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			//TODO: Do stuff before quitting state
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	//End of application
	else
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	//Render stuff
	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
