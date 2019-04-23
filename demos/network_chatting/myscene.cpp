#include "myscene.h"


MyScene::MyScene(){
	this->setSceneMode(SCENE2D); // <-- set scene mode

	_canvas = new Canvas();
	this->addCanvas(_canvas);

	_message = new UITextField("Welcome to Network Chatting. Connect to the server and try it out!");
	_message->text()->center = true;
	_message->position = _canvas->center();

	_button = new UIButton(Color(100, 100, 100), Color(150, 150, 150), Color(200, 200, 200));
	_button->position = _canvas->center() - glm::vec3(0, 100, 0);

	_canvas->addChild(_message);
	_canvas->addChild(_button);

	_player == NULL;
	//_timer = Timer();
	

	// setup packages

	// setup network actions
	NetworkHandler::getInstance()->listen("INIT", [this](Package _pack) { // on receive [INIT]
		_canvas->removeChild(_message);
		_canvas->removeChild(_button);

		_player = new Player();
		this->addChild(_player);

		_networkPlayers = std::vector<Player*>();
		//_timer.start();

		p_updatePosition = new Package("g_update_position", _pack.getInt("network_id"));
		p_updatePosition->set("network_id", _pack.getInt("network_id"));
		std::cout << "network_id: " << _pack.getInt("network_id") << std::endl;
	});

	NetworkHandler::getInstance()->listen("CONNECT", [this](Package _pack) { // on receive [send message]
		std::cout << "connection with id: " << _pack.getInt("network_id") << std::endl;

		// add player to client lost
		Player* p = new Player();
		this->addChild(p);
		p->networkID = _pack.getInt("network_id");
		_networkPlayers.push_back(p);
	});

	NetworkHandler::getInstance()->listen("DISCONNECT", [this](Package _pack) { // on receive [send message]
		std::cout << "lost connection with id: " << _pack.getInt("network_id") << std::endl;

		// remove player from client list
		int id = _pack.getInt("network_id");
		for (int i = 0; i < _networkPlayers.size(); i++){
			if (_networkPlayers[i]->networkID == id) {
				this->removeChild(_networkPlayers[i]);
				_networkPlayers.erase(_networkPlayers.begin() + i);
				break;
			}
		}
	});

	NetworkHandler::getInstance()->listen("g_update_position", [this](Package _pack) { // on receive [send message]
		// update client position in list
		int id = _pack.getInt("network_id");
		for (int i = 0; i < _networkPlayers.size(); i++) {
			if (_networkPlayers[i]->networkID == id) {
				_networkPlayers[i]->position = glm::vec3(_pack.getFloat("position_x"), _pack.getFloat("position_y"), 0);
				break;
			}
		}
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
		}
		else {
			_message->text()->message = "could not connect to server: IP: 127.0.0.1 PORT: 8001";
		}
	}

	if (NetworkHandler::getInstance()->isRunning()) {
		_player->update(deltatime);
		//if (_timer.seconds() > 1) {
			p_updatePosition->set("position_x", _player->position.x);
			p_updatePosition->set("position_y", _player->position.y);
			NetworkHandler::getInstance()->send(*p_updatePosition);
			//_timer.start();
		//}
	}
}

void MyScene::connected(){
}

MyScene::~MyScene(){
	delete _message;
	delete _button;
	delete _canvas;
	if(_player != NULL)
		delete _player;
}

