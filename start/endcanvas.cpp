#include "endcanvas.h"

EndCanvas::EndCanvas(){
	_back = new UIButton(Color(100, 100, 100), Color(120, 120, 120), Color(140, 140, 140));
	_back->position = glm::vec3(SWIDTH / 2, 400, 0);
	_back->setButtonText("<-- back");
	this->addChild(_back);

	_title = new UITextField("HighScores:", "");
	_title->position = glm::vec3(SWIDTH / 2, 600, 0);
	_title->text()->center = true;
	this->addChild(_title);

	_highscore1 = new UITextField("message", "");
	_highscore1->position = glm::vec3(SWIDTH / 2, 570, 0);
	_highscore1->text()->center = true;
	this->addChild(_highscore1);

	_highscore2 = new UITextField("message", "");
	_highscore2->position = glm::vec3(SWIDTH / 2, 540, 0);
	_highscore2->text()->center = true;
	this->addChild(_highscore2);

	_highscore3 = new UITextField("message", "");
	_highscore3->position = glm::vec3(SWIDTH / 2, 510, 0);
	_highscore3->text()->center = true;
	this->addChild(_highscore3);

	_highscore4 = new UITextField("message", "");
	_highscore4->position = glm::vec3(SWIDTH / 2, 490, 0);
	_highscore4->text()->center = true;
	this->addChild(_highscore4);

	_highscore5 = new UITextField("message", "");
	_highscore5->position = glm::vec3(SWIDTH / 2, 460, 0);
	_highscore5->text()->center = true;
	this->addChild(_highscore5);

	for (int i = 0; i < 5; i++) {
		std::string value = SaveManager::getInstance()->getValue("HIGHSCORE_" + std::to_string(i));
		if (value == "") {
			SaveManager::getInstance()->setValue("HIGHSCORE_" + std::to_string(i), "100000.0");
			value = "1000000.0";
		}
	}
}

EndCanvas::~EndCanvas(){
	delete _back;

	delete _title;
	delete _highscore1;
	delete _highscore2;
	delete _highscore3;
	delete _highscore4;
	delete _highscore5;
}

void EndCanvas::update(){
}

void EndCanvas::loadScore(){
	float time = std::stod(SaveManager::getInstance()->getValue("LEVEL_TIMER"));
	for (int i = 0; i < 5; i++){
		std::string value = SaveManager::getInstance()->getValue("HIGHSCORE_" + std::to_string(i));
		if (value == "") {
			SaveManager::getInstance()->setValue("HIGHSCORE_" + std::to_string(i), "100000.0");
			value = "1000000.0";
		}

		float score = std::stod(value);
		if (time < score) {
			SaveManager::getInstance()->setValue("HIGHSCORE_" + std::to_string(i), std::to_string(time));
			_title->text()->message = "HighScores: [You got placed number " + std::to_string(i+1) + " nice!]";
			this->updateText();
			return;
		}
	}
	_title->text()->message = "HighScores:";
	this->updateText();
}

void EndCanvas::updateText(){
	_highscore1->text()->message = "1. " + SaveManager::getInstance()->getValue("HIGHSCORE_0") + " seconds";
	_highscore2->text()->message = "2. " + SaveManager::getInstance()->getValue("HIGHSCORE_1") + " seconds";
	_highscore3->text()->message = "3. " + SaveManager::getInstance()->getValue("HIGHSCORE_2") + " seconds";
	_highscore4->text()->message = "4. " + SaveManager::getInstance()->getValue("HIGHSCORE_3") + " seconds";
	_highscore5->text()->message = "5. " + SaveManager::getInstance()->getValue("HIGHSCORE_4") + " seconds";
}
