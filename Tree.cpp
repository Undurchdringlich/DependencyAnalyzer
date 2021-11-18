#include "Tree.h"

bool Tree::Node::operator == (Tree::Node& node1)
{
	if (this->data == node1.data)
	{
		if (this->parent != nullptr && node1.parent != nullptr)
		{
			if (this->parent->data == node1.parent->data)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (this->parent == nullptr && node1.parent == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

Tree::Node::Data::Data(fs::path _path, std::string _postfix)
{
	this->path = _path;
	this->filename = _path.filename().string();
	this->postfix = _postfix;
}

Tree::Node::Data& Tree::Node::Data::operator = (Tree::Node::Data& data1)
{
	this->path = data1.path;
	this->filename = data1.filename;
	this->postfix = data1.postfix;

	return *this;
}

bool Tree::Node::Data::operator == (Tree::Node::Data& data1)
{
	return this->path == data1.path;
}

bool Tree::Node::Data::operator != (Tree::Node::Data& data1)
{
	return !(this->path == data1.path);
}

Tree::Node::Node(Data _data)
{
	this->data = _data;
}

Tree::Tree(Tree::Node::Data _data)
{
	root.data = _data;
}

void Tree::Bind(Node& parentElement, Node& currentElement)
{
	Tree::Node* parent = GetNode(root, parentElement);

	if (parent != nullptr)
	{
		currentElement.parent = parent;
		parent->child.push_back(currentElement);
	}
}

void Tree::Print()
{
	PrintTree( root );
	std::cout << std::endl;
	PrintOccurrences();
}

void Tree::PrintTree( Tree::Node& current, std::string prefix )
{

	if (current.data != root.data) std::cout << prefix << current.data.filename << current.data.postfix << std::endl;

	auto search = fileOccurrences.find(current.data.filename);
	if (search != fileOccurrences.end())
	{
		if (current.parent != nullptr && current.parent->data != root.data)
		{
			++search->second;
		}
	}
	else
	{
		if (current.data != root.data)
		{
			int insertValue = 0;
			if (current.parent != nullptr && current.parent->data != root.data)
			{
				insertValue = 1;
			}
			fileOccurrences.emplace(std::make_pair(current.data.filename, insertValue));
		}
	}
	
	if ( current.child.size() > 0 )
	{
		if (current.data != root.data) prefix = ".." + prefix;
		for (auto& item : current.child)
		{
			PrintTree( item, prefix);
		}
	}
}

void Tree::PrintOccurrences()
{
	auto cmp = [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b)
	{
		return (a.second > b.second);
	};
	std::vector<std::pair<std::string, int>> vectorOccurrences;
	std::copy(fileOccurrences.begin(), fileOccurrences.end(), std::back_inserter(vectorOccurrences));

	std::sort(vectorOccurrences.begin(), vectorOccurrences.end(), cmp);
	for (auto item : vectorOccurrences)
	{
		std::cout << item.first << " " << item.second << std::endl;
	}
}

Tree::Node* Tree::GetNode(Tree::Node& currentElement, Tree::Node& findNode)
{
	Tree::Node* result = nullptr;	

	if (findNode == currentElement)
	{
		if (result == nullptr) result = &currentElement;
	}
	else
	{
		for (auto& item : currentElement.child)
		{
			if (result == nullptr) result = GetNode(item, findNode);
		}
	}

	return result;
}

bool Tree::SearchUpParentRecursive(Tree::Node* node, Tree::Node& findNode)
{
	bool result = false;
	if (node->data.path == findNode.data.path)
	{
		return true;
	}
	else
	{
		if (node != nullptr)
		{
			if (node->parent != nullptr)
			{
				result = SearchUpParentRecursive(node->parent, findNode);
			}
		}
	}
	return result;
}

bool Tree::SearchUpParent(Tree::Node& parentNode, Tree::Node& findNode)
{
	Tree::Node* parent = GetNode(root, parentNode);

	if (parent != nullptr)
	{
		return SearchUpParentRecursive(parent, findNode);
	}

	return false;
}

