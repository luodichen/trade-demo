export CXX = g++
export CXXFLAGS = -fPIC -Wall -O0 -g -std=c++11
export CXXLDFLAGS = -fPIC -g -std=c++11 -pthread
export BIN = bin

export TARGET = $(BIN)/trade-demo

INSTALLPATH = /usr/bin/trade-demo

subdirs = src bin

.PHONY: all
all:$(TARGET)

$(TARGET):
	@for dir in $(subdirs); do $(MAKE) -C $$dir || exit1; done

.PHONY: install
install:$(TARGET)
	cp -f $(TARGET) $(INSTALLPATH)
	
.PHONY: clean
clean:
	rm -f `find . -name "*.o"`
	rm -f $(TARGET)
	rm -f $(INSTALLPATH)
