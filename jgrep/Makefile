# $Id: Makefile,v 1.1 2012-10-10 18:30:30-07 hqvo - $

JAVASRC    = jgrep.java messages.java options.java
ALLSOURCE  = ${JAVASRC} Makefile README
MAINCLASS  = jgrep
CLASSES    = ${JAVASRC:.java=.class}
JARCLASSES = ${CLASSES}
JARFILE    = jgrep
LISTING    = ../asg1j-jgrep.code.ps
SUBMITDIR  = cmps012b-wm.f12 asg1

all : ${JARFILE}
	- checksource ${ALLSOURCE}

${JARFILE} : ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm Manifest
	chmod +x ${JARFILE}

%.class : %.java
	- cid + $<
	javac $<

clean :
	- rm ${JARCLASSES}

spotless : clean
	- rm ${JARFILE}

ci : ${ALLSOURCE}
	checksource ${ALLSOURCE}
	cid + ${ALLSOURCE}

lis : ${ALLSOURCE}
	mkpspdf ${LISTING} ${ALLSOURCE}

submit : ${ALLSOURCE}
	submit ${SUBMITDIR} ${ALLSOURCE}

again : ${ALLSOURCE}
	make spotless ci all lis
