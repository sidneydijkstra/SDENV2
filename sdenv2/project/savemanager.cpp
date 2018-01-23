#include "savemanager.h"

SaveManager* SaveManager::instance = NULL;


SaveManager::SaveManager(){
	_saveFileLocation = "assets/save.sfm";
}

std::vector<std::string> SaveManager::split(const std::string & string, char delim){
	std::vector<std::string> result;
	std::stringstream sstream(string);

	std::string word = "";
	while (std::getline(sstream, word, delim)) {
		result.push_back(word);
	}

	return result;
}

std::string SaveManager::build(std::vector<std::string> stringList, char delim) {
	if (stringList.empty()) {
		return NULL;
	}

	std::string result = "";
	int indexSize = stringList.size();
	for (int i = 0; i < indexSize; i++){
		result += stringList[i];

		if(indexSize - 1 != i){
			result += delim;
		}
	}

	return result;
}

SaveManager* SaveManager::getInstance(){
	if (instance == NULL)
	{
		std::cout << "instance of input made!" << std::endl;
		instance = new SaveManager();
	}

	return instance;
}

void SaveManager::init(){
	std::ifstream saveFile(SaveManager::getInstance()->_saveFileLocation);

	if (saveFile.is_open()) {
		std::string line;
		while (std::getline(saveFile, line)){
			SaveManager::getInstance()->_saveFileLines.push_back(line);
		}

		saveFile.close();

		std::cout << "[SAVEMANAGER] Loaded save file" << std::endl;
		SaveManager::getInstance()->_loadedSaveFile = true;
		saveFile.close();
		return;
	}else {
		std::cout << "[SAVEMANAGER] Could not load save file" << std::endl;
		SaveManager::getInstance()->_loadedSaveFile = false;
		return;
	}
}

void SaveManager::close(){
	std::ofstream saveFile("assets/save.sfm");
	if (saveFile.is_open()){
		std::vector<std::string> _lines = SaveManager::getInstance()->_saveFileLines;
		for (int i = 0; i < _lines.size(); i++){
			saveFile << _lines[i] + "\n";
		}

		std::cout << "[SAVEMANAGER] Saved save file" << std::endl;
		saveFile.close();
		return;
	}else {
		std::cout << "[SAVEMANAGER] Could not save save file" << std::endl;
		return;
	}
}

void SaveManager::setValue(std::string _key, std::string _value)
{
	if (!SaveManager::getInstance()->_loadedSaveFile) {
		std::cout << "[SAVEMANAGER] Can't set value because save file is not loaded" << std::endl;
		return;
	}

	std::vector<std::string> _lines = SaveManager::getInstance()->_saveFileLines;
	for (int i = 0; i < _lines.size(); i++)
	{
		std::vector<std::string> line = SaveManager::getInstance()->split(_lines[i], ","[0]);

		if (line.empty()) {
			continue;
		}

		// if current line is save key save new value and return
		if(line[0] == _key){
			line[1] = _value;
			_lines[i] = SaveManager::getInstance()->build(line, ","[0]);
			SaveManager::getInstance()->_saveFileLines = _lines;
			return;
		}
	}

	std::string newSaveObject = _key;
	newSaveObject += ",";
	newSaveObject += _value;
	_lines.push_back(newSaveObject);
	SaveManager::getInstance()->_saveFileLines = _lines;
}

void SaveManager::getValue(std::string _key, std::string _value)
{
	// TODO
}

SaveManager::~SaveManager()
{
}
