CC=gcc
CFLAGS=-g -Wall
LDLIBS=-lcurl -lcrypto -lm
SRC=src
OBJ=obj
LIBDIR=lib/
LIB_STATIC=$(LIBDIR)/libcbpro.a
TEST=test/bin/get_product
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)%.c, $(OBJ)/%.o, $(SRCS))

all: $(LIB_STATIC)
test: $(LIB_STATIC) $(TEST)

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LDLIBS) -c $^ -o $@

$(LIB_STATIC): $(OBJS)
	@mkdir -p $(@D)
	ar -rcs $@ $^

$(TEST): test/src/get_product.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o $@ -L./lib -lcbpro

clean:
	rm $(OBJ)/* test/bin/* lib/*
	rmdir $(OBJ) test/bin lib
