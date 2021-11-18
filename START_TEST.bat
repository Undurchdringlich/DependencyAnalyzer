@echo off

set source=%~dp0tests\source
set include1=%~dp0tests\source\includes
set include2=%~dp0tests\lib

%~dp0out\build\x64-Clang-Release\DependencyAnalyzer.exe %source% -I %include1% -I %include2%

@pause