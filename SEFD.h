#pragma once

#if (_MSC_VER > 1900)
	#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING true
	// � visual studio 2019 �������� �������������� � ����� ����������, ���� ������������ experimental/filesystem, � �� ������ filesystem
#endif // (_MSC_VER > 1900)
#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
	#define _SCL_SECURE_NO_WARNINGS
#endif

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;