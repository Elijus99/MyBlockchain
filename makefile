CXX = clang++
CC = clang

main:	hash.o block.o blockchain.o transactionsGenerator.o usersGenerator.o
	clang++ -o main main.cpp hash.o block.o blockchain.o transactionsGenerator.o usersGenerator.o
run:	main
	./main

clean:
	rm -f *.o main