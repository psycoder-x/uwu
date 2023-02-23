CC = gcc
LD = gcc

WARNS = -Wall -Wextra -Werror -pedantic -pedantic-errors
CFLAGS = -std=c99 -O3 ${WARNS}
LFLAGS = -s

SRC = src
OBJ = obj
BIN = bin

OBJ_LIST = \
	${OBJ}/main.o \
	${OBJ}/lib/str.o \
	${OBJ}/tmtime.o \

EXEC = ${BIN}/uwu

.PHONY: all clean

all: ${EXEC}

clean:
	rm -r ${BIN}/*
	rm -r ${OBJ}/*

${OBJ}:
	mkdir ${OBJ}

${OBJ}/lib:
	mkdir ${OBJ}/lib

${BIN}:
	mkdir ${BIN}

${EXEC}: ${OBJ_LIST} | ${BIN}
	${LD} -o $@ ${OBJ_LIST} ${LFLAGS}

${OBJ}/%.o: ${SRC}/%.c | ${OBJ} ${OBJ}/lib
	${CC} ${CFLAGS} -c $< -o $@
