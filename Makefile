.PHONY: all clean
CPPFLAGS ?=  -L$(PACS_ROOT)/lib -lmuparser
CXXFLAGS ?= -Wall -pedantic -std=c++20 -I$(PACS_ROOT)/include -I./include

EXEC = main
SOURCE = main.cpp
OBJECT = main.o
OBJECTS = Vector.o Solver.o Parameters.o Arguments.o Target.o
PARAMETERS = parameters.json
DEFAULTS = defaults.json

# Rules.
all: $(EXEC) $(PARAMETERS)

$(EXEC): $(OBJECTS) $(OBJECT)
	$(CXX) $(CPPFLAGS) $^ -o $(EXEC)

$(OBJECT): $(SOURCE)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJECTS): %.o: ./src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PARAMETERS): $(DEFAULTS)
	cp $(DEFAULTS) $(PARAMETERS)

# Clean.
clean:
	$(RM) *.o
	$(RM) $(EXEC)
	$(RM) $(PARAMETERS)