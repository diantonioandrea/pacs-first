.PHONY: all clean
CXXFLAGS = -Wall -pedantic -std=c++20  -I./include

# MuParser and json.
CPPFLAGS = -I$(PACS_ROOT)/include
LDFLAGS = -L$(PACS_ROOT)/lib
LDLIBS = -lmuparser

# Optimization.
# CXXFLAGS += -O2 -DNDEBUG

EXEC = main
SOURCE = main.cpp
OBJECT = main.o
OBJECTS = Vector.o Solver.o Parameters.o Arguments.o Target.o
PARAMETERS = parameters.json
DEFAULTS = defaults.json

# Rules.
all: $(EXEC) $(PARAMETERS)

$(EXEC): $(OBJECTS) $(OBJECT)
	$(CXX) $(LDFLAGS) $(LDLIBS) $^ -o $(EXEC)

$(OBJECT): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJECTS): %.o: ./src/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(PARAMETERS): $(DEFAULTS)
	cp $(DEFAULTS) $(PARAMETERS)

# Clean.
clean:
	$(RM) *.o
	$(RM) $(EXEC)
	$(RM) $(PARAMETERS)