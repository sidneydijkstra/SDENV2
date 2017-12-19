#include "player.h"

Player::Player(){
	this->mesh()->loadQuad();
	this->scale = glm::vec3(20, 50, 0);
	this->position = glm::vec3(SWIDTH/2, SHEIGHT/2, 0);

	this->addSpriteAnimator();
	std::vector<const char*> locations = {
		"assets/animations/charackters/characters_37.png",
		"assets/animations/charackters/characters_38.png",
		"assets/animations/charackters/characters_39.png",
		"assets/animations/charackters/characters_40.png",
		"assets/animations/charackters/characters_41.png",
	};
	this->spriteAnimator()->setAnimations(locations, 0.3f, 0, 0);

	velocity = glm::vec3(0.0f);
	acceleration = glm::vec3(0.0f);
}

Player::~Player()
{
}

void Player::update(float deltatime, std::vector<Tile*> t){

	this->spriteAnimator()->update();

	// jump
	float jump = 0;
	if (input()->getKeyDown(GLFW_KEY_SPACE)) {
		jump = 12;
	}

	// grafity
	this->acceleration.y = -9.9f;

	// movement
	if (this->input()->getKey(GLFW_KEY_A)) {
		this->velocity.x = -4;
	}else if(this->input()->getKey(GLFW_KEY_D)){
		this->velocity.x = 4;
	}else {
		this->velocity.x = 0;
	}


	// collision loop
	glm::vec3 temp = this->position; // save start pos
	this->position += velocity * 40.0f * deltatime;
	bool didCol = false;
	for (int i = 0; i < t.size(); i++){
		
		// check collision for each tile
		if (t[i]->collision(this)) {
			didCol = true;

			if (t[i]->leftCollision(this) && !t[i]->topCollision(this) || t[i]->rightCollision(this) && !t[i]->topCollision(this)) {
				this->position.x -= velocity.x * 40.0f * deltatime;
				this->velocity.x = 0;
				jump = 0;
			}

			if (t[i]->topCollision(this) && !t[i]->leftCollision(this) && !t[i]->rightCollision(this)) {
				this->velocity.y = 0;
				this->acceleration.y = 0;
			}else if(t[i]->bottomCollision(this) && !t[i]->leftCollision(this) && !t[i]->rightCollision(this)){
				this->velocity.y = 0;
			}
		}
	}
	this->position = temp; // set saved start pos as normal
	 
	// only do if can jump
	if (didCol && jump == 12) {
		this->velocity.y = jump;
	}

	// move player
	this->velocity += acceleration * deltatime;
	this->position += velocity * 40.0f * deltatime;

	//std::cout << "X: " << this->velocity.x << " Y: "<< this->velocity.y << std::endl;

	glm::clamp(this->velocity, glm::vec3(4.0f), glm::vec3(4.0f));

	this->acceleration *= 0;
}
 