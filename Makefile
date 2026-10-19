# OPTIONS
CC := gcc

TARGET   := maya
SRCDIR   := src
INCDIR   := include
LIBDIR   := lib
BUILDDIR := build
BINDIR   := bin

# LIBRARIES (space-separated)
LIBS     := libtomlc17.so.1.0

CFLAGS  += -g -Wall -Wextra -Wpedantic -std=c99 -I$(INCDIR)
LDFLAGS += -L$(LIBDIR) -Wl,-rpath,'$$ORIGIN/../lib'

LDLIBS := $(addprefix $(LIBDIR)/,$(LIBS))

# FILES
SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

# LINK
$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $@

# COMPILE
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# CLEAN
clean:
	rm -rf $(BUILDDIR) $(BINDIR)

.PHONY: clean
