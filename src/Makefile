all:
	g++ -g -fsanitize=address -std=c++17 main.cc ../Libs/EasyBMP/EasyBMP.cpp Model/Model.cc Controler/Controler.cc && ./a.out
	open output.bmp
	open ../Images/Lena.bmp

lib_install:
	git clone git@github.com:aburgh/EasyBMP.git ../Libs/EasyBMP