CXXFLAGS =	-O2 -ggdb -Wall -fmessage-length=0

OBJS =		main.o Net.o

LIBS =		

TARGET = 	NeuralNet

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)