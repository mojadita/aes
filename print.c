/* $Id: print.c,v 1.5 2013/03/14 13:53:43 luis Exp $
 * Author: Luis Colorado <lc@luiscoloradosistemas.com>
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
static char PRINT_C_RCSId[]="\n$Id: print.c,v 1.5 2013/03/14 13:53:43 luis Exp $\n";

/* functions */

static void print_raya(int Nb) /* test ok */
{
	register int i;

	fprintf(stderr, "+");
	for (i = 0; i < Nb; i++)
		fprintf(stderr, "--+");
	fprintf(stderr, "\n");
} /* print_raya */

void aes_PrintState(AES_BYTE *b, int Nb) /* test ok */
{
	register int i, j;

	print_raya(Nb);
	for(i=0; i<AES_WS; i++){
		fprintf(stderr, "|");
		for(j=0; j<Nb; j++)
			fprintf(stderr, "%02x|", b[j*AES_WS+i]);
		fprintf(stderr, "\n");
		print_raya(Nb);
	} /* for */
	fprintf(stderr, "\n");

} /* aes_PrintState */

/* $Id: print.c,v 1.5 2013/03/14 13:53:43 luis Exp $ */
