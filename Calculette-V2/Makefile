all:
	flex -o projet.flex.cpp projet.flex
	bison -d projet.bison -o projet.bison.cpp
	g++ -o projet projet.flex.cpp projet.bison.cpp -w
	./projet test.txt

clean:
	rm -f projet.bison.cpp projet.bison.hpp projet.flex.cpp projet projet.exe