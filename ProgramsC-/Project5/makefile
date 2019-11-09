CXX = g++
CXXFLAGS = -Wall -g

proj5: MusicPlayer.o Song.o driver.cpp
	$(CXX) $(CXXFLAGS) MusicPlayer.o Song.o driver.cpp -o proj5

MusicPlayer.o: MusicPlayer.cpp  MusicPlayer.h Song.o
	$(CXX) $(CXXFLAGS) -c MusicPlayer.cpp

Song.o: Song.cpp Song.h
	$(CXX) $(CXXFLAGS) -c Song.cpp

run:
	./proj5

run1:
	./proj5 p5_music1.txt

val1:
	valgrind ./proj5 p5_music1.txt

clean: 
	rm *.o
	rm *~

