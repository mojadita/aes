/* $Id: pow.c,v 1.1 2003/11/12 00:17:56 luis Exp $
 * Author: Luis Colorado <Luis.Colorado@HispaLinux.ES>
 * Date: Wed Nov 12 01:01:06 MET 2003
 *
 * Disclaimer:
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#define IN_POW_C

/* Standard include files */
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "aes.h"

/* constants */

/* types */

/* prototypes */

/* variables */
static char POW_C_RCSId[]="\n$Id: pow.c,v 1.1 2003/11/12 00:17:56 luis Exp $\n";

/* functions */

/* Esta funci�n calcula potencias en campos GF(2^8) con la multiplicaci�n
 * definida por aes_mult() */
AES_BYTE aes_pow(AES_BYTE x, int n)
{
	AES_BYTE a;

	a = 1;
	while (n) {
		if (n & 1) {
			a = aes_mult(a, x);
		} /* if */
		x = aes_mult(x, x);
		n >>= 1;
	} /* while */

	return a;
} /* aes_pow */

/* $Id: pow.c,v 1.1 2003/11/12 00:17:56 luis Exp $ */