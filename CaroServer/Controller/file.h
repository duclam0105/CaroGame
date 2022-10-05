#pragma once

#include ".\..\Lib.h"
#include ".\..\Model\Player.h"

class file {
private:
	const char* INI_FILE = "PLAYER_DB.ini";
	string section = "PLAYER DATABASE:";
	string Path = "F:\\Microsoft Visual Studio\\Project\\Caro_TCP_IP\\CaroGame_server\\Controller\\PLAYER_DB.ini";
public:
	void setDirection(const string&);
	string getDirection();
	bool writeFile(const string&, const string&);
	string findInFile(const string&);
	vector<string> readFile();
	vector<Player> loadDataToDB();
};

