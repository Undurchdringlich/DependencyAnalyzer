#pragma once

#include <iostream>
#include "Error.h"

class Basic
{
	public:
		int End(); //����������� �����

		Error error; //���������� � ������� ������
	private:
		int ErrorCall(); //�����, ���������� ��� �� ���������� ���������� ������ ���������

	protected:
		int virtual SuccessCall(); //�����, ���������� ��� ���������� ���������� ������ ���������
};

