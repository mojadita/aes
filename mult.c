/* $Id: mult.c,v 1.1 2003/11/11 23:54:47 luis Exp $
 * Author: Luis Colorado <Luis.Colorado@HispaLinux.ES>
 * Date: Tue Nov 11 00:26:05 MET 2003
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

#define IN_MULT_C

/* Standard include files */
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

/* constants */
#define AES_POL 0x11b

/* types */

/* prototypes */

/* variables */
static char MULT_C_RCSId[]="\n$Id: mult.c,v 1.1 2003/11/11 23:54:47 luis Exp $\n";

/* functions */
int aes_mult(int x, int y) /* test ok */
{
	int ac = 0x0;
	int m = 0x80;

	while(m) {
		ac <<= 1;
		if (x & m) {
			ac ^= y;
		} /* if */
		if (ac & 0x100) {
			ac ^= AES_POL;
		} /* if */
		m >>= 1;
	} /* while */

	return ac;
} /* mult */

/* $Id: mult.c,v 1.1 2003/11/11 23:54:47 luis Exp $ */
