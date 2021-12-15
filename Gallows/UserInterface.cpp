#include <iostream>
#include "Header.h"



void Game::setWord(std::string word) { _word = word; }
void Game::menu()
{
	char l;
	
	while (true)
	{
		printGallows();
		std::cout << std::endl << _start;
		std::cout << std::endl << _admin << std::endl;
		std::cin >> l;
		switch (l)
		{
		case'1':
		{
			Decrypt obj{};
			setWord(obj.randWord());

			play();
			break;
		}
		case '0':
		{
			std::cout << "����� ��������������\n";
			admin();
			break;
		}
		default:
			std::cout << "������ ����������� ����� ����\n";
			continue;
		}
	}
}
void Game::printGallows(int i)
{
	
	system("cls");
	auto iter = _logo.begin();
	for (int j = 0; j < i; j++)
	{
		iter++;
	}
	std::cout << *iter;
	
}
void Game::printGallows()
{

	system("cls");
	std::cout << *_logo.rbegin();
	for (auto iter = _banner.begin(); iter != _banner.end(); ++iter)
	{
		std::cout << *iter;
	}

}
void Game::startLogo()
{
	auto end = _logo.end();
	for (auto iter = _logo.begin(); iter != end; ++iter)
	{
		for (int i = 0; i < 5; i++)
		{
			std::cout << *iter;
			system("cls");
		}
	}

	std::cout << *_logo.rbegin();

	for (auto iter = _banner.begin(); iter != _banner.end(); ++iter)
	{
		std::cout << *iter;
	}
	
}



std::string Game::unCorrLetts() { return _unCorrLetts; }
void Game::setUnCorrLetts(char u) { _unCorrLetts = u; }

std::string Game::corrLetts() { return _corrLetts; }
void Game::setCorrLetts(char u) { _corrLetts = u; }
bool Game::isDone()
{
	if (_fails==_logo.size() ||
		_word.size() == _corrLetts.size())
		return true;
	return false;

}

bool Game::find(const char l, std::string& hide)
{
	bool status = false;
	for (int i = 0; i < _word.size(); i++)
	{
		if (_word[i] == l)
		{
			status = true;
			if (hide[i] != '_')
				return status;
			hide[i] = _word[i];
			_corrLetts.push_back(l);
		}
	}

	if (!status)
	{
		for (int i = 0; i <= _unCorrLetts.size(); i++)
		{
			if (_unCorrLetts[i] == l)
				return true;
			_unCorrLetts.push_back(l);
				return false;
		}
	}
	return status;
}
void Game::zeroing()
{
	_time = 0;
	_fails = 0;
	_corrLetts = "";
	_unCorrLetts = "";
}
void Game::play()
{
	zeroing();
	char L = 0;
	std::string hideWord;
	int size = _word.size();
	for( int i = 0; i < size; ++i)
	{
		hideWord.push_back('_');
	}
	unsigned int startTime = clock();
	do
	{
		printGallows(_fails);

		std::cout << "�����: " << hideWord << std::endl;
		std::cout << "������(" << _unCorrLetts.size() << "): " << _unCorrLetts << std::endl;
		std::cout << "�����: ";
		std::cin >> L;
		std::cin.ignore();
		if (!find(L, hideWord))
			_fails++;

	} while (!isDone());
	unsigned int stopTime = clock();
	_time = (stopTime - startTime) / 1000;
	if (_fails<_logo.size())
	{
		printGallows(_fails);

		std::cout << "�����: " << hideWord << std::endl;
		std::cout << "������(" << _unCorrLetts.size() << "): " << _unCorrLetts << std::endl;
		std::cout << "��������� ��������� �����: " << _corrLetts << std::endl;
		std::cout << "�� �������� �� " << _time << " ������!";
	}
	else
	{
			std::cout << "�� ��������� �� " << _time << " ������.\n";
			std::cout << "���������� �����: " << _word<<std::endl;
	}
	system("pause");
}


void Game::admin()
{
	std::string enter;
	char menu;
	std::cout << "������� ������: ";
	std::cin >> enter;
	if (enter != _pass)
	{
		std::cout << "Uncorrect pass\n";
		return;
	}
	std::cout << "\n��������� ������ ����...\n";
	Encrypt output{};
	Decrypt input{};
	input.showAll();

	do {
		menu = '2';
		std::cout << "\n�������� ����� ����� - [1]\n";

		std::cout << "����� � ������� ���� - [2]\n";
		std::cout << "������� ������� - [3]\n";

		std::cout << "\n������� ������� - [9]\n";
		std::cin >> menu;
		std::cin.ignore();
		switch (menu)
		{
		case '1':
			std::cout <<"\n������� ��� ����� ����:\n";
			std::cout << "\nC���� ������ ���� ������ ���������������,\n";
			std::cout << "������������� � ������������ ������ ������������� �����,\n";
			std::cout << "���� �������������� ����� ��� ���������� � ����� ����� ������������� �����.\n";
			std::cout << "���� ���� �� ���������� ���������\n";
			do {
				std::cout << "\n������� ����������� �����:";
				std::cin >> enter;
				output.push(enter);
				std::cout << "\n����� ���������. �������� ���? [y]/[n]  ";
				std::cin >> enter;
			} while (enter == "y");
				

			break;
		case '2':
			std::cout << "����� � ����";
			return;
		case '3':
			input.read();
			input.showAll();
			break;
		case '9':
			std::cout << "��������! ����� ������ ���� �������! �� ������� ����������? [yes]\[n]	";
			std::cin >> enter;
			if (enter == "yes")
			{
				output.clearFile();
				std::cout << "\n�������� ���������\n";
			}
			else
			{
				std::cout << "��� �������� ����� ������ \"yes\" ";
			}
			break;
		default:
			std::cout<<"������������ ����� ����.\n";
			break;
		}

	} while (menu!=2);
}

Game::Game()
{
	//������ ��������
	_logo.push_back("  p=======\n  |     ||\n        ||\n        ||\n        ||\n        ||\n==========\n");
	//������������� ���������
	_logo.push_back("  p=======\n  |     ||\n  O     ||\n        ||\n        ||\n        ||\n==========\n");
	_logo.push_back("  p=======\n  |     ||\n  O     ||\n  |     ||\n        ||\n        ||\n==========\n");
	_logo.push_back("  p=======\n  |     ||\n  O     ||\n /|     ||\n        ||\n        ||\n==========\n");
	_logo.push_back("  p=======\n  |     ||\n  O     ||\n /|\\    ||\n        ||\n        ||\n==========\n");
	_logo.push_back("  p=======\n  |     ||\n  O     ||\n /|\\    ||\n  |     ||\n        ||\n==========\n");
	//��������� ������������ ��������
	_logo.push_back("  p=======\n  |     ||\n  O     ||\n /|\\    ||\n /|     ||\n        ||\n==========\n");

	_banner.push_back("=============\n");
	_banner.push_back("|| ��������||\n");
	_banner.push_back("=============\n");
	startLogo(); 
	
	
}
Game::~Game() {}