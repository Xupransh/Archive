CXX = clang++
LD = clang++
CXXFLAGS = $(CS255) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LDFLAGS = -std=c++1y -stdlib=libc++ -lpthread -lm

.DEFAULT_GOAL := mp1

mp1 : mp1.o main.o PNG.o HSLAPixel.o lodepng.o
	$(LD) mp1.o main.o PNG.o HSLAPixel.o lodepng.o $(LDFLAGS) -o mp1

main.o : main.cpp mp1.h cs225/PNG.h
	$(CXX) $(CXXFLAGS) main.cpp

PNG.o : cs225/PNG.cpp cs225/PNG.h cs225/HSLAPixel.h cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/PNG.cpp

HSLAPixel.o : cs225/HSLAPixel.cpp cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs225/HSLAPixel.cpp

lodepng.o : cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/lodepng/lodepng.cpp

test : unit_tests.o mp1.o PNG.o HSLAPixel.o lodepng.o
	$(LD) unit_tests.o mp1.o PNG.o HSLAPixel.o lodepng.o $(LDFLAGS) -o test

unit_tests.o : tests/unit_tests.cpp tests/catch.hpp cs225/PNG.h cs225/HSLAPixel.h
	$(CXX)	$(CXXFLAGS)	tests/unit_tests.cpp

clean :
	-rm -f *.o test mp1
