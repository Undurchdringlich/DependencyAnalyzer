#pragma once

#include <iostream>

//Класс с информацией об ошибке
class Error
{
	public:
		void Create(std::string, std::string file = "");

		bool isExists();
		std::string message();
		std::string file();
		void Print();

	private:
		bool _isExists = false;
		std::string _message;
		std::string _file;

};

