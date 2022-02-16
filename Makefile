CC=gcc
CFLAGS=-g -Wall
# LDLIBS=-lcurl -lcrypto -lm -lcjson -lcbpro
LDLIBS=-lcurl -lcrypto -lm -lcjson
# LDLIBS=-lcurl -lcrypto -lm
SRC=src
OBJ=obj
BINDIR=bin
BIN=$(BINDIR)/cbpro
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)%.c, $(OBJ)/%.o, $(SRCS))

all:$(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(LDLIBS) -c $^ -o $@

clean:
	rm $(BINDIR)/* $(OBJ)/*
