CXXFLAGS =	-O2 -ggdb -Wall -fmessage-length=0 -Iinclude/

OBJS =		src/main.o  src/NeuralNet.o src/Neuron.o

LIBS =		-lsqlite3

TARGET = 	NeuralNet

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)