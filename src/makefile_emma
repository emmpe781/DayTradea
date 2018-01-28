#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = g++
CFLAGS  = -g -Wall -Wl,-subsystem,console -std=c++0x -D_hypot=hypot


#main: main.cpp matplotlibcpp.h
#	g++ main.cpp -I/usr/include/python3.5 -lpython3.5 -o main -std=c++11


# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
all: main
# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
#main: main.o portfolio.o stock.o readfile.o plot.o algorithms.o
#	$(CC) $(CFLAGS) -o main main.o portfolio.o stock.o readfile.o plot.o algorithms.o -I C:/Python36-32/include -L C:/Python36-32/libs -l python36
main: main.o portfolio.o stock.o readfile.o plot.o algorithms.o
		$(CC) $(CFLAGS) -o main main.o  portfolio.o stock.o readfile.o plot.o algorithms.o  -I C:/Users/Otur1337/Python36-32/include -L C:/Users/Otur1337/Python36-32/libs -l python36


#-DWITHOUT_NUMPY

# To create the object file main.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
#main.o: main.cpp portfolio.h stock.h readfile.h
#	$(CC) $(CFLAGS) -c hello.cpp 

# To create the object file counter.o, we need the source files
# counter.c and counter.h:
#
main.o:  main.cpp portfolio.h readfile.h stock.h plot.h algorithms.h
	$(CC) $(CFLAGS) -c main.cpp
	
portfolio.o:  portfolio.cpp portfolio.h readfile.h stock.h 
	$(CC) $(CFLAGS) -c portfolio.cpp

readfile.o:  readfile.cpp portfolio.h readfile.h stock.h 
	$(CC) $(CFLAGS) -c readfile.cpp

stock.o:  stock.cpp portfolio.h readfile.h stock.h 
	$(CC) $(CFLAGS) -c stock.cpp 

algorithms.o:  algorithms.cpp portfolio.h stock.h 
	$(CC) $(CFLAGS) -c algorithms.cpp 

plot.o: plot.cpp stock.h portfolio.h
	#$(CC) $(CFLAGS) -c plot.cpp -I C:/Python36-32/include -L C:/Python36-32/libs -l python36 

	$(CC) $(CFLAGS) -c plot.cpp -I C:/Users/Otur1337/Python36-32/include -L C:/Users/Otur1337/Python36-32/libs -l python36


ignorePythonWarnings : CXXFLAGS += -w
ignorePythonWarnings : plot.o

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) main *.o *~

# g++ -g -Wall main.cpp stock.cpp portfolio.cpp -o main -DWITHOUT_NUMPY -std=gnu++11 -I C:/Users/Äma/Python36-32/include -L C:/Users/Äma/Python36-32/libs -l python36
#-c -fmessage-length=0 -std=c++0x 
