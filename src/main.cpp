#include <iostream>
#include <filesystem>
#include <fstream>

#include "textureArray.hpp"
#include "Logic.hpp"
#include "windowSettings.hpp"


void gameMenu(int &gewonnen, int &verloren);
void initializeStats(int&, int&);
void saveStats(int&, int&);
std::string get_userpath();

int main()
{
	int gewonnen{ 0 };
	int verloren{ 0 };

	// read stats from .txt files into variables
	initializeStats(gewonnen, verloren);

	myTextures::initTextures(textureArr, otherTextureArr);
	gameMenu(gewonnen, verloren);

	//read variables into .txt files
	saveStats(gewonnen, verloren);

	std::cout << "Tschuess!\n";

	return 0;
}


void initializeStats(int& gewonnen, int& verloren)
{

	std::string path{ get_userpath() };
	std::cout << "Initializing stats..\n";
	
	namespace fs = std::filesystem;

	fs::path dir = path + "/.MagyarKartya/stats"; 
	if (!fs::is_directory(dir) || !fs::exists(dir))
	{
		std::cout << "Did not find the directory, creating now..\n";
		fs::create_directories(dir);
	}

	std::fstream wins;
	wins.open(path + "/.MagyarKartya/stats/wins.txt");
	if (!wins)
		wins.open(path + "/.MagyarKartya/stats/wins.txt", std::ios::out);


	std::fstream loses;
	loses.open(path + "/.MagyarKartya/stats/loses.txt");
	if (!loses)
		loses.open(path + "/.MagyarKartya/stats/loses.txt", std::ios::out);


	if (wins.is_open() && loses.is_open())
	{
		wins >> gewonnen;
		wins.close();

		loses >> verloren;
		loses.close();

		std::cout << "Initialized.\n";
	}
	else
	{
		if (!wins.is_open())
			std::cout << "Couldn't open " << path + R"(\.MagyarKartya\stats\wins.txt")" << std::endl;
		else
			std::cout << "Couldn't open " << path  + R"(\.MagyarKartya\stats\loses.txt")" << std::endl;

		std::cout << "Failed to initialize stats.\n";
	}
}

void saveStats(int& gewonnen, int& verloren)
{
	std::string path{ get_userpath() };

	std::cout << "Saving..\n";

	std::ofstream wins;
	wins.open(path + "/.MagyarKartya/stats/wins.txt", std::ostream::out);

	std::ofstream loses;
	loses.open(path + "/.MagyarKartya/stats/loses.txt", std::ostream::out);

	if (wins.is_open() && loses.is_open())
	{
		wins << gewonnen;
		wins.close();

		loses << verloren;
		loses.close();

		std::cout << "Saved.\n";
	}
	else
	{
		if (!wins.is_open())
			std::cout << "Couldn't open " << path + R"(\.MagyarKartya\stats\wins.txt")" << std::endl;
		else
			std::cout << "Couldn't open " << path + R"(\.MagyarKartya\stats\loses.txt")" << std::endl;

		std::cout << "Failed to save.\n";
	}
}
