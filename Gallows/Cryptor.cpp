#include "Header.h"
#include <fstream>
#include <ctime>
// Шифровальщик/дешифровальщик (done)
// Создание/редактирование файла (done)
// Добавление слова (done)
// шифрование слова(done)
// запись в файл (done)
// 
// чтение из файла (done)
// дешифровка (done)
// Передача массива слов в игру 
// 

//Encrypt

	void Encrypt::crypt()
	{
		int size = _str.size();
		for (int i = 0; i < size; ++i)
		{
			_str[i] += (_key + i); //тупое шифрование, путем добавления к индеску буквы дополнительного числа
		}
	}
	void Encrypt::run()
	{
		if (!_str.empty())
		{
			std::ofstream outF(_path, std::ios::app);
			crypt();
			outF << _str << _border;
			outF.close();
			_str.clear();
		}
	}

	void Encrypt::setStr(const std::string str) { if (str != "") _str = str; }
	std::string Encrypt::str() { return _str; }

	void Encrypt::push(const std::string str)
	{
		setStr(str);
		run();
	}
	
	void Encrypt::clearFile()
	{
		
			std::ofstream outF(_path);
			outF.close();
		
	}


//Decrypt	
	void Decrypt::decode()
	{
		//Через итератор не заработала работа со строками. 
		/*auto end = dictionary.end();
		for (auto iter = dictionary.begin(); iter != end; ++iter)
		{
			int size= *iter.size(); //не работает
			for (int i = 0; i < size; ++i)
			{
				iter[i] -= (_key + i); //не рабоатет
			}
		}*/

		//топорный метод
		int sizeCont = _dictionary.size();
		for (int i = 0; i < sizeCont; ++i) //для обхода по контейнеру
		{
			int sizeStr = _dictionary[i].size();
			for (int j = 0; j < sizeStr; ++j)//для обхода по строке
			{
				_dictionary[i][j] -= (_key + j);
			}
		}
	}

	void Decrypt::read()
	{
		_dictionary.clear();
		std::ifstream inF(_path);
		if (inF.is_open())
		{
			char buffer[_key]{}; //со string не заработало
			while (!inF.eof())
			{
				inF.getline(buffer, _key, _border);
				_dictionary.push_back(buffer);
			}
			inF.close();
		}
	
		decode();
	}


	void Decrypt::showAll()
	{
		std::cout << "Список слов:\n";
		auto end = _dictionary.end();
		for (auto iter = _dictionary.begin(); iter != end; ++iter)
		{
			std::cout << *iter << std::endl;
		}
		std::cout << "______________\n";
	}

	std::vector<std::string>* Decrypt::reciveData()
	{
		if (_dictionary.empty()) 		
			read();
		return &_dictionary;
	}
	std::string Decrypt::randWord()
	{
		srand((unsigned int)time(NULL));
		if (_dictionary.empty())
			read();
		std::string word = _dictionary[rand() % _dictionary.size()];
		return word;
	}
