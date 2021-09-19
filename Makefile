CC 			?= gcc
CFLAGS 		= -Wall -Wextra -Wpedantic -O3

BIN_NAME 	= $(shell basename $(shell pwd))
VPATH 		= src:
C_SRC_FILES = $(shell ls -I "*.h" src)
OBJECTS  	= $(C_SRC_FILES:.c=.o)

debug: CFLAGS += -g
debug: $(BIN_NAME)

$(BIN_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(BIN_NAME) $(OBJECTS)
