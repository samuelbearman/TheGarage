CXX = g++
CXXFLAGS = -g


driver: SqList.o INode.o DNode.o Int341.o driver.cpp
	$(CXX) $(CXXFLAGS) SqList.o INode.o DNode.o Int341.o driver.cpp -o driver

SqList.o: Int341.o INode.o DNode.o SqList.h SqList.cpp
	$(CXX) $(CXXFLAGS) -c SqList.cpp

INode.o: Int341.o DNode.o INode.h INode.cpp
	$(CXX) $(CXXFLAGS) -c INode.cpp

DNode.o: DNode.h DNode.cpp Int341.o
	$(CXX) $(CXXFLAGS) -c DNode.cpp

Int341.o: Int341.h Int341.cpp
	$(CXX) $(CXXFLAGS) -c Int341.cpp

clean:
	rm *.o
	rm *~

run:
	./driver
