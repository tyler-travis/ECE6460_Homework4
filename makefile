CC = g++
CFLAGS = -Wall -c -g
LDFLAGS = -lm
SOURCES = src/main.cpp src/node.cpp src/operator_node.cpp src/operand_node.cpp src/module.cpp src/slicing_tree.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = exec

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm src/*.o
	rm exec
