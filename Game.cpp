#include "Game.h"

//Utilities
string Game::openINI(const char* file)
{
	string path;

	char szPath[MAX_PATH + 1] = {};
	if (SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, SHGFP_TYPE_CURRENT, szPath) == S_OK)
	{
		path = szPath;
		path += "\\2D_RPG_GAME\\";
		filesystem::create_directory(path);
	}

#define iniString iniPath.c_str()

	string iniPath = path + file;

	ifstream ifs(iniString);

	if (!ifs.is_open())
	{
		ofstream ofs(iniString);

		if (ofs.is_open() && !strcmp("Window.ini", file))
		{
			ofs << "2D RPG" << endl;
			ofs << 1920 << " " << 1080 << endl;
			ofs << 144 << endl;
			ofs << false << endl;
		}
		else if (ofs.is_open() && !strcmp("Keybind.ini", file))
		{
			ofs << "A 0" << endl;
			ofs << "D 3" << endl;
			ofs << "W 22" << endl;
			ofs << "S 18" << endl;
			ofs << "Escape 36" << endl;
		}
		else
		{
			printf("File for %s could not be created.\n", file);
		}

		ofs.flush();
		ofs.close();
	}

#undef docString

	return iniPath;
}

//Initializers
void Game::initGameWindow()
{
	ifstream ifs;
	ifs.open(openINI("Window.ini").c_str());

	string title = "None";
	sf::VideoMode window_bounds(60, 60);
	unsigned framerate_limit = 144;
	bool vertical_sync_enabled = false;

	if (ifs.is_open())
	{
		getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
	}

	ifs.close();

	printf("%s\n", title.c_str());
	printf("Window Size: (%d, %d)\n", window_bounds.width, window_bounds.height);
	printf("Framerate limit: %d\n", framerate_limit);
	printf("Vertical sync? %d\n", vertical_sync_enabled);

	this->window = new sf::RenderWindow(window_bounds, title);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
{
	ifstream ifs(openINI("Keybind.ini"));

	if (ifs.is_open())
	{
		string key = "";
		int keyVal = 0;

		while (ifs >> key >> keyVal)
		{
			this->supportedKeys[key] = keyVal;
		}

		ifs.close();
	}

	//DEBUG
	for (auto i : this->supportedKeys) cout << "Key: " << i.first << " | ID: " << i.second << "\n";
}

void Game::initStates()
{
	this->states.push(new GameState(this->window, &this->supportedKeys));
}

//Construtor/Destructor
Game::Game()
{
	this->initGameWindow();

	this->initKeys();

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
