aes:main.o Aes.o
	g++ main.o Aes.o -g -Wall -o aes
	rm -rf *.o
clean:
	rm -rf *.o