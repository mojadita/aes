# $Id: Makefile,v 1.3 2003/11/26 23:30:14 luis Exp $
# Author: Luis.Colorado@HispaLinux.ES
# Date: Wed Nov 12 22:05:54 MET 2003

aes_lib_objs = \
	libaes.a(addRoundKey.o) \
	libaes.a(mixColumn.o) \
	libaes.a(shiftRows.o) \
	libaes.a(subBytes.o) \
	libaes.a(mult.o)

libaes.a: $(aes_lib_objs)

$(aes_lib_objs): aes.h

# $Id: Makefile,v 1.3 2003/11/26 23:30:14 luis Exp $
