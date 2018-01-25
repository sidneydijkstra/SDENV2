#include "editorsaver.h"

EditorSaver::EditorSaver(){
}

EditorSaver::~EditorSaver(){
}

void EditorSaver::saveNewFile(std::string data){
	std::ofstream fs("assets/map.es");

	if (!fs){
		std::cerr << "Cannot open save file." << std::endl;
		return;
	}

	fs.clear();

	fs << data;

	fs.close();
}

std::string EditorSaver::openSaveFile(){
	std::ifstream file("assets/map.es");

	if (file.is_open()) {
		std::string line;
		std::string data;
		while (std::getline(file, line)) {
			data = line;
			break;
		}

		file.close();

		return line;
	}

	return "";
}
