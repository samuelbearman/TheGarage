X = g++
CXXFLAGS = -Wall

proj2: Troop.o Game.o proj2.cpp
	$(CXX) $(CXXFLAGS) Troop.o Game.o proj2.cpp -o proj2

Game.o: Troop.o Game.cpp Game.h
	$(CXX) $(CXXFLAGS) -c Game.cpp

Troop.o: Troop.cpp Troop.h
	$(CXX) $(CXXFLAGS) -c Troop.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj2
