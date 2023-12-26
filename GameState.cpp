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

GameState::GameState(sf::RenderWindow* window, map<string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	this->initKeybinds();
}

GameState::~GameState()
{
	
}

void GameState::endState()
{
	printf("GameState is ending\n");
}

void GameState::updateInput(const float& dt)
{
	this->checkForQuit();

#define MOVE_PARAM(s) if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at(s))))
#define MOVE_COORD(x, y) this->player.move(dt, x, y)

	//Update player input
	MOVE_PARAM("MOVE_LEFT")
	{
		MOVE_COORD(-1.f, 0.f);
	}	
	
	MOVE_PARAM("MOVE_RIGHT")
	{
		MOVE_COORD(1.f, 0.f);
	}	
	
	MOVE_PARAM("MOVE_UP")
	{
		MOVE_COORD(0.f, -1.f);
	}	
	
	MOVE_PARAM("MOVE_DOWN")
	{
		MOVE_COORD(0.f, 1.f);
	}

#undef MOVE_PARAM
#undef MOVE_COORD
}

void GameState::update(const float& dt)
{
	this->updateInput(dt);
	
	this->player.update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target) target = this->window;

	this->player.render(target);
}