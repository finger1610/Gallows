#include "Header.h"
#include <fstream>
#include <ctime>
// ������������/�������������� (done)
// ��������/�������������� ����� (done)
// ���������� ����� (done)
// ���������� �����(done)
// ������ � ���� (done)
// 
// ������ �� ����� (done)
// ���������� (done)
// �������� ������� ���� � ���� 
// 

//Encrypt

	void Encrypt::crypt()
	{
		int size = _str.size();
		for (int i = 0; i < size; ++i)
		{
			_str[i] += (_key + i); //����� ����������, ����� ���������� � ������� ����� ��������������� �����
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
		//����� �������� �� ���������� ������ �� ��������. 
		/*auto end = dictionary.end();
		for (auto iter = dictionary.begin(); iter != end; ++iter)
		{
			int size= *iter.size(); //�� ��������
			for (int i = 0; i < size; ++i)
			{
				iter[i] -= (_key + i); //�� ��������
			}
		}*/

		//�������� �����
		int sizeCont = _dictionary.size();
		for (int i = 0; i < sizeCont; ++i) //��� ������ �� ����������
		{
			int sizeStr = _dictionary[i].size();
			for (int j = 0; j < sizeStr; ++j)//��� ������ �� ������
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
			char buffer[_key]{}; //�� string �� ����������
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
		std::cout << "������ ����:\n";
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
