.PHONY: all clean
CPPFLAGS ?= -Wall -pedantic -std=c++20 -I$(PACS_ROOT)/include -I./include

EXEC = main
SOURCE = main.cpp
OBJECT = main.o
OBJECTS = Vector.o Solver.o Parameters.o Arguments.o Target.o
PARAMETERS = parameters.json

# Rules.
all: $(EXEC)

$(EXEC): $(OBJECTS) $(OBJECT)
	$(MAKE) $(PARAMETERS)
	$(CXX) $(CPPFLAGS) $^ -o $(EXEC)

$(OBJECT): $(SOURCE)
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(OBJECTS): %.o: ./src/%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(PARAMETERS): defaults.json
	@cp defaults.json parameters.json

# Clean.
clean:
	$(RM) *.o
	$(RM) $(EXEC)