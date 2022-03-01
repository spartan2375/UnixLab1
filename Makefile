ROOT=../apue# Change this to apue root
PLATFORM=linux#$(shell $(ROOT)/systype.sh)
CFLAGS= -g -Wall
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	shell2 myshell

all:	$(PROGS)

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.libapue.inc
