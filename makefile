SRC     = ./src
IDIR    = ./include
TEMPDIR = temp
CXX     = g++
CFLAGS  = -I$(IDIR) -std=c++11
LDFLAGS = -I$(IDIR) -std=c++11
TARGET  = run
FILES   = main.cpp Matrix/MatrixException.cpp Matrix/UpperTriangularMatrix.cpp Storage/Vector.cpp Storage/VectorException.cpp
SOURCES = $(patsubst %,$(SRC)/%,$(FILES))
OBJECTS = $(patsubst %.cpp,$(TEMPDIR)/%.o,$(FILES))
DEPS    = $(patsubst %.cpp,$(TEMPDIR)/%.d,$(FILES))

$(TEMPDIR)/%.o: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

$(TEMPDIR)/%.d: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) -MM -MT $< -MF $@

-include $(DEPS)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $(TARGET)
