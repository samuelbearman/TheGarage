CXX = g++
CXXFLAGS = -g

driver: Point.o BBox.o QTNode.o QTree.o p3test02.cpp
	$(CXX) $(CXXFLAGS) Point.o BBox.o QTNode.o QTree.o p3test02.cpp -o driver

#driver: Point.o BBox.o QTNode.o QTree.o driver.cpp
#	$(CXX) $(CXXFLAGS) Point.o BBox.o QTNode.o QTree.o driver.cpp -o driver

QTree.o: Point.o BBox.o QTNode.o QTree.h QTree.cpp
	$(CXX) $(CXXFLAGS) -c QTree.cpp

QTNode.o: Point.o BBox.o QTNode.h QTNode.cpp
	$(CXX) $(CXXFLAGS) -c QTNode.cpp

BBox.o: Point.o BBox.h BBox.cpp
	$(CXX) $(CXXFLAGS) -c BBox.cpp

Point.o: Point.h Point.cpp
	$(CXX) $(CXXFLAGS) -c Point.cpp

clean:
	rm *.o
	rm *~

