# DependencyAnalyzer
���������� ������������ ������ �++

# RU
## ������� �������� ������ ��� Windows:
```sh
��������� START_TEST.bat
```

## �������� � ����������:
1. ��� ������ ��������� �� ������ ������ ���� `Analyzer` � ����������� �������� ������� ��������� ��������� ������.
2. � ������������ �� ��������� � ���������� ��� ���������, � ����� ��������� ��������� `Analyzer::InputData` ��� ����������� ������������� ���� ������.
3. ����� �������� ������� ���� `Analyzer` �� ��������� �������� ����� ������ ������: `Analyzer::Start`, ������� � ���� ������� ���������� ����� ���� `.cpp` � `.hpp` ������ ������ ���������� � ����� ����������� ������ ������ ������� �� ���� ������ �� ���� ������ ��������� (`#include`)
4. ����������� ���� �� ������ ��������� ������������ �� ��������� ��������� �������� ����� ��������� ����� ���������:

| ������ | ���� |
| ------ | ------ |
| " | ���� ������������ �������� ����� |
| < | ���� �� ���������� ��������� ������ |

5. ������� ��������� ������ ������������ �� ���� ������, ���� �������� ����� ����� ��������� ��������.
6. � ����������� �������� �� ������ 3 �� ��������� ���� ������� ������ `Tree` ����� �������, ����� ������������ ������ ����������� ������� ������
7. ����������� ����������� ������ ��������� ����������� ��������� ������ ������ �� ������� ����� ������ �� ����  �� ���� �� �������� �� ����� ������
8. ����������� ������������ ������� ������ ��������� � ������� ����������� (���� ������ � ������������ ������������) � ������ ������
9. ��� �������� ���������� ������ ������ ��������� ���� ������ � �������������, � �����, ��������������� �� ��������, ���������� � ���������� ��������� ��� ��� ���� ������


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