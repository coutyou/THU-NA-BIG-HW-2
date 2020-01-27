Windows:

1. 直接运行main.exe

2. 命令行（需要安装g++编译器）：

cd到main.cpp的目录下

if ($?) { g++ main.cpp -o main } ; if ($?) { .\main }

Linux:

1. 命令行：

cd到main.cpp的目录下

g++ main.cpp -o main
./main