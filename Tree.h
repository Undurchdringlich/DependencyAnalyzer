#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "SEFD.h"

class Tree
{
	public:
		class Node
		{
			public:
				friend class Tree;

				//класс для инкапсуляции хранимых данных
				class Data
				{
					public:
						Data(fs::path, std::string _postfix = "");
						Data() {}

						Data& operator = (Data&);
						bool operator == (Data&);
						bool operator != (Data&);

						fs::path path;
						std::string filename;
						std::string postfix;
				};

				Node(Data);
				Node(){}

				bool operator == (Node&);

				Data data;
			private:
				Node* parent = nullptr;
				std::vector<Node> child;
		};

		Node root;

		Tree(Tree::Node::Data);
		
		void Bind(Node&, Node&); //Создаём узел на основании непривязанного узла и его предполагаемого родителя в дереве

		void Print();

		bool SearchUpParent(Node&, Node&); //Нахождение родителя в дереве и запуск рекурсивного поиска нужного узла от предполагаемого родителя

	private:
		std::map<std::string, int> fileOccurrences;

		bool SearchUpParentRecursive(Node*, Node&); //Рекурсивный поиск узла на существование, от предполагаемого родителя до корня дерева
		
		Node* GetNode(Node&, Node&); //Получаем узел дерева на основании другого такого-же непривязанного узла и его предполагаемого родителя в дереве

		void PrintTree(Node& current, std::string prefix = ""); //Печатаем в консоль дерево

		void PrintOccurrences(); //Печатаем в консоль файлы и количество их вхождений
};

