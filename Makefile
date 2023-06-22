TARGET = checkers
CC = gcc
SRC_DIR = src
INC_DIRS = inc
CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -g $(addprefix -I, $(INC_DIRS))

SOURCES = $(shell find $(SRC_DIR) -name '*.c')
OBJECTS = $(SOURCES:.c=.o)
DEPS = $(OBJECTS:.o=.d)

.PHONY: all clean
all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -MMD -o $@ -c $<
clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET)
-include $(DEPS)
