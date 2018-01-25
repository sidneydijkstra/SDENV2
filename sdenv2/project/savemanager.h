/**
* @file savemanager.h
*
* @brief The SaveManager header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

/**
* @brief The SaveManager class
*/
class SaveManager
{
public:
	/// @brief get the Instance of the SaveManager
	/// @return SaveManager*
	static SaveManager* getInstance();
	~SaveManager(); ///< @brief Destructor of the SaveManager

	/// @brief initialize the SaveManager
	/// @return void
	static void init();
	static void close();

	static void setValue(std::string _key, std::string _value);
	static std::string getValue(std::string _key);

private:
	SaveManager(); ///< @brief Constructor of the SaveManager
	static SaveManager* instance; ///< @brief the main instance of the SaveManager

	const char* _saveFileLocation;
	std::vector<std::string> _saveFileLines;
	bool _loadedSaveFile;

	std::vector<std::string> split(const std::string &string, char delim);
	std::string build(std::vector<std::string> stringList, char delim);
}; 

#endif /* end SAVEMANAGER_H */