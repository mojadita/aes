# $Id: Makefile,v 1.6 2003/11/29 10:44:25 luis Exp $
# Author: Luis.Colorado@HispaLinux.ES
# Date: Wed Nov 12 22:05:54 MET 2003

LDFLAGS = -L.

all: aes

aes_libs =
aes_objs = main.o libaes.a
aes: $(aes_objs)
	$(CC) $(LDFLAGS) -o aes $(aes_objs) $(aes_libs)

libaes.a: \
	libaes.a(addRoundKey.o) \
	libaes.a(mixColumn.o) \
	libaes.a(shiftRows.o) \
	libaes.a(subBytes.o) \
	libaes.a(keyExpansion.o) \
	libaes.a(print.o) \
	libaes.a(aes.o) \
	libaes.a(mult.o)

$(aes_lib_objs) $(aes_objs): aes.h

# $Id: Makefile,v 1.6 2003/11/29 10:44:25 luis Exp $
