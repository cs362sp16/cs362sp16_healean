cmake_minimum_required(VERSION 3.3)

project(dominion)

#[[set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")]]

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fpic -coverage -lm")

add_custom_target(dominion COMMAND make -C ${mytest_SOURCE_DIR}
        CLION_EXE_DIR=${PROJECT_BINARY_DIR})


set(DOMINION dominion.h dominion.c rngs.h rngs.c)

set(UNITTEST1 unittest1.c ${DOMINION})
set(UNITTEST2 unittest2.c ${DOMINION})
set(UNITTEST3 unittest3.c ${DOMINION})
set(UNITTEST4 unittest4.c ${DOMINION})

set(CARDTEST1 cardtest1.c ${DOMINION} testdominion.h)
set(CARDTEST2 cardtest2.c ${DOMINION})
set(CARDTEST3 cardtest3.c ${DOMINION})
set(CARDTEST4 cardtest4.c ${DOMINION})

set(RANDOMADV randomtestadventurer.c ${DOMINION})
set(RANDMOMCARD1 randomcard1.c ${DOMINION})
set(RANDMOMCARD2 randomcard2.c ${DOMINION})

set(TESTDOMINION testdominion.c ${DOMINION})

add_executable(unittest1 ${UNITTEST1})
add_executable(unittest2 ${UNITTEST2})
add_executable(unittest3 ${UNITTEST3})
add_executable(unittest4 ${UNITTEST4})

add_executable(cardtest1 ${CARDTEST1})
add_executable(cardtest2 ${CARDTEST2})
add_executable(cardtest3 ${CARDTEST3})
add_executable(cardtest4 ${CARDTEST4})

add_executable(randomtestadventurer ${RANDOMADV})
add_executable(randomcard1 ${RANDMOMCARD1})
add_executable(randomcard2 ${RANDMOMCARD2})

add_executable(testdominion ${TESTDOMINION})
