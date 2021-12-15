#pragma once

#include <iostream>
#include <vector>
#include <list>

//Cryptor.cpp
class Encrypt
{
protected:
	static const int _key{ 45 };
	static const char _border{ '‹' };
	const std::string _path{ "Data.txt" };
	std::string _str;

	void crypt();
	void run();
public:
	void setStr(const std::string str);
	std::string str();

	void push(const std::string str);
	void clearFile();
	Encrypt(std::string str) : _str{ str } { run(); }
	Encrypt() :_str{} {}
	~Encrypt() {}
};

class Decrypt :Encrypt //наследование для использования ключа шифрования и пути к файлу
{
protected:
	std::vector <std::string> _dictionary{};
	void decode();
	std::vector<std::string>* reciveData();
public:
	void read();
	void showAll();
	
	std::string randWord();

	Decrypt() { read(); }
	~Decrypt() {}
};

//UserInterface.cpp
class Game
{
protected:
	const std::string _pass{ "1234" };
	std::list <std::string> _logo{};

	std::list <std::string> _banner{};
	int _time{};
	int _fails{};

	std::string _unCorrLetts{};
	std::string _corrLetts{};

	const std::string _start{ "Начать игру [1]" };

	const std::string _admin{ "Изменение словаря [0]" };
	void zeroing();
	
	std::string _word{};
public:
	bool isDone();
	std::string unCorrLetts();
	void setUnCorrLetts(char u);

	std::string corrLetts();
	void setCorrLetts(char u);

	void startLogo();
	void printGallows();
	void printGallows(int i);
	bool find(const char l, std::string& hide);

	void menu();
	void play();
	void statistic();
	void admin();

	void setWord(std::string word);

	Game();
	~Game();
	
};

