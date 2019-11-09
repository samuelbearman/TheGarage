CXX = g++
CXXFLAGS = -Wall

proj3: Cipher.o driver.cpp
	$(CXX) $(CXXFLAGS) Cipher.o CipherString.o driver.cpp -o proj3

Cipher.o: CipherString.o Cipher.cpp Cipher.h
	$(CXX) $(CXXFLAGS) -c Cipher.cpp

CipherString.o: CipherString.cpp CipherString.h Node.h
	$(CXX) $(CXXFLAGS) -c CipherString.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj3

run1:
	./proj3 proj3_t1.txt

run2:
	./proj3 proj3_t2.txt

run3:
	./proj3 proj3_t3.txt