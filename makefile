
TARGET=modo
BUILDDIR=build
SRCDIR=src
SRC= $(shell find $(SRCDIR) -name "*.cpp")
OBJ= $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo Compiling $@
	@g++ -o $@ $^ -lncurses
	@echo "Built target: $@"

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	@g++ -c -o $@ $<



