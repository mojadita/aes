/* $Id: mult.c,v 1.4 2003/11/12 21:16:22 luis Exp $
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
#include "aes.h"

/* constants */

/* types */

/* prototypes */

/* variables */
static char MULT_C_RCSId[]="\n$Id: mult.c,v 1.4 2003/11/12 21:16:22 luis Exp $\n";

/* functions */

/* Esta función multiplica dos números en GF(2^8) (de 8 bits)
 * módulo x^8 + x^4 + x^3 + x^1 + 1
 * Los parámetros válidos de entrada son dos enteros x e y
 * tales que 0 <= x < 0x100, 0 <= y < 0x100.
 */
AES_BYTE aes_mult(AES_BYTE x, AES_BYTE y, AES_BYTE pol) /* test ok */
{
	int ac = 0x0;
	int m = 0x80;

	while(m) {
		ac <<= 1;
		if (x & m) { /* multiplicación polinómica */
			ac ^= y;
		} /* if */
		if (ac & 0x100) { /* reducción módulo */
			ac ^= pol;
		} /* if */
		m >>= 1;
	} /* while */

	return ac;
} /* mult */

/* $Id: mult.c,v 1.4 2003/11/12 21:16:22 luis Exp $ */
