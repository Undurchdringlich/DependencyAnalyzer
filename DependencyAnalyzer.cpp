// DependencyAnalyzer.cpp: определяет точку входа для приложения.
//

#include "Analyzer.h"

int main(int argc, char* argv[])
{
    Analyzer dependencyAnalyzer(argc, argv);
    dependencyAnalyzer.Start();
    return dependencyAnalyzer.End();
}