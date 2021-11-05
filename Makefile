CC := gcc
CFLAGS := -O3 -Wall -std=c89 -pedantic
LINK := -lm -lpthread -lc

INC_DIR := include/
SRC_DIR := source/
OBJ_DIR := bin/
LIB_DIR := /usr/lib/

SRC := $(wildcard $(SRC_DIR)*.c)
OBJ := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

LIB_LN := -lstruct
LIB_SO := libstruct.so

TEST = test


.PHONY: all
all : $(LIB_SO) $(TEST)

.PHONY: lib
lib : $(LIB_SO)


.PHONY : install
install: all
	cp $(LIB_SO) $(LIB_DIR)

.PHONY : runtest
runtest: $(TEST)
	./runtest.sh

$(LIB_SO) : $(OBJ)
	$(CC) $(CFLAGS) $(LINK) -lc -shared -o $@ $^


$(TEST) : $(LIB_SO) $(OBJ_DIR)$(TEST).o
	$(CC) $(CFLAGS) $(LINK) -I$(INC_DIR) -L./ $(LIB_LN) -o $@ $^



$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -fpic -c -o $@ $<



clean :
	rm -f */*.o $(TEST)