TestRule: ./crc/main.cpp
	g++ ./crc/main.cpp ./include/invoice.h ./include/phoneCall.h ./include/declarations.h ./crc/definitions.cpp ./crc/invoice.cpp ./crc/phoneCall.cpp -o program.exe
