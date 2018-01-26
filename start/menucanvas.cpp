#include "menucanvas.h"

MenuCanvas::MenuCanvas(){

	_title = new UITextField("MirrorRace", "");
	_title->position = glm::vec3(SWIDTH / 2, 700, 0);
	_title->text()->center = true;
	this->addChild(_title);

	_start = new UIButton(Color(100, 100, 100), Color(120, 120, 120), Color(140, 140, 140));
	_start->position = glm::vec3(SWIDTH / 2, 650, 0);
	_start->setButtonText("Start");
	this->addChild(_start);

	_tutorialA = new UITextField("You can move using [A] and [D] for left and right and [SPACE] to jump.", "");
	_tutorialA->position = glm::vec3(SWIDTH / 2, 570, 0);
	_tutorialA->text()->center = true;
	this->addChild(_tutorialA);

	_tutorialB = new UITextField("In the level, watch out for the snakes and search for the black and white end tile.", "");
	_tutorialB->position = glm::vec3(SWIDTH / 2 - 50, 540, 0);
	_tutorialB->text()->center = true;
	this->addChild(_tutorialB);

	_tutorialC = new UITextField("you have two display's in each display there is a part of the world use both to navigate.", "");
	_tutorialC->position = glm::vec3(SWIDTH / 2 - 70, 510, 0);
	_tutorialC->text()->center = true;
	this->addChild(_tutorialC);

	_creditArt = new UITextField("Art by Bunch http://blog-buch.rhcloud.com", "");
	_creditArt->position = glm::vec3(SWIDTH / 2, 450, 0);
	_creditArt->text()->center = true;
	this->addChild(_creditArt);

	_creditDev = new UITextField("Programmed by Sidney Dijkstra", "");
	_creditDev->position = glm::vec3(SWIDTH / 2, 420, 0);
	_creditDev->text()->center = true;
	this->addChild(_creditDev);
}

MenuCanvas::~MenuCanvas()
{
	delete _title;
	delete _start;
	delete _tutorialA;
	delete _tutorialB;
	delete _tutorialC;
	delete _creditArt;
	delete _creditDev;
}

void MenuCanvas::update()
{
}
