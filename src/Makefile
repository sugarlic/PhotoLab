all:
	git clone git@github.com:aburgh/EasyBMP.git Libs
	g++ main.cc ../Libs/EasyBMP/EasyBMP.cpp Model/Model.cc Controler/Controler.cc && ./a.out
	open output.bmp
	open ../Images/Lena.bmp