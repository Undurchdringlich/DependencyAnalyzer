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

				//����� ��� ������������ �������� ������
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
		
		void Bind(Node&, Node&); //������ ���� �� ��������� �������������� ���� � ��� ��������������� �������� � ������

		void Print();

		bool SearchUpParent(Node&, Node&); //���������� �������� � ������ � ������ ������������ ������ ������� ���� �� ��������������� ��������

	private:
		std::map<std::string, int> fileOccurrences;

		bool SearchUpParentRecursive(Node*, Node&); //����������� ����� ���� �� �������������, �� ��������������� �������� �� ����� ������
		
		Node* GetNode(Node&, Node&); //�������� ���� ������ �� ��������� ������� ������-�� �������������� ���� � ��� ��������������� �������� � ������

		void PrintTree(Node& current, std::string prefix = ""); //�������� � ������� ������

		void PrintOccurrences(); //�������� � ������� ����� � ���������� �� ���������
};

