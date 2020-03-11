CC = g++
CFLAGS = -Wall -O2 -I../c++ -mcx16 -march=native -DCILK -fcilkplus -std=c++17
LIB_PATH=
LIBS=
# Unfortunately, I suck at creating Makefiles
SOURCES_TMP1=$(wildcard src/*.cpp)
SOURCES_TMP2=$(subst src/test.cpp,,${SOURCES_TMP1})
SOURCES=$(subst src/benchmark.cpp,,${SOURCES_TMP2})

OBJECTS_TMP=$(patsubst %.cpp, %.o, $(SOURCES))
OBJECTS=$(patsubst src/%, obj/%, $(OBJECTS_TMP))
EXECUTABLES = bin/test bin/benchmark
# Headers that contain code that cannot be moved to .cpp
# files, likely due to language restrictions (inline/templates)
EXEC_HEADERS = src/headers/rmat.h

all: build $(EXECUTABLES)

$(EXECUTABLES): bin/%: src/%.cpp $(OBJECTS)
	$(CC) $(CFLAGS) $< $(OBJECTS) $(LIB_PATH) $(LIBS) -o $@

$(OBJECTS): obj/%.o : src/%.cpp $(EXEC_HEADERS)
	$(CC) $(CFLAGS) -c $< $(LIB_PATH) $(LIBS) -o $@

build:
	@mkdir -p bin
	@mkdir -p obj

clean:
	rm -rf bin
	rm -rf obj
