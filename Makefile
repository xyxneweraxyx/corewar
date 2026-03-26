# Compilation
TARGET := corewar
CC := clang
FLAGS := -Wall -Wextra -g3 -O2
LIBS :=

# Sources
IGNORE := no_compile

# Normal sources
ALL_SRC := $(shell find . -name '*.c')
ALL_HDR := $(shell find . -name '*.h')

# Filtered sources
IGNORE_PAT := $(IGNORE:%=./%/)
SRC := $(ALL_SRC:$(IGNORE_PAT)%=)
HDR := $(ALL_HDR:$(IGNORE_PAT)%=)

# Objects
OBJ := $(SRC:%.c=obj/%.o)
OBJ_DIRS := $(sort $(dir $(OBJ)))

all: $(TARGET)

$(OBJ_DIRS):
	mkdir -p $@

obj/%.o: %.c | $(OBJ_DIRS)
	$(CC) $(FLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(TARGET) $(LIBS)

clean:
	rm -rf obj/
	rm -rf $(shell find . -name '*.o')
	rm -rf $(shell find . -name '*.c~')
	rm -rf $(shell find . -name '*.h~')
	rm -rf $(shell find . -name '*#*')
	rm -rf $(shell find . -name '*.pch')
	rm -rf $(shell find . -name '*.out')
	rm -rf $(shell find . -name '*~')

fclean: clean
	rm -rf $(shell find . -name '$(TARGET)')

re: fclean $(TARGET)

print_src:
	$(info $(shell find . -name '*.c'))

epiclang_all:
	epiclang $(SRC) $(HDR)