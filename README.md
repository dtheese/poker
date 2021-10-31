# Project to Count Frequency of 5-Card Poker Hands Contained within K-card Hands (5 <= K <= 52)

Directories **main** and **common** contain source for a program that indirectly enumerates all possible K-card poker hands (5 <= K <= 52) and determines each hand's rank. The count of each rank is then presented.

This program works as follows.

A unique integer (an "encoding") in the range 0..2,598,959 is associated with every possible 5-card poker hand (of which there are 2,598,960). A pre-computed lookup table (an array indexed by an encoding) is created at startup. Given an encoding, this lookup table returns the rank of the hand the encoding represents.

The program then proceeds to indirectly enumerate all K-card poker hands by looping over all integers in 0..C(52,K)-1. Each such integer represents the unique encoding of a K-card poker hand. That encoding is then decoded into the K-card poker hand it represents. Then, each possible 5-card combination of these K cards is considered. Each such 5-card hand's rank is obtained by encoding that 5-card hand and using the encoding to find the 5-card hand's rank in the lookup table. The highest rank of all 5-card hands contained within a K-card hand is then returned as the rank of the K-card hand.

This program uses a number of threads that is the least of:
   * The number of threads the hardware will support
   * The number of chunks of work the problem at hand can be split into
   * A user-specified limit on the number of threads

## Verifying Program Correctness (Monte Carlo Simulation)
This program has a secondary mode of operation where, instead of enumerating all possible hands and directly counting the number of hands that are of each rank, a Monte Carlo simulation is performed. Over a large enough number of trials, this will allow verifying that the probability of a given hand rank is coming out close to the theoretical value.

To perform a Monte Carlo simulation, edit **common/parameters.h**, set **TRIALS** to the desired number of trials, and rebuild (described below).

## Setting the Hand Size (K)
To control the hand size, edit **common/parameters.h**, set **NUM_CARDS** to the desired value, and rebuild (described below).

The default hand size is 5.

## Limiting the Number of Threads
If you wish to limit the number of threads used, edit **common/parameters.h**, set **THREADS_LIMIT** to the desired value, and rebuild (described below).

The default behavior is to use as many threads as the hardware will support.

## Build Environment
This project was built under CentOS 8 with **g++** and conforms to **C++17**.

## Obtaining, Configuring, Building, and Running the Project
You can create a local clone of this project with this command:  
**git clone https://github.com/dtheese/poker**

Edit **common/parameters.h** to select any particular behavior, as described above.

The program can then be built as follows:  
**cd poker/main**
**./build**

The program can then be run as follows:  
**./poker**
