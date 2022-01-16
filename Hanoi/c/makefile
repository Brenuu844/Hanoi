# Project name
PROJ_NAME=hanoi

# Compiler
CC=<compiler_path>

# Flags for compiler
CC_FLAGS=-c        \
         -ansi     \
		 -W        \
		 -Wall     \
         -pedantic

#
# Compiling and linking
#

all: $(PROJ_NAME)

$(PROJ_NAME): ./hanoi.o
	$(CC) -o $@ $^

./hanoi.o: ./hanoi.c
	$(CC) -o $@ $< $(CC_FLAGS)

clean:
	del *.o
	rm $(PROJ_NAME).exe
