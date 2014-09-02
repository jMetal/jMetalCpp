#
# jMetalCpp Makefile
#
#   Author:
#     Esteban Lopez <esteban@lcc.uma.es>
#
# Instructions:
#    - "make all" to compile everything
#    - Use "spike" target to quick developing and compiling. CMAES_main example
#      is included.
#


# This is the main compiler
CC := g++
# CC := clang --analyze # and comment out the linker last line for sanity

# Source files extension
SRCEXT := cpp

# Source directory
SRCDIR := src

# Build directory
BUILDDIR := build

# Library directory
LIBDIR := lib

# Binaries directory
BINDIR := bin


# Header files directories
HEADER_DIRS := $(shell find $(SRCDIR)/* -type d -print)

# Main files directories
MAIN_DIRS := $(shell find $(SRCDIR) -type d -name main)

# Main source files
MAIN_FILES := $(shell find $(MAIN_DIRS) -type f -name *.$(SRCEXT))

# Binary files
BINARIES := $(patsubst main/%.$(SRCEXT),$(BINDIR)/%,$(MAIN_FILES))

# All source files (including main source files)
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))

# Source files needed to generate the library
LIB_SOURCES := $(filter-out $(MAIN_FILES), $(SOURCES))

# Object files
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(LIB_SOURCES:.$(SRCEXT)=.o))

#BINARIES := $(patsubst $(MAIN_DIRS)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# Flags
CFLAGS := -O3 -std=c++11 # -g # -Wall

# Include flags when compiling
INC := $(patsubst %,-I %/.,$(HEADER_DIRS))


# Library name
LIBNAME := libjmetal.a

# Library path
LIB := $(LIBDIR)/$(LIBNAME)


# Dependencies needed when generating executables	
MAIN_DEPS := $(LIB)

# Libraries needed when generating executables
MAIN_LIBS := -lm #-pthread


# All rule
all: library mains

# Main files rule
mains : $(patsubst $(SRCDIR)%.$(SRCEXT), $(BINDIR)%, $(MAIN_FILES))

# Generic binary file rule
$(BINDIR)/% : $(patsubst $(BINDIR)%, $(SRCDIR)%.cpp, $(BINDIR)/%) $(LIB)
	@echo "Compiling $(patsubst $(BINDIR)%, $(SRCDIR)%.cpp, $@)"
	@mkdir -p $(BINDIR)
	@mkdir -p $(dir $@)
	@echo "$(CC) $(CFLAGS) $(patsubst $(BINDIR)%, $(SRCDIR)%.cpp, $@) $(MAIN_DEPS) -o $@ $(INC) $(MAIN_LIBS)"; $(CC) $(CFLAGS) $(patsubst $(BINDIR)%, $(SRCDIR)%.cpp, $@) $(MAIN_DEPS) -o $@ $(INC) $(MAIN_LIBS)

# Library rule
library : $(LIB)

$(LIB): $(OBJECTS)
	@echo "Creating library..."
	@mkdir -p $(LIBDIR)
	ar -r $(LIB) $^
	ranlib $(LIB)

# Generic object file rule
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

# Clean rule
clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(BINDIR) $(LIBDIR)"; $(RM) -r $(BUILDDIR) $(BINDIR) $(LIBDIR)

# Tests
tester: 

# Spikes (CMAES_main quick developing and compiling example)
spikes : CMAES_main_spike

CMAES_main_spike : $(SRCDIR)/main/CMAES_main.$(SRCEXT) $(LIB)
	@echo "Compiling spike $(SRCDIR)/main/CMAES_main.$(SRCEXT)"
	@mkdir -p $(BINDIR)/spike
	@echo "$(CC) $(CFLAGS) $(SRCDIR)/main/CMAES_main.$(SRCEXT) $(MAIN_DEPS) -o $(BINDIR)/spike/CMAES_main $(INC) $(MAIN_LIBS)"; $(CC) $(CFLAGS) $(SRCDIR)/main/CMAES_main.$(SRCEXT) $(MAIN_DEPS) -o $(BINDIR)/spike/CMAES_main $(INC) $(MAIN_LIBS)

.PHONY: clean