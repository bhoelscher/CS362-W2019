CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

randomtestresults: randomtestcard1.c randomtestcard2.c randomtestadventurer.c dominion.c rngs.c
	gcc -o randomTest1 -coverage randomtestcard1.c dominion.c rngs.c -Wall -fpic -lm -std=c99
	./randomTest1 >> randomtestcard1.out
	gcov ./dominion.c -b -f >> randomtestcard1.out
	gcc -o randomTest2 -coverage randomtestcard2.c dominion.c rngs.c -Wall -fpic -lm -std=c99
	./randomTest2 >> randomtestcard2.out
	gcov ./dominion.c -b -f >> randomtestcard2.out
	gcc -o randomTestAdv -coverage randomtestadventurer.c dominion.c rngs.c -Wall -fpic -lm -std=c99
	./randomTestAdv >> randomtestadventurer.out
	gcov ./dominion.c -b -f >> randomtestadventurer.out

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
