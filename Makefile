CC = g++
CFLAGS = -O2 -I../c++ -mcx16 -march=native -DCILK -fcilkplus -std=c++11
LIB_PATH=
LIBS=
SOURCES=$(wildcard src/*.cpp)
OBJECTS_TMP=$(patsubst %.cpp, %.o, $(SOURCES))
OBJECTS=$(patsubst src/%, obj/%, $(OBJECTS_TMP))
EXECUTABLE=bin/test

all: build $(EXECUTABLE)

$(EXECUTABLE):  $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIB_PATH) $(LIBS)

$(OBJECTS): obj/%.o : src/%.cpp
	$(CC) $(CFLAGS) -c $< $(LIB_PATH) $(LIBS) -o $@

build:
	@mkdir -p bin
	@mkdir -p obj

clean:
	rm -rf bin
	rm -rf obj
