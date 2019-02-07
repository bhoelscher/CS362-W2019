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

unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.c rngs.c
	gcc -o unitTest1 -coverage unittest1.c dominion.c rngs.c -Wall -fpic -lm -std=c99
	./unitTest1 >> unittestresults.out
	gcov ./dominion.c -b -f >> unittestresults.out
	gcc -o unitTest2 -coverage unittest2.c dominion.c rngs.c -Wall -fpic -lm -std=c99
	./unitTest2 >> unittestresults.out
	gcov ./dominion.c -b -f >> unittestresults.out
	gcc -o unitTest3 -coverage unittest3.c dominion.c rngs.c -Wall -fpic -lm -std=c99
	./unitTest3 >> unittestresults.out
	gcov ./dominion.c -b -f >> unittestresults.out
	gcc -o unitTest4 -coverage unittest4.c dominion.c rngs.c -Wall -fpic -lm -std=c99
	./unitTest4 >> unittestresults.out
	gcov ./dominion.c -b -f >> unittestresults.out
	gcc -o cardTest1 -coverage cardtest1.c dominion.c rngs.c -Wall -fpic -lm -std=c99
	./cardTest1 >> unittestresults.out
	gcov ./dominion.c -b -f >> unittestresults.out
	gcc -o cardTest2 -coverage cardtest2.c dominion.c rngs.c -Wall -fpic -lm -std=c99
	./cardTest2 >> unittestresults.out
	gcov ./dominion.c -b -f >> unittestresults.out
	gcc -o cardTest3 -coverage cardtest3.c dominion.c rngs.c -Wall -fpic -lm -std=c99
	./cardTest3 >> unittestresults.out
	gcov ./dominion.c -b -f >> unittestresults.out
	gcc -o cardTest4 -coverage cardtest4.c dominion.c rngs.c -Wall -fpic -lm -std=c99
	./cardTest4 >> unittestresults.out
	gcov ./dominion.c -b -f >> unittestresults.out

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unitTest1 unitTest2 unitTest3 unitTest4 cardTest1 cardTest2 cardTest3 cardTest4
