
CXXFLAGS := -std=c++11 -march=native -fopenmp
INCLUDES := \
-I. \
-I./baseline \
-I./optimization1 \
-I./optimization2 \
-I./optimization3 \
-I./optimization4 \

#CORE_SRC := helper.cc

main: main.o baseline.o helper.o optimization1.o optimization2.o optimization3.o optimization4.o
	g++ -g $(CXXFLAGS) -o main main.o baseline.o helper.o optimization1.o optimization2.o optimization3.o optimization4.o
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
helper.o: helper.cc
	g++ -g $(CXXFLAGS) $(INCLUDES) -c helper.cc
clean:
	rm main *.o