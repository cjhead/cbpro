# Paths
PREFIX=/usr
INCPREFIX=$(PREFIX)/include
LIBPREFIX=$(PREFIX)/lib

# Flags
CC=gcc
CFLAGS=-g -Wall
LDLIBS=-lcurl -lcrypto -lm

SRC=src
OBJ=obj
LIBDIR=lib
LIB_STATIC=$(LIBDIR)/libcbpro.a
LIB_SHARED=$(LIBDIR)/libcbpro.so
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)%.c, $(OBJ)/%.o, $(SRCS))
TEST=get_product\
	 get_all_products\
	 get_product_book\
	 get_product_candles\
	 get_product_stats\

all: $(LIB_SHARED)

test: $(LIB_SHARED) $(TEST)


$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LDLIBS) -c $^ -o $@

$(LIB_STATIC): $(OBJS)
	@mkdir -p $(@D)
	ar -rcs $@ $^

$(LIB_SHARED): $(SRCS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LDLIBS) -fPIC -shared $^ -o $@

$(TEST):
	@mkdir -p test/bin
	$(CC) $(CFLAGS) $(LDLIBS) test/src/$@.c -o test/bin/$@ -L./lib -lcbpro

install: all
	mkdir -p $(DESTDIR)$(LIBPREFIX)
	mkdir -p $(DESTDIR)$(INCPREFIX)
	cp -f $(LIB_SHARED) $(DESTDIR)$(LIBPREFIX)
	cp -f src/cbpro.h $(DESTDIR)$(INCPREFIX)

uninstall:
	rm -f $(DESTDIR)$(LIBPREFIX)/libcbpro.so
	rm -f $(DESTDIR)$(INCPREFIX)/cbpro.h

clean:
	rm -f $(OBJ)/* test/bin/* lib/*

.PHONY: all test clean
