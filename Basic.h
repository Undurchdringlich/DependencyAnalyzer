#pragma once

#include <iostream>
#include "Error.h"

class Basic
{
	public:
		int End(); //Завершающий метод

		Error error; //Информация о текущей ошибке
	private:
		int ErrorCall(); //Метод, вызываемый при не корректном завершении работы программы

	protected:
		int virtual SuccessCall(); //Метод, вызываемый при корректном завершении работы программы
};

