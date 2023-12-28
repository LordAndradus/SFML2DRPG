#include "MainMenuState.h"
#include "Button.h"

void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(
	static_cast<float> (this->window->getSize().x), 
	static_cast<float> (this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("Backgrounds/Main Menu.png"))
		throw("ERROR::MAINMENMUSTATE::FAILED to load texture \"Backgrounds/Main Menu.png\"");
	
	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/arial.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULDN'T LOAD FONT 'arial.tff'");
	}
}

void MainMenuState::initKeybinds()
{
	string path;

	char szPath[MAX_PATH + 1] = {};
	if (SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, SHGFP_TYPE_CURRENT, szPath) == S_OK)
	{
		path = szPath;
		path += "\\2D_RPG_GAME\\";
	}

	string iniPath = path + "MainMenuState_Keybind.ini";

	ifstream ifs(iniPath);

	if (!ifs.is_open())
	{
		ofstream ofs(iniPath);

		if (ofs.is_open())
		{
			ofs << "QUIT Escape" << endl;

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

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(450, 500, 300, 100, &this->font,
		"New Game", sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));	
	
	this->buttons["SETTINGS_STATE"] = new Button(450, 650, 300, 100, &this->font,
		"Settings", sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["QUIT_STATE"] = new Button(450, 800, 300, 100, &this->font,
		"Quit", sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	auto i = this->buttons.begin();
	for (i = i; i != this->buttons.end(); ++i)
	{
		delete i->second;
	}
}

void MainMenuState::endState()
{
	printf("MainMenuState is ending\n");
}

void MainMenuState::updateInput(const float& dt)
{
	this->checkForQuit();
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();

	static float time = 1;
	static float pile = 0;
	static bool printedScreen = false;

	pile += dt;

	if (pile >= time)
	{
		//system("cls");
		cout << "\x1b[A";
		cout << "\x1b[2K";
		printedScreen = false;
		pile -= time;
	}
	if (pile <= time && !printedScreen)
	{
		printedScreen = true;
		cout << "(" << this->mousePosView.x << ", " << this->mousePosView.y << ")" << endl;
	}
}

void MainMenuState::updateButtons()
{
	//Updates all buttons in the main menu
	for (auto it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//Handles the functionalities
	if (this->buttons["QUIT_STATE"]->isActive()) this->quit = true;

	if (this->buttons["GAME_STATE"]->isActive())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target) target = this->window;

	target->draw(this->background);

	this->renderButtons(target);

	sf::Text mouseText;
	mouseText.setPosition(sf::Vector2f(mousePosView.x + 20, mousePosView.y - 20));
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(24);

	stringstream ss;
	ss << "(" << this->mousePosView.x << ", " << this->mousePosView.y << ")" << endl;
	mouseText.setString(ss.str());

	target->draw(mouseText);
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto it : this->buttons)
	{
		it.second->render(target);
	}
}
