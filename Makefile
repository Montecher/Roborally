NAME = app

CXX = g++
LD = g++
RM = rm -f

CFLAGS = -Wall -Wextra --std=c++14 -pedantic -g
LDFLAGS = -lpthread

MODULES = board test Graph

SOURCES = $(foreach module, $(MODULES), src/$(module).cpp)
OBJS    = $(foreach module, $(MODULES), build/$(module).o)
DEPS    = $(foreach module, $(MODULES), build/$(module).d)
HEADERS = $(wildcard src/*.hpp)
BINARY  = out/$(NAME)

all: $(BINARY)
run: all
	./$(BINARY) appdata/board.txt

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
mrproper: clean
	$(RM) $(BINARY)

build/%.o: src/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

build/%.d: src/%.cpp $(HEADERS)
	@echo 'echo build/$$(shell $(CXX) -M $<) > $@'
	@echo build/$(shell $(CXX) -M $<) > $@

$(BINARY): $(OBJS)
	$(LD) $^ -o $@ $(LDFLAGS)

-include $(DEPS)

.PHONY: all run clean mrproper
