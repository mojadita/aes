# $Id: Makefile,v 1.7 2003/11/29 22:02:04 luis Exp $
# Author: Luis.Colorado@HispaLinux.ES
# Date: Wed Nov 12 22:05:54 MET 2003

LDFLAGS = -L.

.SUFFIXES: .c .so

all: aes libaes.a

aes_libs =
aes_objs = main.o libaes.so
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

libaes_so_objs = \
	addRoundKey.so \
	mixColumn.so \
	shiftRows.so \
	subBytes.so \
	keyExpansion.so \
	print.so \
	aes.so \
	mult.so
libaes.so: libaes.so.1.1.0
	-ln -s $< $@
libaes.so.1.1.0: $(libaes_so_objs)
	$(CC) $(LDFLAGS) -o libaes.so.1.1.0 -Wl,-soname=libaes.so.1.1.0 -shared $(libaes_so_objs)

.c.so:
	$(CC) $(CFLAGS) -fPIC -c $*.c -o $*.so

$(aes_lib_objs) $(aes_objs): aes.h

# $Id: Makefile,v 1.7 2003/11/29 22:02:04 luis Exp $
