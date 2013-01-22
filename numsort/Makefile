# $Id: Makefile,v 1.4 2012-11-01 19:34:52-07 - - $

MKFILE    = Makefile
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS    = gcc -MM
GRIND     = valgrind --leak-check=full

CSOURCE   = inssort.c numsort.c linesort.c
CHEADER   =        inssort.h
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = numsort linesort

SOURCES   = ${CHEADER} ${CSOURCE} ${MKFILE} README

SUBMIT    = submit cmps012b-wm.f12 lab9

all : ${EXECBIN}

numsort: numsort.o inssort.o

linesort: linesort.o inssort.o

%.o : %.c
	${GCC} -c $< -o $@

ci : ${SOURCES}
	cid + ${SOURCES} test*.data
	- checksource $<

submit : ${SOURCES}
	${SUBMIT} ${SOURCES}


ifeq "${NEEDINCL}" ""
include ${DEPSFILE}
endif

