bb8: main.cc print.o
	g++ -std=c++0x main.cc -o bb8

print.o: print.c
	gcc -c print.c
