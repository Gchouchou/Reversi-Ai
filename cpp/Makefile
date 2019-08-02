CC := g++
CFLAGS_PRE := -std=c++17 -Wall -MMD
CFLAGS_DEBUG := -g
SRCDIR := src
BUILDDIR := build
INCDIR := include
SRCEXT := cc
LIBS := -lncurses
TARGET := bin/reversi

SOURCES := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
SOURCENAMES:= $(notdir $(SOURCES))
SOURCEDIRS := $(sort $(dir $(SOURCES)))
HEADERDIRS := $(sort $(shell find . -type f -name '*.h' -printf "%h\n"))
OBJECTS := $(patsubst %.$(SRCEXT),$(BUILDDIR)/%.o,$(SOURCENAMES))
DEP := $(OBJECTS:.o=.d)
INC := $(addprefix -I ,$(HEADERDIRS))
CFLAGS := $(CFLAGS_PRE)
# looks for any source files in sourcedir
vpath %.$(SRCEXT) $(SOURCEDIRS)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	$(CC) $^ $(LIBS) -o $@

$(BUILDDIR)/%.o: %.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

-include $(DEP)

clean:
	@echo " Cleaning..."; 
	$(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean

debug: CFLAGS := $(CFLAGS_PRE) $(CFLAGS_DEBUG) $(INC)
debug: $(TARGET)
