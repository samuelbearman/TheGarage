CXX = g++
CXXFLAGS = -Wall -g

driver: SortedSquareList.o SSLColumn.o driver.cpp
	$(CXX) $(CXXFLAGS) SortedSquareList.o SSLColumn.o driver.cpp -o driver

SortedSquareList.o: SSLColumn.o SortedSquareList.cpp SortedSquareList.h
	$(CXX) $(CXXFLAGS) -c SortedSquareList.cpp  

SSLColumn.o: SSLColumn.cpp SSLColumn.h
	$(CXX) $(CXXFLAGS) -c SSLColumn.cpp

run:
	./driver

clean:
	rm *.o
	rm *~

