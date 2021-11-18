#pragma once

#include "Basic.h"
#include "SEFD.h"
#include "Tree.h"
#include <vector>

class Analyzer : public Basic
{
	//Структура входящих данных для упрощения манипулирования данными
	struct InputData
	{
		std::string mainPath;
		std::vector<std::string> includes;
	};

	public:
		Analyzer(int, char*[]);
		~Analyzer();

		void Start(); //Метод запускающий работу анализатора
	private:
		InputData inputData;
		Tree* tree;

		void CommandLineParser(int, char*[]); //Производим разбор аргументов командной строки и заполняем inputData
		std::vector<std::string> GetFiles(std::string); //Получаем файлы из директорий включений
		void FillTree(std::pair<std::string, std::string>, Tree&, Tree::Node&); //Рекурсивное заполнение дерева
		std::pair<std::string, std::string> GetPathToIncludeFile(const std::string&, const std::string&, const std::string&); //Получаем путь до файла включения и постфиксную приписку (Для тех включений, файлов которых не существует)
		std::pair<fs::path, std::string> FindFileWithDirectory(std::string, std::vector<std::string>); //Ищем файл включения в нескольких директориях
		std::pair<fs::path, std::string> FindFileWithDirectory(std::string, std::string); //Ишем файл включения в конкретной директории
		std::pair<fs::path, std::string> ReturnFileWithDirectory(const std::vector<std::pair<fs::path, std::string>>&, const std::string&); //Проверка и возврат значения

		int SuccessCall() override final;
};

