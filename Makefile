.PHONY: all clean
CXXFLAGS = -Wall -pedantic -std=c++20  -I./include

# MuParser and json.
CXXFLAGS += -I$(PACS_ROOT)/include
CPPFLAGS = -L$(PACS_ROOT)/lib -lmuparser

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