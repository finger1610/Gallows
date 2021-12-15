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
			std::cout << "Режим редактирования\n";
			admin();
			break;
		}
		default:
			std::cout << "Выбран некорретный пункт меню\n";
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

		std::cout << "Слово: " << hideWord << std::endl;
		std::cout << "Ошибки(" << _unCorrLetts.size() << "): " << _unCorrLetts << std::endl;
		std::cout << "Буква: ";
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

		std::cout << "Слово: " << hideWord << std::endl;
		std::cout << "Ошибки(" << _unCorrLetts.size() << "): " << _unCorrLetts << std::endl;
		std::cout << "Правильно введенные буквы: " << _corrLetts << std::endl;
		std::cout << "Вы победили за " << _time << " секунд!";
	}
	else
	{
			std::cout << "Вы проиграли за " << _time << " секунд.\n";
			std::cout << "Правильное слово: " << _word<<std::endl;
	}
	system("pause");
}


void Game::admin()
{
	std::string enter;
	char menu;
	std::cout << "Введите пароль: ";
	std::cin >> enter;
	if (enter != _pass)
	{
		std::cout << "Uncorrect pass\n";
		return;
	}
	std::cout << "\nЗагзурзка списка слов...\n";
	Encrypt output{};
	Decrypt input{};
	input.showAll();

	do {
		menu = '2';
		std::cout << "\nДобавить новое слово - [1]\n";

		std::cout << "Выйти в главное меню - [2]\n";
		std::cout << "Вывести словарь - [3]\n";

		std::cout << "\nУдалить словарь - [9]\n";
		std::cin >> menu;
		std::cin.ignore();
		switch (menu)
		{
		case '1':
			std::cout <<"\nПравила для ввода слов:\n";
			std::cout << "\nCлово должно быть именем существительным,\n";
			std::cout << "нарицательным в именительном падеже единственного числа,\n";
			std::cout << "либо множественного числа при отсутствии у слова формы единственного числа.\n";
			std::cout << "ввод слов на английской раскладке\n";
			do {
				std::cout << "\nВведите добавляемое слово:";
				std::cin >> enter;
				output.push(enter);
				std::cout << "\nСлово добавлено. Добавить ещё? [y]/[n]  ";
				std::cin >> enter;
			} while (enter == "y");
				

			break;
		case '2':
			std::cout << "Выход в меню";
			return;
		case '3':
			input.read();
			input.showAll();
			break;
		case '9':
			std::cout << "Внимание! будет удален весь словарь! Вы желаете продолжить? [yes]\[n]	";
			std::cin >> enter;
			if (enter == "yes")
			{
				output.clearFile();
				std::cout << "\nУдаление завершено\n";
			}
			else
			{
				std::cout << "для удаления нужно ввести \"yes\" ";
			}
			break;
		default:
			std::cout<<"Некорректный пункт меню.\n";
			break;
		}

	} while (menu!=2);
}

Game::Game()
{
	//Пустая виселица
	_logo.push_back("  p=======\n  |     ||\n        ||\n        ||\n        ||\n        ||\n==========\n");
	//промежуточная отрисовка
	_logo.push_back("  p=======\n  |     ||\n  O     ||\n        ||\n        ||\n        ||\n==========\n");
	_logo.push_back("  p=======\n  |     ||\n  O     ||\n  |     ||\n        ||\n        ||\n==========\n");
	_logo.push_back("  p=======\n  |     ||\n  O     ||\n /|     ||\n        ||\n        ||\n==========\n");
	_logo.push_back("  p=======\n  |     ||\n  O     ||\n /|\\    ||\n        ||\n        ||\n==========\n");
	_logo.push_back("  p=======\n  |     ||\n  O     ||\n /|\\    ||\n  |     ||\n        ||\n==========\n");
	//полностью отрисованная виселица
	_logo.push_back("  p=======\n  |     ||\n  O     ||\n /|\\    ||\n /|     ||\n        ||\n==========\n");

	_banner.push_back("=============\n");
	_banner.push_back("|| Виселица||\n");
	_banner.push_back("=============\n");
	startLogo(); 
	
	
}
Game::~Game() {}