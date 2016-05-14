CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

unittest1: unittest1.c dominion.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresult.out
	gcov unittest1.c >> unittestresult.out

unittest2: unittest2.c dominion.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresult.out
	gcov unittest2.c >> unittestresult.out

unittest3: unittest3.c dominion.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresult.out
	gcov unittest3.c >> unittestresult.out

unittest4: unittest4.c dominion.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresult.out
	gcov unittest4.c >> unittestresult.out

cardtest1: cardtest1.c dominion.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> unittestresult.out
	gcov -b cardtest1.c >> unittestresult.out

cardtest2: cardtest2.c dominion.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> unittestresult.out
	gcov -b cardtest2.c >> unittestresult.out

cardtest3: cardtest3.c dominion.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> unittestresult.out
	gcov -b cardtest3.c >> unittestresult.out

cardtest4: cardtest4.c dominion.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> unittestresult.out
	gcov -b cardtest4.c >> unittestresult.out

randomtestadventurer: randomtestadventurer.c dominion.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	
randomcard1: randomcard1.c dominion.o
	gcc -o randomcard1 -g randomcard1.c dominion.o rngs.o $(CFLAGS)
	./randomcard1 >> randomcard1.out
	gcov -b dominion.c >> randomcard1.out
	cat dominion.c.gcov >> randomcard1.out
	
randomcard2: randomcard2.c dominion.o
	gcc -o randomcard2 -g randomcard2.c dominion.o rngs.o $(CFLAGS)
	./randomcard2 >> randomcard2.out
	gcov -b dominion.c >> randomcard2.out
	cat dominion.c.gcov >> randomcard2.out
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomcard1 randomcard2

test: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest3 cardtest4 randomtestadventurer randomcard1 randomcard2

clean:
	rm -f *.o playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomcard1 randomcard2 player.exe *.gcov *.gcda *.gcno *.so *.a *.dSYM *.out
