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
CFLAGS  = -g -Wall -Wl,-subsystem,console -std=c++0x 


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
main: main.o portfolio.o stock.o readfile.o 
	$(CC) $(CFLAGS) -o main main.o portfolio.o stock.o readfile.o -DWITHOUT_NUMPY -I C:/Users/Otur1337/Python36-32/include -L C:/Users/Otur1337/Python36-32/libs -l python36


# To create the object file main.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
#main.o: main.cpp portfolio.h stock.h readfile.h
#	$(CC) $(CFLAGS) -c hello.cpp 

# To create the object file counter.o, we need the source files
# counter.c and counter.h:
#
main.o:  main.cpp portfolio.h readfile.h stock.h matplotlibcpp.h
	$(CC) $(CFLAGS) -c main.cpp -DWITHOUT_NUMPY -I C:/Users/Otur1337/Python36-32/include -L C:/Users/Otur1337/Python36-32/libs -l python36



portfolio.o:  portfolio.cpp portfolio.h readfile.h stock.h
	$(CC) $(CFLAGS) -c portfolio.cpp

readfile.o:  readfile.cpp portfolio.h readfile.h stock.h 
	$(CC) $(CFLAGS) -c readfile.cpp

stock.o:  stock.cpp portfolio.h readfile.h stock.h
	$(CC) $(CFLAGS) -c stock.cpp

matplotlibcpp.o:  .cpp portfolio.h readfile.h stock.h
	$(CC) $(CFLAGS) -c stock.cpp


# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) main *.o *~

# g++ -g -Wall main.cpp stock.cpp portfolio.cpp -o main -DWITHOUT_NUMPY -std=gnu++11 -I C:/Users/Otur1337/Python36-32/include -L C:/Users/Otur1337/Python36-32/libs -l python36
#-c -fmessage-length=0 -std=c++0x 
