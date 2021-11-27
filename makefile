CXX = g++
CFLAGS = -g -Wall

CPPFILES = src/main.cpp src/calcfile.cpp src/fileutils.cpp
OBJFILES = $(CPPFILES:.cpp=.o)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJFILES)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

clean:
	$(RM) $(OBJFILES)
	$(RM) $(TARGET)
