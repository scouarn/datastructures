CC := gcc
CFLAGS := -O3 -Wall -std=c99
LINK := -lm -lpthread -lc

INC_DIR := include/
SRC_DIR := source/
OBJ_DIR := bin/
LIB_DIR := /lib/

SRC := $(wildcard $(SRC_DIR)*.c)
OBJ := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

TGT_LN := -lstruct
TGT_SO := libstruct.so

TEST = test


.PHONY: all
all : $(TGT_SO) $(TEST)

.PHONY: lib
lib : $(TGT_SO)


.PHONY : install
install: all
	cp $(TGT_SO) $(LIB_DIR)

.PHONY : runtest
runtest:
	export LD_LIBRARY_PATH=`pwd`
	./test

$(TGT_SO) : $(OBJ)
	$(CC) $(CFLAGS) $(LINK) -lc -shared -o $@ $^


$(TEST) : $(TGT_SO) $(OBJ_DIR)$(TEST).o
	$(CC) $(CFLAGS) $(LINK) -I$(INC_DIR) -L./ $(TGT_LN) -o $@ $^



$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -fpic -c -o $@ $<



clean :
	rm -f */*.o $(TGT)