#include "Analyzer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

Analyzer::Analyzer(int argc, char* argv[])
{
    CommandLineParser(argc, argv);
    Tree::Node::Data rootNodeData(fs::path(inputData.mainPath));
    tree = new Tree(rootNodeData);
}
Analyzer::~Analyzer()
{
    delete tree;
}


void Analyzer::CommandLineParser(int argc, char* argv[])
{
    if (argc > 1)
    {
        std::string sourcePath = argv[1];
        if (fs::exists(fs::path(sourcePath)))
        {
            if (fs::is_directory(fs::path(sourcePath)))
            {
                inputData.mainPath = sourcePath;
            }
            else
            {
                error.Create("Source path is not directory", sourcePath);
                return;
            }
            
        }
        else
        {
            error.Create("Source path is not exists", sourcePath);
            return;
        }

        bool isIncludePath = false;
        for ( int i = 2; i < argc; i++ )
        {
            std::string arg = argv[i];
            if ( arg == "-I" )
            {
                isIncludePath = true;
                continue;
            }
            
            if (isIncludePath)
            {
                if (fs::exists(fs::path(arg)))
                {
                    inputData.includes.push_back(arg);
                    isIncludePath = false;
                }
                else
                {
                    error.Create("Include path is not exists", arg);
                    return;
                }
               
            }
        }
        
    }
    else
    {
        error.Create("Missing command line arguments");
        return;
    }
}

std::pair<fs::path, std::string> Analyzer::FindFileWithDirectory(std::string filename, std::vector<std::string> directories)
{
    std::vector<std::pair<fs::path, std::string>> result;
    for ( auto directory : directories )
    {
        fs::path source = fs::path(fs::path(directory).string() + "/" + filename).parent_path();
        for (auto& entry : fs::directory_iterator(source))
        {
            if (entry.path().filename() == fs::path(filename).filename())
            {
                result.push_back(std::make_pair(entry.path(), ""));
            }
        }
    }

    return ReturnFileWithDirectory(result, filename);
}

std::pair<fs::path, std::string> Analyzer::FindFileWithDirectory(std::string filename, std::string directory)
{
    std::vector<std::pair<fs::path, std::string>> result;
    for (auto& entry : fs::directory_iterator(directory))
    {
        if (entry.path().filename().string() == filename)
        {
            result.push_back(std::make_pair(entry.path(), ""));
        }
    }

    return ReturnFileWithDirectory(result, filename);
}

std::pair<fs::path, std::string> Analyzer::ReturnFileWithDirectory(const std::vector<std::pair<fs::path, std::string>>& result, const std::string& filename)
{
    if (result.size() > 1)
    {
        error.Create("calling an undefined file");
    }

    if (result.size() == 1)
    {
        return result[0];
    }

    return std::make_pair(filename, " (!)");
}

std::pair<std::string, std::string> Analyzer::GetPathToIncludeFile(const std::string& filename, const std::string& delimiter, const std::string& parentFile)
{
    std::pair<fs::path, std::string> result;
    //Поиск файла относительно пути к обрабатываемому файлу
    if (delimiter == "\"")
    {
        fs::path source = fs::path(fs::path(parentFile).parent_path().string() + "/" + filename).parent_path();
        result = FindFileWithDirectory(fs::path(filename).filename().string(), source.string());
    }

    //Поиск файла в директориях включения, указанных в аргументах при запуске программы
    if (delimiter == "<")
    {
        result = FindFileWithDirectory(filename, inputData.includes);
    }

    return std::make_pair(result.first.string(), result.second);
}



void Analyzer::FillTree(std::pair<std::string, std::string> pathToFile, Tree& tree, Tree::Node& parentNode)
{
    Tree::Node::Data nodeData(fs::path(pathToFile.first), pathToFile.second);
    Tree::Node node(nodeData);

    if (!tree.SearchUpParent(parentNode, node))
    {
        std::regex include_regex("(#include) (\"|<)(.{3,})[\"|>]");

        std::string one_line_comment("//");
        std::string multi_line_comment_start("/*");
        std::string multi_line_comment_end("*/");

        bool isMultiLineComment = false;

        std::ifstream in(pathToFile.first);
        std::string line;
        std::smatch include_match; //Результат работы регулярного выражения
        std::map<std::string, std::string> includes; //Пул вызываемых включений

        tree.Bind(parentNode, node);

        if (in.is_open())
        {
            while (std::getline(in, line))
            {
                bool isLineComment = false;
                //Определяем, присутствует ли начало многострочного комментария в строке
                if (line.find(multi_line_comment_start) < line.length())
                {
                    isMultiLineComment = true;
                }
                
                if (std::regex_search(line, include_match, include_regex))
                {
                    if (include_match[0].length() > 0)
                    {
                        //Определяем, закомментирована ли зависимость однострочным комментарием
                        if (line.find(include_match[0]) > line.find(one_line_comment))
                        {
                            isLineComment = true;
                        }

                        
                        if (line.find(multi_line_comment_start) < line.length())
                        {
                            //Определяем, начинается ли многострочный комментарий перед #include
                            if (line.find(include_match[0]) < line.find(multi_line_comment_start))
                            {
                                isMultiLineComment = false;
                            }
                        }
                        
                        if (line.find(multi_line_comment_end) < line.length())
                        {
                            //Определяем, заканчивается ли многострочный комментарий перед #include
                            if (line.find(include_match[0]) > line.find(multi_line_comment_end))
                            {
                                isMultiLineComment = false;
                            }
                        }
                    }

                    if (!isLineComment && !isMultiLineComment && include_match[3].length() > 0)
                    {
                        //Добавляем файл из директивы #include в пул для рекурсивного прохода
                        includes.emplace(std::make_pair(include_match[3], include_match[2]));
                    }
                        
                }

                //Определяем, присутствует ли конец многострочного комментария в строке
                if (line.find(multi_line_comment_end) < line.length())
                {
                    isMultiLineComment = false;
                }
            }
            in.close();
        }

        for (auto inc : includes)
        {
            //Рекурсивно проходим по каждому наследнику из includes
            FillTree(GetPathToIncludeFile(inc.first, inc.second, pathToFile.first), tree, node);
        }
    }
    else
    {
        error.Create( "Cyclic dependency in file: " + parentNode.data.path.string() + " to file: ", node.data.path.string());
    }
}

void Analyzer::Start()
{
    if (!error.isExists())
    {
        std::vector<std::string> sourceFiles = GetFiles(inputData.mainPath);
        
        for ( auto item : sourceFiles )
        {
            FillTree(std::make_pair(item, ""), *tree, tree->root);
            if (error.isExists()) return;
        }
    }
    else
    {
        return;
    }
}

int Analyzer::SuccessCall()
{
    tree->Print();
    return 0;
}

std::vector<std::string> Analyzer::GetFiles(std::string path)
{
    std::vector<std::string> result;
    for (auto& entry : fs::directory_iterator(path))
    {
        if (entry.path().extension() == ".hpp" || entry.path().extension() == ".cpp")
        {
            result.push_back(entry.path().string());
        }
    }

    return result;
}