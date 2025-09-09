CC = gcc
CFLAGS = -Iinclude -MMD -MP

SRC = $(wildcard src/*.c) main.c
OBJ = $(patsubst %.c, build/%.o, $(notdir $(SRC)))
DEP = $(OBJ:.o=.d)

OUT  = build/program
DUMP = build/dump.txt

all: $(OUT) $(DUMP)

$(DUMP): $(OUT)
	objdump -d $(OUT) > $@

# Link step
$(OUT): $(OBJ)
	$(CC) -o $@ $^

# Compile step (put .o into build/)
build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: %.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build/ exists
build:
	mkdir -p build

clean:
	rm -rf build

-include $(DEP)

.PHONY: all clean build

