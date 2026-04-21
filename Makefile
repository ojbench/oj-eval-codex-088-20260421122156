CXX := g++
CXXFLAGS := -O2 -pipe -static -s -std=c++17

all: code

code: code.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f code *.o

