#pragma once

#include "Basic.h"
#include "SEFD.h"
#include "Tree.h"
#include <vector>

class Analyzer : public Basic
{
	//��������� �������� ������ ��� ��������� ��������������� �������
	struct InputData
	{
		std::string mainPath;
		std::vector<std::string> includes;
	};

	public:
		Analyzer(int, char*[]);
		~Analyzer();

		void Start(); //����� ����������� ������ �����������
	private:
		InputData inputData;
		Tree* tree;

		void CommandLineParser(int, char*[]); //���������� ������ ���������� ��������� ������ � ��������� inputData
		std::vector<std::string> GetFiles(std::string); //�������� ����� �� ���������� ���������
		void FillTree(std::pair<std::string, std::string>, Tree&, Tree::Node&); //����������� ���������� ������
		std::pair<std::string, std::string> GetPathToIncludeFile(const std::string&, const std::string&, const std::string&); //�������� ���� �� ����� ��������� � ����������� �������� (��� ��� ���������, ������ ������� �� ����������)
		std::pair<fs::path, std::string> FindFileWithDirectory(std::string, std::vector<std::string>); //���� ���� ��������� � ���������� �����������
		std::pair<fs::path, std::string> FindFileWithDirectory(std::string, std::string); //���� ���� ��������� � ���������� ����������
		std::pair<fs::path, std::string> ReturnFileWithDirectory(const std::vector<std::pair<fs::path, std::string>>&, const std::string&); //�������� � ������� ��������

		int SuccessCall() override final;
};

