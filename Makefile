
#CXXFLAGS := -std=c++11 -march=native -fopenmp
CXXFLAGS := -std=c++11 -march=cooperlake -fopenmp

INCLUDES := \
-I. \
-I./baseline \
-I./optimization1 \
-I./optimization2 \
-I./optimization3 \
-I./optimization4 \
-I./optimization5 \
-I./optimization6 \
-I./optimization7 \
-I./optimization8 \

#CORE_SRC := helper.cc

main: main.o baseline.o helper.o optimization1.o optimization2.o optimization3.o optimization4.o optimization5.o optimization6.o optimization7.o optimization8.o
	g++ -g $(CXXFLAGS) -o main main.o baseline.o helper.o optimization1.o optimization2.o optimization3.o optimization4.o optimization5.o optimization6.o optimization7.o optimization8.o
main.o: main.cpp 
	g++ -g $(CXXFLAGS) $(INCLUDES) -c main.cpp 
baseline.o: ./baseline/baseline.cpp 
	g++ -g $(CXXFLAGS) $(INCLUDES) -c ./baseline/baseline.cpp 
optimization1.o: ./optimization1/optimization1.cpp 
	g++ -g $(CXXFLAGS) $(INCLUDES) -c ./optimization1/optimization1.cpp 
optimization2.o: ./optimization2/optimization2.cpp 
	g++ -g $(CXXFLAGS) $(INCLUDES) -c ./optimization2/optimization2.cpp
optimization3.o: ./optimization3/optimization3.cpp 
	g++ -g $(CXXFLAGS) $(INCLUDES) -c ./optimization3/optimization3.cpp
optimization4.o: ./optimization4/optimization4.cpp 
	g++ -g $(CXXFLAGS) $(INCLUDES) -c ./optimization4/optimization4.cpp
optimization5.o: ./optimization5/optimization5.cpp 
	g++ -g $(CXXFLAGS) $(INCLUDES) -c ./optimization5/optimization5.cpp
optimization6.o: ./optimization6/optimization6.cpp
	g++ -g $(CXXFLAGS) $(INCLUDES) -c ./optimization6/optimization6.cpp
optimization7.o: ./optimization7/optimization7.cpp
	g++ -g $(CXXFLAGS) $(INCLUDES) -c ./optimization7/optimization7.cpp
optimization8.o: ./optimization8/optimization8.cpp
	g++ -g $(CXXFLAGS) $(INCLUDES) -c ./optimization8/optimization8.cpp
helper.o: helper.cc
	g++ -g $(CXXFLAGS) $(INCLUDES) -c helper.cc
clean:
	rm main *.o