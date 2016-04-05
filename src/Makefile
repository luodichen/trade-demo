SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

INCLUDE_PATH = ../include

.PHONY: all

all: $(OBJ)
	cp -f *.o ../$(BIN)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_PATH) -c -o $@ $<
	