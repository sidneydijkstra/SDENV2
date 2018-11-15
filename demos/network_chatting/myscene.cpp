#include "myscene.h"


MyScene::MyScene(){
	this->setSceneMode(SCENE2D); // <-- set scene mode
	_messages = std::vector<UITextField*>();

	_canvas = new Canvas();
	this->addCanvas(_canvas);

	_message = new UITextField("Welcome to Network Chatting. Connect to the server and try it out!");
	_message->text()->center = true;
	_message->position = _canvas->center();

	_button = new UIButton(Color(100, 100, 100), Color(150, 150, 150), Color(200, 200, 200));
	_button->position = _canvas->center() - glm::vec3(0, 100, 0);

	_input = new UITextField("");
	_input->text()->center = true;
	_input->position = _canvas->center() - glm::vec3(0, 100, 0);

	_canvas->addChild(_message);
	_canvas->addChild(_button);

	// setup packages
	p_sendMessage = new Package("SMESSAGE");

	// setup network actions
	NetworkHandler::getInstance()->listen("SMESSAGE", [this](Package _pack) { // on receive [send message]
		displayMessage(_pack);
	});
	
}	

void MyScene::update(float deltatime) {
	NetworkManager::getInstance()->update(); // <-- TODO: check in main loop if network is user or activate it in scene and than call update automaticly!

	_canvas->update();
	_button->update();
	if (_button->OnClick()) {
		_message->text()->message = "connecting to server: IP: 127.0.0.1 PORT: 8001";
		if (NetworkManager::getInstance()->init(IpAddress("127.0.0.1"), 8001)) {
			_message->text()->message = "connected to server: IP: 127.0.0.1 PORT: 8001";
			connected();
		}
		else {
			_message->text()->message = "could not connect to server: IP: 127.0.0.1 PORT: 8001";
		}
	}

	if (NetworkHandler::getInstance()->isRunning()) {
		getInput();
	}
}

void MyScene::connected(){
	_canvas->removeChild(_message);
	_canvas->removeChild(_button);
	_canvas->addChild(_input);

	p_sendMessage->set("username", std::string("test tesst"));

	_messages.clear();
}

void MyScene::getInput(){
	if (Input::getKeyDown(GLFW_KEY_ENTER)) {
		sendMessage(_input->text()->message);
		_input->text()->message = "";
		return;
	}
	if (Input::getKeyDown(GLFW_KEY_BACKSPACE)) {
		if (_input->text()->message.empty())
			return;

		_input->text()->message.erase(_input->text()->message.end() - 1);
		return;
	}

	for (size_t i = 0; i < GLFW_KEY_LAST; i++){
		if (Input::getKeyDown(i)) {
			char key = (char)i;
			_input->text()->message += key;
		}
	}
	
}

void MyScene::sendMessage(std::string _message){
	p_sendMessage->set("username", std::string(_message));
	NetworkHandler::getInstance()->send(*p_sendMessage);
}

void MyScene::displayMessage(Package _pack){

	if (_messages.size() > 10) {
		UITextField* field = _messages[0];
		_messages.erase(_messages.begin());
		_canvas->removeChild(field);
		delete field;
	}

	for (int i = _messages.size()-1; i >= 0 ; i--){
		_messages[i]->position = _canvas->center() + glm::vec3(0, (i+1) * 30, 0);
	}

	UITextField* temp = new UITextField(_pack.getString("username"));
	temp->text()->center = true;
	temp->position = _canvas->center() + glm::vec3(0, 0, 0);

	_canvas->addChild(temp);
	_messages.push_back(temp);

	std::cout << temp->position.x << "/" << temp->position.y << _pack.getString("username") << std::endl;
}

MyScene::~MyScene(){
	delete _message;
	delete _button;
	delete _input;
	_messages.clear();
	delete _canvas;
}

