#include "uitextfield.h"

UITextField::UITextField(std::string message, const char* font){
	_text = new UIText(font, 0.4);
	_text->center = false;
	_text->message = message;
	this->add(_text);
}

UITextField::~UITextField(){
	delete _text;
}

void UITextField::update(){
}

UIText * UITextField::text(){
	return _text;
}
