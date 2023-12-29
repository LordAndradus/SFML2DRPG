#include "GameState.h"

void GameState::initKeybinds()
{
	string path;

	char szPath[MAX_PATH + 1] = {};
	if (SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, SHGFP_TYPE_CURRENT, szPath) == S_OK)
	{
		path = szPath;
		path += "\\2D_RPG_GAME\\";
	}

	string iniPath = path + "GameState_Keybind.ini";

	ifstream ifs(iniPath);

	if (!ifs.is_open())
	{
		ofstream ofs(iniPath);

		if (ofs.is_open())
		{
			ofs << "QUIT Escape" << endl;
			ofs << "MOVE_UP W" << endl;
			ofs << "MOVE_DOWN S" << endl;
			ofs << "MOVE_LEFT A" << endl;
			ofs << "MOVE_RIGHT D" << endl;

			ifs.open(iniPath);
		}
		else
		{
			printf("File for %s could not be created.\n", iniPath.c_str());
		}

		ofs.flush();
		ofs.close();
	}

	if (ifs.is_open())
	{
		string keyAction = "";
		string keyLetter = "";

		while (ifs >> keyAction >> keyLetter)
		{
			this->keybinds[keyAction] = this->supportedKeys->at(keyLetter);
		}

		ifs.close();
	}
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/Player Spritesheet.png"))
		throw("ERROR::GAMESTATE::COULD_NOT_LOAD_PLAYER_TEXTURE");
}

void GameState::initPlayer()
{
	this->player = new Player(window->getPosition().x / 2, window->getPosition().y / 2, this->textures["PLAYER_SHEET"]);
}

//Constructor & Destructor
GameState::GameState(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initTextures();
	this->initPlayer();
}

GameState::~GameState()
{
	delete this->player;
}

void GameState::updateInput(const float& dt)
{

#define MOVE_PARAM(s) if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at(s))))
#define MOVE_COORD(x, y) this->player->move(dt, x, y)
#define moveAmount 1.f

	//Update player input
	MOVE_PARAM("MOVE_LEFT")
	{
		MOVE_COORD(-moveAmount, 0.f);
	}	
	
	MOVE_PARAM("MOVE_RIGHT")
	{
		MOVE_COORD(moveAmount, 0.f);
	}	
	
	MOVE_PARAM("MOVE_UP")
	{
		MOVE_COORD(0.f, -moveAmount);
	}	
	
	MOVE_PARAM("MOVE_DOWN")
	{
		MOVE_COORD(0.f, moveAmount);
	}

	MOVE_PARAM("QUIT") this->endState();

#undef MOVE_PARAM
#undef MOVE_COORD
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	
	this->player->update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target) target = this->window;

	this->player->render(target);
}