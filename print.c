/* $Id: print.c,v 1.1 2003/11/27 00:56:00 luis Exp $
 * Author: Luis Colorado <Luis.Colorado@HispaLinux.ES>
 * Date: Thu Nov 27 01:08:15 MET 2003
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

#define IN_PRINT_C

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
static char PRINT_C_RCSId[]="\n$Id: print.c,v 1.1 2003/11/27 00:56:00 luis Exp $\n";

/* functions */

static void print_raya(int Nb)
{
	register int i;

	printf("+");
	for (i = 0; i < Nb; i++)
		printf("--+");
	printf("\n");
} /* print_raya */

void aes_PrintState(BYTE *b, int Nb)
{
	register int i, j;

	print_raya(Nb);
	for(i=0;i<AES_WS;i++){
		printf("|");
		for(j=0;j<Nb;j++)
			printf("%02x|", b[j*AES_WS+i]);
		printf("\n");
		print_raya(Nb);
	} /* for */
	printf("\n");

} /* aes_PrintState */

/* $Id: print.c,v 1.1 2003/11/27 00:56:00 luis Exp $ */
