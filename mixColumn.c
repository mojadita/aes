/* $Id: mixColumn.c,v 1.2 2003/11/27 00:55:09 luis Exp $
 * Author: Luis Colorado <Luis.Colorado@HispaLinux.ES>
 * Date: Wed Nov 26 19:28:42 MET 2003
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

#define IN_MIXCOLUMN_C

/* Standard include files */
#include <sys/types.h>
#include <stdio.h>
#include "aes.h"

/* constants */
#define DEBUG 1
#define MAIN 0

/* types */

/* prototypes */

/* variables */
static char MIXCOLUMN_C_RCSId[]="\n$Id: mixColumn.c,v 1.2 2003/11/27 00:55:09 luis Exp $\n";

static BYTE pol1[] = { 0x02, 0x01, 0x01, 0x03 };
static BYTE pol2[] = { 0x0e, 0x09, 0x0d, 0x0b };

/* functions */

/* multiplies mod x^4 + 1 two words */
static void MC(BYTE *b1, BYTE *b2)
{
	BYTE mat[AES_WS][AES_WS];
	int i, j, k;
	BYTE res[AES_WS];

	/* let's construct the matrix */
	for (i = 0; i < AES_WS; i++) {
		for (j = 0; j < AES_WS; j++) {
			register int k = (i-j)%AES_WS;
			if (k<0) k += AES_WS;
			mat[i][j] = b2[k];
		} /* for */
	} /* for */

	/* now, let's multiply the matrix by b1 */
	for (i = 0; i < AES_WS; i++) {
		res[i] = 0x00;
		for (j = 0; j < AES_WS; j++) {
			res[i] ^= aes_mult(mat[i][j], b1[j], 0x11b);
		} /* for */
	} /* for */

	/* now, copy the result to b1 */
	for (i = 0; i < AES_WS; i++) {
		b1[i] = res[i];
	} /* for */

} /* MC */

static void MCs(BYTE *b, int Nb, BYTE *p)
{
	int i;
	for (i = 0; i < Nb; i++) {
		MC(b, p);
		b += AES_WS;
	} /* for */
} /* MCs */

void aes_MixColumns(BYTE *b, int Nb)
{
	MCs(b, Nb, pol1);
} /* aes_MixColumns */

void aes_InvMixColumns(BYTE *b, int Nb)
{
	MCs(b, Nb, pol2);
} /* aes_InvMixColumns */

#if MAIN
main()
{
	static BYTE b[] = {
		0xd4, 0xbf, 0x5d, 0x30,
		0xe0, 0xb4, 0x52, 0xae,
		0xb8, 0x41, 0x11, 0xf1,
		0x1e, 0x27, 0x98, 0xe5,
	};
	print(b, 4);
	aes_MixColumns(b, 4);
	print(b, 4);
	aes_InvMixColumns(b, 4);
	print(b, 4);
}
#endif

	
/* $Id: mixColumn.c,v 1.2 2003/11/27 00:55:09 luis Exp $ */
