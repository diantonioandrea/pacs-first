# PACS - First Challenge.
# Andrea Di Antonio, 10655477.
.PHONY: all clean
CPPFLAGS ?= -Wall -pedantic -std=c++20 -O2 -pipe -mtune=native -march=native

EXEC = main
SOURCE = main.cpp
OBJECT = main.o

# Headers' .cpp files to be compiled.
OBJECTS = Vector.o Solver.o Parameters.o Default.o Arguments.o

# Rules.
all: $(EXEC)

$(EXEC): $(OBJECTS) $(OBJECT)
	$(CXX) $(CPPFLAGS) $^ -o $(EXEC)

$(OBJECT): $(SOURCE)
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(OBJECTS): %.o: ./src/%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

# Clean.
clean:
	$(RM) *.o
	$(RM) $(EXEC)