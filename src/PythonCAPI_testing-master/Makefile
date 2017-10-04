CXXFLAGS :=  -IC:/Users/Otur1337/Python36-32/include 
LDFLAGS := -LC:/Users/Otur1337/Python36-32/libs 
LDLIBS := -lfftw3 -lm -lpython36

EXECUTABLE := testEmbed


all: $(EXECUTABLE)

testEmbed: testEmbed.o
	g++ testEmbed.o -o $(EXECUTABLE) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

testEmbed.o: testEmbed.cpp
	g++ -c testEmbed.cpp $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

clean:
	rm -rf *o $(EXECUTABLE)
