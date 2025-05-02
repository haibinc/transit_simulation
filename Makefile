CXX = g++
CXXFLAGS = -g -Wall -std=c++11
TARGET = main.exe
SRCS = main.cpp Route.cpp Bus.cpp Vehicle.cpp Stop.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)