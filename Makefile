# $Id: Makefile,v 1.2 2003/11/13 21:45:12 luis Exp $
# Author: Luis.Colorado@HispaLinux.ES
# Date: Wed Nov 12 22:05:54 MET 2003

pru_objs = pru.o mult.o pow.o subBytes.o
pru_libs =
pru: $(pru_objs)
	$(CC) $(LDFLAGS) -o pru $(pru_objs) $(pru_libs)
$(pru_objs): aes.h

# $Id: Makefile,v 1.2 2003/11/13 21:45:12 luis Exp $
