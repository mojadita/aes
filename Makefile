# $Id: Makefile,v 1.4 2003/11/27 00:55:09 luis Exp $
# Author: Luis.Colorado@HispaLinux.ES
# Date: Wed Nov 12 22:05:54 MET 2003

all: aes

aes_objs = aes.o libaes.a
aes: $(aes_objs)
	$(CC) $(LDFLAGS) -o aes $(aes_objs) $(aes_libs)

aes_lib_objs = \
	libaes.a(addRoundKey.o) \
	libaes.a(mixColumn.o) \
	libaes.a(shiftRows.o) \
	libaes.a(subBytes.o) \
	libaes.a(keyExpansion.o) \
	libaes.a(print.o) \
	libaes.a(mult.o)
libaes.a: $(aes_lib_objs)

$(aes_lib_objs) $(aes_objs): aes.h

# $Id: Makefile,v 1.4 2003/11/27 00:55:09 luis Exp $
