CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -I/usr/local/include
LIBS = -lgraphblas -lgc

SRCDIR = src
OUTDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OUTDIR)/%.o)

PROGRAM = lisp

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $@

$(OBJECTS): $(OUTDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OUTDIR)/*.o $(PROGRAM)
