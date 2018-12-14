CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to enter: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g dominion.o rngs.o interface.o $(CFLAGS)

# ut1.o: unittest1.c unittest1.h
# 	gcc -c unittest1.c -g $(CFLAGS)
#
# ut2.o: unittest2.c unittest2.h
# 	gcc -c unittest2.c -g $(CFLAGS)
#
# ut3.o: unittest3.c unittest3.h
# 	gcc -c unittest3.c -g $(CFLAGS)
#
# ct1.o: cardtest1.c cardtest1.h
# 	gcc -c cardtest1.c -g $(CFLAGS)

unittests: unittests.c
	gcc -o unittests unittests.c -g dominion.o rngs.o interface.o $(CFLAGS)

# cardtests: cardtest1.o dominion.o rngs.o
# 	gcc -o cardtests cardtests.c cardtest1.c -g dominion.o rngs.o $(CFLAGS)

unittestresults: unittests playdom player
	./unittests &> unittestresults.out
	gcov unittest1.c >> unittestresults.out
	cat unittest1.c.gcov >> unittestresults.out
	gcov unittest2.c >> unittestresults.out
	cat unittest2.c.gcov >> unittestresults.out
	# gcov unittest3.c >> unittestresults.out
	# cat unittest3.c.gcov >> unittestresults.out
	# gcov unittest4.c >> unittestresults.out
	# cat unittest4.c.gcov >> unittestresults.out
	# ./cardtests >> unittestresults.out
	gcov cardtest1.c >> unittestresults.out
	cat cardtest1.gcov >>  unittestresults.out
	# gcov cardtest2.c >> unittestresults.out
	# cat cardtest2.gcov >>  unittestresults.out
	# gcov cardtest3.c >> unittestresults.out
	# cat cardtest3.gcov >>  unittestresults.out
	# gcov cardtest4.c >> unittestresults.out
	# cat cardtest4.gcov >>  unittestresults.out

all: playdom player

clean:
	rm -f *.o unittests unittests.exe playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittestresults unittestresults.exe unittestresult unittestresult.exe
