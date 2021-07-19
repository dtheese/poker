Project to count frequency of 5-card poker hands contained within N-card hands (5 <= N <= 52)

Directory "main" contains a version of the program that enumerates all possible 5-card hands and determines each hand's rank by direct evaluation of the hand.

The version of the program in directory "main" also has a second mode of operation. In this alternate mode of operation, hands are randomly generated until a target hand rank has been achieved a specified number of times. The intent of this mode is to check that the hand frequencies are coming out close to what is expected over a large number of trials.

The mode of operation for the version of the program in "main" is selected in the file main.cpp with the use of a **\#if** preprocessor statement.

Directory "tableLookup" is an experimental version of the program where I pre-construct a lookup table to determine a hand's rank. Then, as with "main", the program enumerates all possible 5-card hands and determines each hand's rank, but it does so by using the lookup table instead of by direct evaluation.

The "common" directory contains files that are common to both versions of this program.

After empirical timing tests, C-style arrays are generally preferred to std::vector or std::array.

This project was built under CentOS 7.

This project conforms to C++11. However, the "build" file specifies C++14 as that is the latest version of C++ with support available for CentOS 7.

CentOS 7 does not support C++11 (or higher) by default. To get this support, you must execute these commands:  
\# Do this one time only  
**yum install centos-release-scl**

\# Do this in every shell session where you build this program  
**scl enable devtoolset-7 bash**

You can create a local clone of this project with this command:  
**git clone https://github.com/dtheese/poker**

The program can then be built as follows:  
**cd poker/main**  
OR  
**cd poker/tableLookup**  

**./build**  

The program can then be run as follows:  
**./poker**
