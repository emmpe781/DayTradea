# DayTradea


USE MAKE FILE:

OLD NOTES (MIGHT NOT WORK)
To compile pictures. Download Python 3.6 and install matplotlib. Run:
g++ -DWITHOUT_NUMPY -std=gnu++11 -I C:/Users/Otur1337/Python36-32/include -L C:/Users/Otur1337/Python36-32/libs -o minimal minimal.cpp -l python36

To ompile project with following files:
$ g++ -g -Wall main.cpp readfile.cpp stock.cpp portfolio.cpp -o main -DWITHOUT_NUMPY -std=gnu++11 -I C:/Users/Otur1337/Python36-32/include -L C:/Users/Otur1337/Python36-32/libs -l python36