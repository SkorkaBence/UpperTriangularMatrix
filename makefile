SRC     = ./src
IDIR    = ./include
TEMPDIR = temp
CXX     = g++
CFLAGS  = -I$(IDIR) -std=c++11
LDFLAGS = -I$(IDIR) -std=c++11
FILES   = main.cpp Matrix/MatrixException.cpp Matrix/UpperTriangularMatrix.cpp Storage/Vector.cpp Storage/VectorException.cpp
TARGET  = run
SOURCES = $(patsubst %,$(SRC)/%,$(FILES))
OBJECTS = $(patsubst %.cpp,$(TEMPDIR)/%.o,$(FILES))
DEPS    = $(patsubst %.cpp,$(TEMPDIR)/%.d,$(FILES))

$(TEMPDIR)/%.o: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) -c $< -O3 -o $@

#$(TEMPDIR)/%.d: $(SRC)/%.cpp
#	$(CXX) $(CFLAGS) -MM -MT $< -MF $@

-include $(DEPS)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -O3 -o $(TARGET)
