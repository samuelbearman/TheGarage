CXX = g++
CXXFLAGS = -Wall

#proj4: User.o Computer.o main.o 
#	$(CXX) $(CXXFLAGS) User.o Computer.o main.o -o proj4 

#main.o: User.o Computer.o main.cpp
#	$(CXX) $(CXXFLAGS) -c main.cpp

proj4: User.o Computer.o Player.o Grid.o main.cpp
	$(CXX) $(CXXFLAGS) User.o Computer.o Player.o Grid.o main.cpp -o proj4

User.o: Player.o User.cpp User.h
	$(CXX) $(CXXFLAGS) -c User.cpp

Computer.o: Player.o Computer.cpp Computer.h
	$(CXX) $(CXXFLAGS) -c Computer.cpp

#proj4: Player.o Grid.o main.cpp
#	$(CXX) $(CXXFLAGS) Player.o Grid.o main.cpp -o proj4

Player.o: Player.cpp Player.h Grid.h
	$(CXX) $(CXXFLAGS) -c Player.cpp

Grid.o: Grid.cpp Grid.h
	$(CXX) $(CXXFLAGS) -c Grid.cpp

clean:
	rm *.o*
	rm *~

run:
	./proj4

run1:
	./proj4 p4_comp1.txt p4_user1.txt

run2:
	./proj4 p4_comp2.txt p4_user2.txt

run3:
	./proj4 p4_comp3.txt p4_user3.txt
