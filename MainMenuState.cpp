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

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/Main Menu.png"))
		throw("ERROR::MAINMENMUSTATE::FAILED to load texture \"Resources/Images/Backgrounds/Main Menu.png\"");
	
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
#define bWidth 300
#define bHeight 75
#define colorI	sf::Color(70, 70, 70, 0)
#define colorH	sf::Color(150, 150, 150, 0)
#define colorA	sf::Color(20, 20, 20, 0)
#define textI	sf::Color(70, 70, 70, 200)
#define textH	sf::Color(250, 250, 250, 250)
#define textA	sf::Color(20, 20, 20, 50)

#define buttonMake(x, y, s, fs) new Button(x, y, bWidth, bHeight, &this->font, s, fs, textI, textH, textA, colorI, colorH, colorA)

	this->buttons["GAME_STATE"] = buttonMake(450, 500, "New Game", 24);
	
	this->buttons["SETTINGS_STATE"] = buttonMake(450, 600, "Settings", 24);

	this->buttons["EDITOR_STATE"] = buttonMake(450, 700, "Editor", 24);

	this->buttons["QUIT_STATE"] = buttonMake(450, 800, "Quit", 24);

#undef bWidth
#undef bHeight
#undef colorI
#undef colorH
#undef colorA
#undef textI
#undef textH
#undef textA
#undef buttonMake
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

void MainMenuState::updateInput(const float& dt)
{
	
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
	if (this->buttons["QUIT_STATE"]->isActive()) this->endState();

	if (this->buttons["GAME_STATE"]->isActive())
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	
	if (this->buttons["EDITOR_STATE"]->isActive())
		this->states->push(new EditorState(this->window, this->supportedKeys, this->states));
	
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target) target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);

	sf::Text mouseText;
	mouseText.setPosition(sf::Vector2f(mousePosView.x + 20, mousePosView.y - 20));
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(24);

	stringstream ss;
	ss << "(" << this->mousePosView.x << ", " << this->mousePosView.y << ")" << endl;
	mouseText.setString(ss.str());

	target->draw(mouseText);
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto it : this->buttons)
	{
		it.second->render(target);
	}
}
