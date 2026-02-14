CC = clang++
FLAGS = -std=c++17
LIBS = -lz
src: src.cpp errors.hpp repo.hpp inih/cpp/INIReader.cpp
	$(CC) $(FLAGS) -Iinih/cpp -Iinih src.cpp inih/cpp/INIReader.cpp inih/ini.c -o src $(LIBS)

dBug :src.cpp errors.hpp repo.hpp inih/cpp/INIReader.cpp
	$(CC) $(FLAGS) -g -Iinih/cpp -Iinih src.cpp inih/cpp/INIReader.cpp inih/ini.c -o src $(LIBS)

clean:
	rm -f src *.o
