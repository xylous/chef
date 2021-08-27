CC 			?= gcc
CFLAGS 		= -O3

BIN_NAME 	= chef
VPATH 		= src:
C_SRC_FILES = $(shell ls -I "*.h" src)
OBJECTS  	= $(C_SRC_FILES:.c=.o)

$(BIN_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

debug: CFLAGS += -g
debug: $(BIN_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(BIN_NAME) $(OBJECTS)
