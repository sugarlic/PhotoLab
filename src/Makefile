all:
	g++ -g -fsanitize=address main.cc ../Libs/EasyBMP/EasyBMP.cpp Model/Model.cc && ./a.out
	open output.bmp
	open ../Images/Lena.bmp