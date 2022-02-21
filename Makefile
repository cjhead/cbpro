CC=gcc
CFLAGS=-g -Wall
LDLIBS=-lcurl -lcrypto -lm
SRC=src
OBJ=obj
LIBDIR=lib/
LIB_STATIC=$(LIBDIR)/libcbpro.a
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)%.c, $(OBJ)/%.o, $(SRCS))
TEST=get_product\
	 get_all_products\
	 get_product_book\
	 get_product_candles\
	 get_product_stats\

all: $(LIB_STATIC)
test: $(LIB_STATIC) $(TEST)

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LDLIBS) -c $^ -o $@

$(LIB_STATIC): $(OBJS)
	@mkdir -p $(@D)
	ar -rcs $@ $^

$(TEST):
	@mkdir -p test/bin
	$(CC) $(CFLAGS) $(LDLIBS) test/src/$@.c -o test/bin/$@ -L./lib -lcbpro

clean:
	rm $(OBJ)/* test/bin/* lib/*
	rmdir $(OBJ) test/bin lib
