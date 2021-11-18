# DependencyAnalyzer
Анализатор зависимостей файлов С++

# RU
## Быстрая проверка работы для Windows:
```sh
Запустить START_TEST.bat
```

## Подробно о реализации:
1. При старте программы мы создаём объект типа `Analyzer` в конструктор которого передаём аргументы командной строки.
2. В конструкторе мы разбираем и валидируем все аргументы, а потом заполняем структуру `Analyzer::InputData` для дальнейшего использования этих данных.
3. После создания объекта типа `Analyzer` мы запускаем основной метод работы модуля: `Analyzer::Start`, который в свою очередь инициирует обход всех `.cpp` и `.hpp` файлов внутри дериктории а также рекурсивный проход внутри каждого из этих файлов по пути файлов включения (`#include`)
4. Определение пути до файлов включения определяется на основании следующих символов перед названием файла включения:

| Символ | Путь |
| ------ | ------ |
| " | путь относительно текущего файла |
| < | путь из аргументов командной строки |

5. Главная структура данных представляет из себя дерево, узлы которого могут иметь множество потомков.
6. В рекурсивных проходов из пункта 3 мы заполняем наше главное дерево `Tree` таким образом, чтобы отображалась прямая взаимосвязь вызовов файлов
7. Рекурсивная зависимость файлов включения пресекается проверкой внутри дерева на наличие точно такого же узла  по пути от родителя до корня дерева
8. Комментарии определяются методом поиска подстроки с началом комментария (либо просто с однострочным комментарием) в каждой строке
9. при успешном завершении работы модуля выводится само дерево с зависимостями, а также, отсортированная по убыванию, информация о количестве включений тех или иных файлов


# EN
# DependencyAnalyzer
C ++ File Dependency Analyzer


## Quick Checker for Windows:
```sh
Run START_TEST.bat
```

## Implementation details:
1. At the start of the program, we create an object of type `Analyzer` in the constructor of which we pass the string arguments.
2. In the constructor, we parse and validate all the arguments, and then fill in the `Analyzer :: InputData` structure for further use of this data.
3. After creating an object of the `Analyzer` type, we run the main method of the module:` Analyzer :: Start`, which in turn starts the traversal of all the files `.cpp` and` .hpp` inside the directory, as well as a recursive traversal inside each of these files in the include file path (`# include`)
4. The definition of the path to the include files is defined by the following characters before the name of the include file:

| Symbol | The path |
| ------ | ------ |
| "| path relative to the current file |
| <| path from string system arguments |

5. The main data structure is a tree, the nodes of which can have many children.
6. In the recursive passes from point 3, we fill our tree `Tree` in such a way that the direct relationship of files is displayed.
7. Recursive dependency of include files is suppressed by checking the presence of the same node along the path from the parent to the root of the tree inside the tree
8. Comments by the method of searching for a substring with the beginning of a comment (or just with a one-line comment) in each line
9. upon successful completion of the module, the tree itself with dependencies is displayed, as well as sorted in descending order, information about the number of included those or containing files