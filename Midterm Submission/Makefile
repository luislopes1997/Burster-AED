
# Executable name
PROGNAME = burster

#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -Wall -ansi
#CFLAGS = -Wall

# Debug flags
DBG = -g -Wextra
#DBG = -g

# Optimization flags
OPT = -O3

#CFLAGS += $(DBG)
CFLAGS += $(OPT)

SOURCES = $(wildcard *.c)

OBJECTS = $(SOURCES:.c=.o)



all: $(SOURCES) $(PROGNAME)

$(PROGNAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean depend zip


# Clean directory
clean:
	rm -f *.o core $(PROGNAME) *~ .fuse *.step *.zip

# Build list of dependencies
depend:
	makedepend  -- $(CFLAGS) -Y $(SOURCES)

# Creates the zip file for mooshack submission
zip:
	zip gp13.zip *.c *.h makefile


# DO NOT DELETE THIS LINE

burster.o: matrix.h midterm.h
matrix.o: matrix.h
midterm.o: midterm.h

