CXX = g++
CXXFLAGS = -Wall -std=c++11 -g
SRCS = command.cpp document.cpp DocumentController.cpp ECEditorTest.cpp ECTextViewImp.cpp 
OBJS = $(SRCS:.cpp=.o)
TARGET = MyEditor

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)


.PHONY: all clean