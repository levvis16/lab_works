CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = program

all: $(TARGET)

$(TARGET): main.cpp smartarray.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp smartarray.cpp

clean:
	rm -f $(TARGET)