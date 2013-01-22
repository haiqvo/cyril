# $Id: Makefile,v 1.4 2012-11-01 19:34:52-07 - - $

MKFILE    = Makefile
DEPSFILE  = ${MKFILE}.deps
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS    = gcc -MM
GRIND     = valgrind --leak-check=full

CSOURCE   = l8stat.c
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = l8stat
SOURCES   = ${CSOURCE} ${MKFILE} README
SUBMIT    = submit cmps012b-wm.f12 lab8

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

%.o : %.c
	cid + $<
	${GCC} -c $<

ci : ${SOURCES}
	cid + ${SOURCES} test*.data


clean :
	- rm ${OBJECTS} ${DEPSFILE} core ${OUTPUT}

spotless : clean
	- rm ${EXECBIN}

deps : ${CSOURCE}
	@ echo "# ${DEPSFILE} created `date`" >${DEPSFILE}
	${MKDEPS} ${CSOURCE} | sort | uniq >>${DEPSFILE}

${DEPSFILE} :
	@ touch ${DEPSFILE}
	${MAKE} --no-print-directory deps

submit :
	${SUBMIT} ${SOURCES}

again :
	gmake spotless deps ci all lis

ifeq "${NEEDINCL}" ""
include ${DEPSFILE}
endif

