# $Id: Makefile,v 1.9 2003/12/02 20:08:24 luis Exp $
# Author: Luis.Colorado@HispaLinux.ES
# Date: Wed Nov 12 22:05:54 MET 2003

LDFLAGS = -L.
LIB_VERSION = 1.1.0

.SUFFIXES: .c .so .to
.c.to:
	$(CC) $(CFLAGS) -o $*.to -DDEBUG=1 -DMAIN=1 -c $*.c
.c.so:
	$(CC) $(CFLAGS) -fPIC -c $*.c -o $*.so

all: aes libaes.a libaes.so
test: aes_test keyexp_test 
clean:
	$(RM) aes aes_test keyexp_test \
		libaes.a libaes.so libaes.so.$(LIB_VERSION) \
		$(aes_test_objs) $(keyexp_test_objs)

aes_test_objs = aes_test.o aes.to keyExpansion.to libaes.a
aes_test: $(aes_test_objs)
	$(CC) $(LDFLAGS) -o aes_test $(aes_test_objs)

keyexp_test_objs = keyExpansion_test.o keyExpansion.to libaes.a
keyexp_test: $(keyexp_test_objs)
	$(CC) $(LDFLAGS) -o keyexp_test $(keyexp_test_objs)

aes_libs =
aes_objs = main.o libaes.so
aes: $(aes_objs)
	$(CC) $(LDFLAGS) -o aes $(aes_objs) $(aes_libs)

libaes_a_objs = \
	libaes.a(addRoundKey.o) \
	libaes.a(mixColumn.o) \
	libaes.a(shiftRows.o) \
	libaes.a(subBytes.o) \
	libaes.a(keyExpansion.o) \
	libaes.a(print.o) \
	libaes.a(aes.o) \
	libaes.a(mult.o)
libaes.a: $(libaes_a_objs)

libaes.so: libaes.so.$(LIB_VERSION)
	-ln -fs $< $@

libaes_so_objs = \
	addRoundKey.so \
	mixColumn.so \
	shiftRows.so \
	subBytes.so \
	keyExpansion.so \
	print.so \
	aes.so \
	mult.so
libaes.so.$(LIB_VERSION): $(libaes_so_objs)
	$(CC) $(LDFLAGS) -o libaes.so.$(LIB_VERSION) \
		-Wl,-soname=libaes.so.$(LIB_VERSION) \
		-shared $(libaes_so_objs)

$(libaes_a_objs) \
$(libaes_so_objs) \
aes.to keyExpansion.to \
$(aes_objs): aes.h

# $Id: Makefile,v 1.9 2003/12/02 20:08:24 luis Exp $
