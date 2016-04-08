SRC = $(wildcard *.o)
TARGET_THIS = $(notdir $(TARGET))
LIBPATH = ../lib
LIBS = -lthostmduserapi -lthosttraderapi

.PHONY: all
all: $(TARGET_THIS)

$(TARGET_THIS):
	$(CXX) $(CXXLDFLAGS) -L$(LIBPATH) $(LIBS) -o $(TARGET_THIS) $(SRC)
